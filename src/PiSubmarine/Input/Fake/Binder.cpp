#include "PiSubmarine/Input/Fake/Binder.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <array>
#include <chrono>
#include <memory>
#include <numbers>
#include <string>

namespace PiSubmarine::Input::Fake
{
    void Binder::StartCapture(KeyCallback callback)
    {
        static constexpr std::array<std::chrono::milliseconds, 4> periods{
            std::chrono::milliseconds(900),
            std::chrono::milliseconds(1300),
            std::chrono::milliseconds(1700),
            std::chrono::milliseconds(2200)
        };

        const std::size_t button = m_NextKey++;
        const auto period = periods[button % periods.size()];
        const auto pressedDuration = std::chrono::milliseconds(period.count() / 3);

        callback(CaptureStatus::Ok, std::make_unique<KeyBinding>(
            static_cast<int>(button),
            period,
            pressedDuration,
            "Fake Button " + std::to_string(button + 1)));
    }

    void Binder::StartCapture(AxisCallback callback)
    {
        const std::size_t channel = m_NextAxis++;
        const double phase = std::numbers::pi_v<double> * (0.35 * static_cast<double>(channel));

        callback(CaptureStatus::Ok, std::make_unique<AxisBinding>(
            static_cast<int>(channel),
            phase,
            "Fake Axis " + std::to_string(channel + 1)));
    }

    void Binder::StopCapture()
    {
    }
}
