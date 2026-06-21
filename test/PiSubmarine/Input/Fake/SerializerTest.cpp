#include <gtest/gtest.h>
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include "PiSubmarine/Input/Fake/Serializer.h"

namespace PiSubmarine::Input::Fake
{
    TEST(SerializerTest, AxisBindingRoundTripPreservesData)
    {
        Serializer serializer;
        AxisBinding binding(4, 1.75, "Fake Axis 5");

        const auto data = serializer.Serialize(binding);
        const auto restored = serializer.DeserializeAxis(data);

        const auto* restoredBinding = dynamic_cast<AxisBinding*>(restored.get());
        ASSERT_NE(restoredBinding, nullptr);
        EXPECT_EQ(restoredBinding->GetChannel(), 4);
        EXPECT_DOUBLE_EQ(restoredBinding->GetPhase(), 1.75);
        EXPECT_EQ(restoredBinding->GetHint(), "Fake Axis 5");
    }

    TEST(SerializerTest, KeyBindingRoundTripPreservesData)
    {
        Serializer serializer;
        KeyBinding binding(6, std::chrono::milliseconds(1800), std::chrono::milliseconds(500), "Fake Button 7");

        const auto data = serializer.Serialize(binding);
        const auto restored = serializer.DeserializeKey(data);

        const auto* restoredBinding = dynamic_cast<KeyBinding*>(restored.get());
        ASSERT_NE(restoredBinding, nullptr);
        EXPECT_EQ(restoredBinding->GetButton(), 6);
        EXPECT_EQ(restoredBinding->GetPeriod(), std::chrono::milliseconds(1800));
        EXPECT_EQ(restoredBinding->GetPressedDuration(), std::chrono::milliseconds(500));
        EXPECT_EQ(restoredBinding->GetHint(), "Fake Button 7");
    }
}
