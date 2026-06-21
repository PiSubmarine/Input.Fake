#pragma once

#include "PiSubmarine/Input/Api/IBinder.h"
#include "PiSubmarine/Time/ITickable.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace PiSubmarine::Input::Fake
{
    class Binder final : public Api::IBinder, public Time::ITickable
    {
    public:
        explicit Binder(std::uint32_t seed = 0x5EED1234U);

        void StartCapture(KeyCallback callback) override;
        void StartCapture(AxisCallback callback) override;
        void StopCapture() override;
        void Tick(const std::chrono::nanoseconds& uptime, const std::chrono::nanoseconds& deltaTime) override;

    private:
        struct PendingKeyCapture
        {
            std::chrono::nanoseconds RemainingDelay{};
            KeyCallback Callback;
        };

        struct PendingAxisCapture
        {
            std::chrono::nanoseconds RemainingDelay{};
            AxisCallback Callback;
        };

        [[nodiscard]] std::chrono::nanoseconds CreateRandomDelay();

        std::optional<PendingKeyCapture> m_PendingKeyCapture;
        std::optional<PendingAxisCapture> m_PendingAxisCapture;
        std::size_t m_NextKey = 0;
        std::size_t m_NextAxis = 0;
        std::uint32_t m_RandomState;
    };
}
