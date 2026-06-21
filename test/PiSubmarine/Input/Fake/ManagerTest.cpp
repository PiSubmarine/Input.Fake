#include <gtest/gtest.h>
#include "PiSubmarine/Input/Api/KeyState.h"
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"
#include "PiSubmarine/Input/Fake/Manager.h"

namespace PiSubmarine::Input::Fake
{
    TEST(ManagerTest, CreateAxisProducesNormalizedValue)
    {
        Manager manager;
        AxisBinding binding(2, 0.5, "Pitch");

        const auto axis = manager.CreateAxis(binding);
        manager.Tick(std::chrono::seconds(1), std::chrono::seconds(1));

        ASSERT_NE(axis, nullptr);

        const double value = axis->GetValue();
        EXPECT_GE(value, -1.0);
        EXPECT_LE(value, 1.0);
    }

    TEST(ManagerTest, CreateKeyProducesValidKeyState)
    {
        Manager manager;
        KeyBinding binding(3, std::chrono::milliseconds(1200), std::chrono::milliseconds(350), "Light");

        const auto key = manager.CreateKey(binding);
        manager.Tick(std::chrono::milliseconds(100), std::chrono::milliseconds(100));

        ASSERT_NE(key, nullptr);
        EXPECT_TRUE(key->GetState() == Api::KeyState::Pressed || key->GetState() == Api::KeyState::Released);
    }

    TEST(ManagerTest, TickUpdatesKeyStateOverTime)
    {
        Manager manager;
        KeyBinding binding(1, std::chrono::milliseconds(1000), std::chrono::milliseconds(300), "Mode");

        const auto key = manager.CreateKey(binding);
        ASSERT_NE(key, nullptr);

        manager.Tick(std::chrono::milliseconds(100), std::chrono::milliseconds(100));
        EXPECT_EQ(key->GetState(), Api::KeyState::Pressed);

        manager.Tick(std::chrono::milliseconds(600), std::chrono::milliseconds(500));
        EXPECT_EQ(key->GetState(), Api::KeyState::Released);
    }
}
