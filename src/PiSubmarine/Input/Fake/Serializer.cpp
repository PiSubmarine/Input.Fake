#include "PiSubmarine/Input/Fake/Serializer.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include <chrono>
#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace PiSubmarine::Input::Fake
{
    namespace
    {
        std::string ToString(const std::vector<std::byte>& data)
        {
            return {reinterpret_cast<const char*>(data.data()), data.size()};
        }

        std::vector<std::byte> ToBytes(const std::string& value)
        {
            std::vector<std::byte> result;
            result.reserve(value.size());
            for (const char character : value)
            {
                result.push_back(static_cast<std::byte>(character));
            }
            return result;
        }

        AxisBinding MakeAxisBinding(Api::IAxisBinding& binding)
        {
            if (const auto* fakeBinding = dynamic_cast<AxisBinding*>(&binding); fakeBinding != nullptr)
            {
                return *fakeBinding;
            }

            return AxisBinding(0, 0.0, binding.GetHint());
        }

        KeyBinding MakeKeyBinding(Api::IKeyBinding& binding)
        {
            if (const auto* fakeBinding = dynamic_cast<KeyBinding*>(&binding); fakeBinding != nullptr)
            {
                return *fakeBinding;
            }

            return KeyBinding(0, std::chrono::milliseconds(1000), std::chrono::milliseconds(300), binding.GetHint());
        }
    }

    std::vector<std::byte> Serializer::Serialize(Api::IAxisBinding& binding) const
    {
        const auto fakeBinding = MakeAxisBinding(binding);

        std::ostringstream stream;
        stream << fakeBinding.GetChannel() << '\n'
               << fakeBinding.GetPhase() << '\n'
               << fakeBinding.GetHint();
        return ToBytes(stream.str());
    }

    std::unique_ptr<Api::IAxisBinding> Serializer::DeserializeAxis(const std::vector<std::byte>& data) const
    {
        std::istringstream stream(ToString(data));

        int channel = 0;
        double phase = 0.0;
        std::string hint;
        std::string ignored;

        if (!(stream >> channel))
        {
            throw std::invalid_argument("Failed to deserialize fake axis binding channel.");
        }

        std::getline(stream, ignored);

        if (!(stream >> phase))
        {
            throw std::invalid_argument("Failed to deserialize fake axis binding phase.");
        }

        std::getline(stream, ignored);
        std::getline(stream, hint, '\0');

        return std::make_unique<AxisBinding>(channel, phase, hint);
    }

    std::vector<std::byte> Serializer::Serialize(Api::IKeyBinding& binding) const
    {
        const auto fakeBinding = MakeKeyBinding(binding);

        std::ostringstream stream;
        stream << fakeBinding.GetButton() << '\n'
               << fakeBinding.GetPeriod().count() << '\n'
               << fakeBinding.GetPressedDuration().count() << '\n'
               << fakeBinding.GetHint();
        return ToBytes(stream.str());
    }

    std::unique_ptr<Api::IKeyBinding> Serializer::DeserializeKey(const std::vector<std::byte>& data) const
    {
        std::istringstream stream(ToString(data));

        int button = 0;
        std::int64_t periodMs = 0;
        std::int64_t pressedDurationMs = 0;
        std::string hint;
        std::string ignored;

        if (!(stream >> button))
        {
            throw std::invalid_argument("Failed to deserialize fake key binding button.");
        }

        std::getline(stream, ignored);

        if (!(stream >> periodMs))
        {
            throw std::invalid_argument("Failed to deserialize fake key binding period.");
        }

        std::getline(stream, ignored);

        if (!(stream >> pressedDurationMs))
        {
            throw std::invalid_argument("Failed to deserialize fake key binding pressed duration.");
        }

        std::getline(stream, ignored);
        std::getline(stream, hint, '\0');

        return std::make_unique<KeyBinding>(
            button,
            std::chrono::milliseconds(periodMs),
            std::chrono::milliseconds(pressedDurationMs),
            hint);
    }
}
