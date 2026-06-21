#include <gtest/gtest.h>
#include "PiSubmarine/Input/Fake/AxisBinding.h"
#include "PiSubmarine/Input/Fake/Binder.h"
#include "PiSubmarine/Input/Fake/KeyBinding.h"

namespace PiSubmarine::Input::Fake
{
    TEST(BinderTest, StartCaptureCreatesAxisBinding)
    {
        Binder binder(1);

        Api::IBinder::CaptureStatus status = Api::IBinder::CaptureStatus::UnknownError;
        std::unique_ptr<Api::IAxisBinding> binding;

        binder.StartCapture([&](const Api::IBinder::CaptureStatus callbackStatus, std::unique_ptr<Api::IAxisBinding> callbackBinding)
        {
            status = callbackStatus;
            binding = std::move(callbackBinding);
        });

        binder.Tick(std::chrono::milliseconds(400), std::chrono::milliseconds(400));
        EXPECT_EQ(status, Api::IBinder::CaptureStatus::UnknownError);
        EXPECT_EQ(binding, nullptr);

        binder.Tick(std::chrono::milliseconds(800), std::chrono::milliseconds(800));
        ASSERT_EQ(status, Api::IBinder::CaptureStatus::Ok);
        ASSERT_NE(binding, nullptr);

        const auto* fakeBinding = dynamic_cast<AxisBinding*>(binding.get());
        ASSERT_NE(fakeBinding, nullptr);
        EXPECT_EQ(fakeBinding->GetChannel(), 0);
        EXPECT_EQ(fakeBinding->GetHint(), "Fake Axis 1");
    }

    TEST(BinderTest, StartCaptureCreatesKeyBinding)
    {
        Binder binder(2);

        Api::IBinder::CaptureStatus status = Api::IBinder::CaptureStatus::UnknownError;
        std::unique_ptr<Api::IKeyBinding> binding;

        binder.StartCapture([&](const Api::IBinder::CaptureStatus callbackStatus, std::unique_ptr<Api::IKeyBinding> callbackBinding)
        {
            status = callbackStatus;
            binding = std::move(callbackBinding);
        });

        binder.Tick(std::chrono::milliseconds(400), std::chrono::milliseconds(400));
        EXPECT_EQ(status, Api::IBinder::CaptureStatus::UnknownError);
        EXPECT_EQ(binding, nullptr);

        binder.Tick(std::chrono::milliseconds(900), std::chrono::milliseconds(900));
        ASSERT_EQ(status, Api::IBinder::CaptureStatus::Ok);
        ASSERT_NE(binding, nullptr);

        const auto* fakeBinding = dynamic_cast<KeyBinding*>(binding.get());
        ASSERT_NE(fakeBinding, nullptr);
        EXPECT_EQ(fakeBinding->GetButton(), 0);
        EXPECT_EQ(fakeBinding->GetHint(), "Fake Button 1");
        EXPECT_LT(fakeBinding->GetPressedDuration(), fakeBinding->GetPeriod());
    }

    TEST(BinderTest, StopCaptureCancelsPendingCallback)
    {
        Binder binder(3);

        Api::IBinder::CaptureStatus status = Api::IBinder::CaptureStatus::UnknownError;
        bool wasCalled = false;

        binder.StartCapture([&](const Api::IBinder::CaptureStatus callbackStatus, std::unique_ptr<Api::IKeyBinding>)
        {
            status = callbackStatus;
            wasCalled = true;
        });

        binder.StopCapture();

        ASSERT_TRUE(wasCalled);
        EXPECT_EQ(status, Api::IBinder::CaptureStatus::Cancelled);
    }
}
