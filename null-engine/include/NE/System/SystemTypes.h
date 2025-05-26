#ifndef NULLENGINE_SYSTEMTYPES_H
#define NULLENGINE_SYSTEMTYPES_H

namespace null
{
    namespace system
    {
        // Window data specific to device implementation
        struct WindowGraphicsDeviceData;

        // Data specific to the window's API implementation
        struct WindowData;
        class Window;

        // Data specific to the device's API implementation
        struct GraphicsDeviceData;
        class GraphicsDevice;

        class Input;
        class Keyboard;
        class Mouse;
        class Gamepad;
    } // namespace system
} // namespace null

#endif //NULLENGINE_SYSTEMTYPES_H
