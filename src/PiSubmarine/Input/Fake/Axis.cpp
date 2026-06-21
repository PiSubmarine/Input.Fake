#include "PiSubmarine/Input/Fake/Axis.h"
#include <algorithm>
#include <chrono>
#include <cmath>

namespace PiSubmarine::Input::Fake
{
    namespace
    {
        double Clamp(const double value)
        {
            return std::clamp(value, -1.0, 1.0);
        }
    }

    Axis::Axis(AxisBinding binding)
        : m_Binding(std::move(binding))
    {
    }

    SignedNormalizedFraction Axis::GetValue() const
    {
        using namespace std::chrono;

        const auto now = duration_cast<duration<double>>(steady_clock::now().time_since_epoch()).count();
        const double primary = std::sin(now * (0.65 + (0.12 * m_Binding.GetChannel())) + m_Binding.GetPhase());
        const double secondary = std::sin(now * (1.20 + (0.08 * m_Binding.GetChannel())) + (m_Binding.GetPhase() * 0.5));
        const double combined = Clamp((primary * 0.75) + (secondary * 0.25));
        return SignedNormalizedFraction(combined);
    }
}
