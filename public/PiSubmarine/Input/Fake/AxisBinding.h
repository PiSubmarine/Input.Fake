#pragma once

#include "PiSubmarine/Input/Api/IAxisBinding.h"
#include <string>

namespace PiSubmarine::Input::Fake
{
    class AxisBinding final : public Api::IAxisBinding
    {
    public:
        AxisBinding(int channel, double phase, std::string hint = {});

        [[nodiscard]] std::string GetHint() const override;
        [[nodiscard]] int GetChannel() const;
        [[nodiscard]] double GetPhase() const;

    private:
        int m_Channel;
        double m_Phase;
        std::string m_Hint;
    };
}
