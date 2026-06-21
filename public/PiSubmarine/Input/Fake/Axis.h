#pragma once

#include "PiSubmarine/Input/Api/IAxis.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"

namespace PiSubmarine::Input::Fake
{
    class Axis final : public Api::IAxis
    {
    public:
        explicit Axis(AxisBinding binding);

        [[nodiscard]] SignedNormalizedFraction GetValue() const override;

    private:
        AxisBinding m_Binding;
    };
}
