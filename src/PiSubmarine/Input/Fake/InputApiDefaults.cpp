#include "PiSubmarine/Input/Api/IAxisBinding.h"
#include "PiSubmarine/Input/Api/IKeyBinding.h"

namespace PiSubmarine::Input::Api
{
    std::string IAxisBinding::GetHint() const
    {
        return {};
    }

    std::string IKeyBinding::GetHint() const
    {
        return {};
    }
}
