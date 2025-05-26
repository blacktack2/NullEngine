#include "NE/Rendering/GraphicsDevice.h"

#if defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)

#include "NE/API/Common_SDL2_Vulkan.h"

#include "NE/Core/Engine.h"

null::render::GraphicsDevice::GraphicsDevice(core::Engine& engine)
        :
        m_engine(engine),
        m_graphicsDeviceData(std::make_unique<GraphicsDeviceData>())
{
}

null::render::GraphicsDevice::~GraphicsDevice()
{
    Destroy();
}

bool CreateSurface(SDL_Window* window, VkInstance& instance, VkSurfaceKHR& surface)
{
    VkResult vkResult;
    SDL_bool sdlResult;

    sdlResult = SDL_Vulkan_CreateSurface(window, instance, &surface);
    if (sdlResult != SDL_TRUE)
    {
        null::debug::AssertFail("Failed to create Vulkan surface\n");
        return false;
    }

    return true;
}

bool null::render::GraphicsDevice::WindowInit()
{
    if (!CreateSurface(m_engine.GetWindow().GetWindowData().window, m_graphicsDeviceData->instance, m_graphicsDeviceData->surface))
    {
        m_debugMessage = "Failed to create Vulkan surface";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

#endif //defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)
