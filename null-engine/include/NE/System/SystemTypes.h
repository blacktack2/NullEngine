#ifndef NULLENGINE_SYSTEMTYPES_H
#define NULLENGINE_SYSTEMTYPES_H

namespace null
{
    namespace system
    {
        // Data for the device populated by the window
        struct WindowDeviceData;

        // Data specific to the window's API implementation
        struct WindowData;
        class Window;

        // Data specific to the device's API implementation
        struct DeviceData;
        class Device;

        class Input;
        class Keyboard;
        class Mouse;
        class Gamepad;
    } // namespace system
} // namespace null

#endif //NULLENGINE_SYSTEMTYPES_H
