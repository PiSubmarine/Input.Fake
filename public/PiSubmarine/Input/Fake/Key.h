#pragma once

#include "PiSubmarine/Input/Api/IKey.h"
#include <functional>

namespace PiSubmarine::Input::Fake
{
    class Key final : public Api::IKey
    {
    public:
        explicit Key(std::function<Api::KeyState()> getState);

        [[nodiscard]] Api::KeyState GetState() const override;

    private:
        std::function<Api::KeyState()> m_GetState;
    };
}
