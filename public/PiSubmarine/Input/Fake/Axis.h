#pragma once

#include "PiSubmarine/Input/Api/IAxis.h"
#include <functional>

namespace PiSubmarine::Input::Fake
{
    class Axis final : public Api::IAxis
    {
    public:
        explicit Axis(std::function<SignedNormalizedFraction()> getValue);

        [[nodiscard]] SignedNormalizedFraction GetValue() const override;

    private:
        std::function<SignedNormalizedFraction()> m_GetValue;
    };
}
