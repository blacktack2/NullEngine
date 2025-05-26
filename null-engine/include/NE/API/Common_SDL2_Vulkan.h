#pragma once

#if defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)

#include "NE/API/Common_Vulkan.h"
#include "NE/API/Common_SDL2.h"

#include <SDL2/SDL_vulkan.h>

namespace null
{
    namespace system
    {
    } // namespace system
} // namespace null

#endif //defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)
