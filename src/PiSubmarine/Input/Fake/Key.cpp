#include "PiSubmarine/Input/Fake/Key.h"
#include <utility>

namespace PiSubmarine::Input::Fake
{
    Key::Key(std::function<Api::KeyState()> getState)
        : m_GetState(std::move(getState))
    {
    }

    Api::KeyState Key::GetState() const
    {
        return m_GetState();
    }
}
