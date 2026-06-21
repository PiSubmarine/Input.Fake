#include <gtest/gtest.h>
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/Binder.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"

namespace PiSubmarine::Input::Fake
{
    TEST(BinderTest, StartCaptureCreatesAxisBinding)
    {
        Binder binder;

        Api::IBinder::CaptureStatus status = Api::IBinder::CaptureStatus::UnknownError;
        std::unique_ptr<Api::IAxisBinding> binding;

        binder.StartCapture([&](const Api::IBinder::CaptureStatus callbackStatus, std::unique_ptr<Api::IAxisBinding> callbackBinding)
        {
            status = callbackStatus;
            binding = std::move(callbackBinding);
        });

        ASSERT_EQ(status, Api::IBinder::CaptureStatus::Ok);
        ASSERT_NE(binding, nullptr);

        const auto* fakeBinding = dynamic_cast<AxisBinding*>(binding.get());
        ASSERT_NE(fakeBinding, nullptr);
        EXPECT_EQ(fakeBinding->GetChannel(), 0);
        EXPECT_EQ(fakeBinding->GetHint(), "Fake Axis 1");
    }

    TEST(BinderTest, StartCaptureCreatesKeyBinding)
    {
        Binder binder;

        Api::IBinder::CaptureStatus status = Api::IBinder::CaptureStatus::UnknownError;
        std::unique_ptr<Api::IKeyBinding> binding;

        binder.StartCapture([&](const Api::IBinder::CaptureStatus callbackStatus, std::unique_ptr<Api::IKeyBinding> callbackBinding)
        {
            status = callbackStatus;
            binding = std::move(callbackBinding);
        });

        ASSERT_EQ(status, Api::IBinder::CaptureStatus::Ok);
        ASSERT_NE(binding, nullptr);

        const auto* fakeBinding = dynamic_cast<KeyBinding*>(binding.get());
        ASSERT_NE(fakeBinding, nullptr);
        EXPECT_EQ(fakeBinding->GetButton(), 0);
        EXPECT_EQ(fakeBinding->GetHint(), "Fake Button 1");
        EXPECT_LT(fakeBinding->GetPressedDuration(), fakeBinding->GetPeriod());
    }
}
