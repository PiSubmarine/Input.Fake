#pragma once

#include "PiSubmarine/Input/Api/IManager.h"

namespace PiSubmarine::Input::Fake
{
    class Manager final : public Api::IManager
    {
    public:
        [[nodiscard]] std::unique_ptr<Api::IAxis> CreateAxis(Api::IAxisBinding& binding) override;
        [[nodiscard]] std::unique_ptr<Api::IKey> CreateKey(Api::IKeyBinding& binding) override;
    };
}
