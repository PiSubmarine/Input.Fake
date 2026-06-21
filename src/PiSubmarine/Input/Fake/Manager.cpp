#include "PiSubmarine/Input/Fake/Manager.h"
#include "PiSubmarine/Input/Fake/Axis.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/Key.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>

namespace PiSubmarine::Input::Fake
{
    struct Manager::AxisState
    {
        AxisBinding Binding;
        double Value = 0.0;
    };

    struct Manager::KeyState
    {
        KeyBinding Binding;
        Api::KeyState State = Api::KeyState::Released;
    };

    namespace
    {
        double Clamp(const double value)
        {
            return std::clamp(value, -1.0, 1.0);
        }

        AxisBinding MakeAxisBinding(Api::IAxisBinding& binding)
        {
            if (const auto* fakeBinding = dynamic_cast<AxisBinding*>(&binding); fakeBinding != nullptr)
            {
                return *fakeBinding;
            }

            const std::size_t hash = std::hash<std::string>{}(binding.GetHint());
            const int channel = static_cast<int>(hash % 8U);
            const double phase = (static_cast<double>((hash / 8U) % 628U) / 100.0);
            return AxisBinding(channel, phase, binding.GetHint());
        }

        KeyBinding MakeKeyBinding(Api::IKeyBinding& binding)
        {
            if (const auto* fakeBinding = dynamic_cast<KeyBinding*>(&binding); fakeBinding != nullptr)
            {
                return *fakeBinding;
            }

            const std::size_t hash = std::hash<std::string>{}(binding.GetHint());
            const int button = static_cast<int>(hash % 12U);
            const auto period = std::chrono::milliseconds(900 + static_cast<int>(hash % 1600U));
            const auto pressedDuration = std::chrono::milliseconds(std::max<std::int64_t>(150, period.count() / 3));
            return KeyBinding(button, period, pressedDuration, binding.GetHint());
        }
    }

    std::unique_ptr<Api::IAxis> Manager::CreateAxis(Api::IAxisBinding& binding)
    {
        auto state = std::make_shared<AxisState>(AxisState{
            .Binding = MakeAxisBinding(binding)
        });
        m_Axes.push_back(state);

        return std::make_unique<Axis>([state]()
        {
            return SignedNormalizedFraction(state->Value);
        });
    }

    std::unique_ptr<Api::IKey> Manager::CreateKey(Api::IKeyBinding& binding)
    {
        auto state = std::make_shared<KeyState>(KeyState{
            .Binding = MakeKeyBinding(binding)
        });
        m_Keys.push_back(state);

        return std::make_unique<Key>([state]()
        {
            return state->State;
        });
    }

    void Manager::Tick(const std::chrono::nanoseconds& uptime, const std::chrono::nanoseconds&)
    {
        using namespace std::chrono;

        const auto seconds = duration_cast<duration<double>>(uptime).count();
        const auto millisecondsElapsed = duration_cast<milliseconds>(uptime);

        for (const auto& axis : m_Axes)
        {
            const double primary = std::sin(seconds * (0.65 + (0.12 * axis->Binding.GetChannel())) + axis->Binding.GetPhase());
            const double secondary = std::sin(seconds * (1.20 + (0.08 * axis->Binding.GetChannel())) + (axis->Binding.GetPhase() * 0.5));
            axis->Value = Clamp((primary * 0.75) + (secondary * 0.25));
        }

        for (const auto& key : m_Keys)
        {
            const auto position = millisecondsElapsed % key->Binding.GetPeriod();
            key->State = position < key->Binding.GetPressedDuration() ? Api::KeyState::Pressed : Api::KeyState::Released;
        }
    }
}
