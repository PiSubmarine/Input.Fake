#include "PiSubmarine/Input/Fake/Axis.h"
#include <utility>

namespace PiSubmarine::Input::Fake
{
    Axis::Axis(std::function<SignedNormalizedFraction()> getValue)
        : m_GetValue(std::move(getValue))
    {
    }

    SignedNormalizedFraction Axis::GetValue() const
    {
        return m_GetValue();
    }
}
