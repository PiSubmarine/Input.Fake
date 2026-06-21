#include "PiSubmarine/Input/Fake/Manager.h"
#include "PiSubmarine/Input/Fake/Axis.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/Key.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>

namespace PiSubmarine::Input::Fake
{
    namespace
    {
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
        return std::make_unique<Axis>(MakeAxisBinding(binding));
    }

    std::unique_ptr<Api::IKey> Manager::CreateKey(Api::IKeyBinding& binding)
    {
        return std::make_unique<Key>(MakeKeyBinding(binding));
    }
}
