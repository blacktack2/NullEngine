/**
 * Structures and functions common to SDL2 implementations.
 */

#pragma once

#include <SDL2/SDL.h>

namespace null
{
    namespace system
    {
        struct WindowData
        {
            SDL_Window *window;
        };

        SDL_WindowFlags GetWindowFlagsForDevice();
    } // namespace system
} // namespace null
