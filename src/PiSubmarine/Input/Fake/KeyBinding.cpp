#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <utility>

namespace PiSubmarine::Input::Fake
{
    KeyBinding::KeyBinding(const int button, const std::chrono::milliseconds period, const std::chrono::milliseconds pressedDuration, std::string hint)
        : m_Button(button)
        , m_Period(period)
        , m_PressedDuration(pressedDuration)
        , m_Hint(std::move(hint))
    {
    }

    std::string KeyBinding::GetHint() const
    {
        return m_Hint;
    }

    int KeyBinding::GetButton() const
    {
        return m_Button;
    }

    std::chrono::milliseconds KeyBinding::GetPeriod() const
    {
        return m_Period;
    }

    std::chrono::milliseconds KeyBinding::GetPressedDuration() const
    {
        return m_PressedDuration;
    }
}
