#pragma once

#include "PiSubmarine/Input/Api/IKey.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"

namespace PiSubmarine::Input::Fake
{
    class Key final : public Api::IKey
    {
    public:
        explicit Key(KeyBinding binding);

        [[nodiscard]] Api::KeyState GetState() const override;

    private:
        KeyBinding m_Binding;
    };
}
