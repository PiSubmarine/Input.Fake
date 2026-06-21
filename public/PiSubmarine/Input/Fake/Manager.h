#pragma once

#include "PiSubmarine/Input/Api/IManager.h"
#include "PiSubmarine/Time/ITickable.h"
#include <chrono>
#include <memory>
#include <vector>

namespace PiSubmarine::Input::Fake
{
    class Manager final : public Api::IManager, public Time::ITickable
    {
    public:
        [[nodiscard]] std::unique_ptr<Api::IAxis> CreateAxis(Api::IAxisBinding& binding) override;
        [[nodiscard]] std::unique_ptr<Api::IKey> CreateKey(Api::IKeyBinding& binding) override;
        void Tick(const std::chrono::nanoseconds& uptime, const std::chrono::nanoseconds& deltaTime) override;

    private:
        struct AxisState;
        struct KeyState;

        std::vector<std::shared_ptr<AxisState>> m_Axes;
        std::vector<std::shared_ptr<KeyState>> m_Keys;
    };
}
