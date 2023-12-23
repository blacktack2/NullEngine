/**
 * Structures and functions common to SDL2 implementations.
 */

#ifndef NULLENGINE_COMMON_SDL2_H
#define NULLENGINE_COMMON_SDL2_H

#ifdef NE_BUILD_SDL2

#include <SDL2/SDL.h>

namespace null
{
    namespace system
    {
        struct WindowData
        {
            SDL_Window *window;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_COMMON_SDL2_H

#endif //NE_BUILD_SDL2
