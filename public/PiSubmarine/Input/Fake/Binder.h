#pragma once

#include "PiSubmarine/Input/Api/IBinder.h"
#include <cstddef>

namespace PiSubmarine::Input::Fake
{
    class Binder final : public Api::IBinder
    {
    public:
        void StartCapture(KeyCallback callback) override;
        void StartCapture(AxisCallback callback) override;
        void StopCapture() override;

    private:
        std::size_t m_NextKey = 0;
        std::size_t m_NextAxis = 0;
    };
}
