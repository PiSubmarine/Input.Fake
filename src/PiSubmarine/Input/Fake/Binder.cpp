#include "PiSubmarine/Input/Fake/Binder.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <array>
#include <chrono>
#include <cstdint>
#include <limits>
#include <memory>
#include <numbers>
#include <string>

namespace PiSubmarine::Input::Fake
{
    namespace
    {
        constexpr std::uint32_t Multiplier = 1664525U;
        constexpr std::uint32_t Increment = 1013904223U;
    }

    Binder::Binder(const std::uint32_t seed)
        : m_RandomState(seed)
    {
    }

    void Binder::StartCapture(KeyCallback callback)
    {
        m_PendingKeyCapture = PendingKeyCapture{
            .RemainingDelay = CreateRandomDelay(),
            .Callback = std::move(callback)
        };
    }

    void Binder::StartCapture(AxisCallback callback)
    {
        m_PendingAxisCapture = PendingAxisCapture{
            .RemainingDelay = CreateRandomDelay(),
            .Callback = std::move(callback)
        };
    }

    void Binder::StopCapture()
    {
        if (m_PendingKeyCapture.has_value())
        {
            m_PendingKeyCapture->Callback(CaptureStatus::Cancelled, nullptr);
            m_PendingKeyCapture.reset();
        }

        if (m_PendingAxisCapture.has_value())
        {
            m_PendingAxisCapture->Callback(CaptureStatus::Cancelled, nullptr);
            m_PendingAxisCapture.reset();
        }
    }

    void Binder::Tick(const std::chrono::nanoseconds&, const std::chrono::nanoseconds& deltaTime)
    {
        static constexpr std::array<std::chrono::milliseconds, 4> periods{
            std::chrono::milliseconds(900),
            std::chrono::milliseconds(1300),
            std::chrono::milliseconds(1700),
            std::chrono::milliseconds(2200)
        };

        if (m_PendingKeyCapture.has_value())
        {
            m_PendingKeyCapture->RemainingDelay -= deltaTime;
            if (m_PendingKeyCapture->RemainingDelay <= std::chrono::nanoseconds::zero())
            {
                const std::size_t button = m_NextKey++;
                const auto period = periods[button % periods.size()];
                const auto pressedDuration = std::chrono::milliseconds(period.count() / 3);

                auto callback = std::move(m_PendingKeyCapture->Callback);
                m_PendingKeyCapture.reset();

                callback(CaptureStatus::Ok, std::make_unique<KeyBinding>(
                    static_cast<int>(button),
                    period,
                    pressedDuration,
                    "Fake Button " + std::to_string(button + 1)));
            }
        }

        if (m_PendingAxisCapture.has_value())
        {
            m_PendingAxisCapture->RemainingDelay -= deltaTime;
            if (m_PendingAxisCapture->RemainingDelay <= std::chrono::nanoseconds::zero())
            {
                const std::size_t channel = m_NextAxis++;
                const double phase = std::numbers::pi_v<double> * (0.35 * static_cast<double>(channel));

                auto callback = std::move(m_PendingAxisCapture->Callback);
                m_PendingAxisCapture.reset();

                callback(CaptureStatus::Ok, std::make_unique<AxisBinding>(
                    static_cast<int>(channel),
                    phase,
                    "Fake Axis " + std::to_string(channel + 1)));
            }
        }
    }

    std::chrono::nanoseconds Binder::CreateRandomDelay()
    {
        m_RandomState = (m_RandomState * Multiplier) + Increment;
        const auto milliseconds = 500LL + (static_cast<long long>(m_RandomState) % 1001LL);
        return std::chrono::milliseconds(milliseconds);
    }
}
