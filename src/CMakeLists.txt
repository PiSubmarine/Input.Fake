include("${PISUBMARINE_BUILD_SYSTEM}")

message("Adding library: ${PISUBMARINE_MODULE_NAME}")
add_library(${PISUBMARINE_MODULE_NAME}
        PiSubmarine/Input/Fake/Axis.cpp
        PiSubmarine/Input/Fake/AxisBinding.cpp
        PiSubmarine/Input/Fake/Binder.cpp
        PiSubmarine/Input/Fake/InputApiDefaults.cpp
        PiSubmarine/Input/Fake/Key.cpp
        PiSubmarine/Input/Fake/KeyBinding.cpp
        PiSubmarine/Input/Fake/Manager.cpp
        PiSubmarine/Input/Fake/Serializer.cpp)
target_include_directories(${PISUBMARINE_MODULE_NAME}
        PUBLIC "../public"
        PRIVATE "./")
PiSubmarineInitTarget(${PISUBMARINE_MODULE_NAME})

PiSubmarineAddDependency("https://github.com/PiSubmarine/Input.Api.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} PUBLIC PiSubmarine.Input.Api)

PiSubmarineAddDependency("https://github.com/PiSubmarine/Time.Tickable.Api.git" "")
target_link_libraries(${PISUBMARINE_MODULE_NAME} PUBLIC PiSubmarine.Time.Tickable.Api)
