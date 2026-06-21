#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include <utility>

namespace PiSubmarine::Input::Fake
{
    AxisBinding::AxisBinding(int channel, double phase, std::string hint)
        : m_Channel(channel)
        , m_Phase(phase)
        , m_Hint(std::move(hint))
    {
    }

    std::string AxisBinding::GetHint() const
    {
        return m_Hint;
    }

    int AxisBinding::GetChannel() const
    {
        return m_Channel;
    }

    double AxisBinding::GetPhase() const
    {
        return m_Phase;
    }
}
