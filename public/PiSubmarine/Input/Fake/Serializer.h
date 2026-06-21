#pragma once

#include "PiSubmarine/Input/Api/ISerializer.h"

namespace PiSubmarine::Input::Fake
{
    class Serializer final : public Api::ISerializer
    {
    public:
        [[nodiscard]] std::vector<std::byte> Serialize(Api::IAxisBinding& binding) const override;
        [[nodiscard]] std::unique_ptr<Api::IAxisBinding> DeserializeAxis(const std::vector<std::byte>& data) const override;

        [[nodiscard]] std::vector<std::byte> Serialize(Api::IKeyBinding& binding) const override;
        [[nodiscard]] std::unique_ptr<Api::IKeyBinding> DeserializeKey(const std::vector<std::byte>& data) const override;
    };
}
