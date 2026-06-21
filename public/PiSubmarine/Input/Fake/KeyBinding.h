#pragma once

#include "PiSubmarine/Input/Api/IKeyBinding.h"
#include <chrono>
#include <string>

namespace PiSubmarine::Input::Fake
{
    class KeyBinding final : public Api::IKeyBinding
    {
    public:
        KeyBinding(int button, std::chrono::milliseconds period, std::chrono::milliseconds pressedDuration, std::string hint = {});

        [[nodiscard]] std::string GetHint() const override;
        [[nodiscard]] int GetButton() const;
        [[nodiscard]] std::chrono::milliseconds GetPeriod() const;
        [[nodiscard]] std::chrono::milliseconds GetPressedDuration() const;

    private:
        int m_Button;
        std::chrono::milliseconds m_Period;
        std::chrono::milliseconds m_PressedDuration;
        std::string m_Hint;
    };
}
