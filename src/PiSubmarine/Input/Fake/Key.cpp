#include "PiSubmarine/Input/Fake/Key.h"
#include <chrono>

namespace PiSubmarine::Input::Fake
{
    Key::Key(KeyBinding binding)
        : m_Binding(std::move(binding))
    {
    }

    Api::KeyState Key::GetState() const
    {
        using namespace std::chrono;

        const auto now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());
        const auto position = now % m_Binding.GetPeriod();
        return position < m_Binding.GetPressedDuration() ? Api::KeyState::Pressed : Api::KeyState::Released;
    }
}
