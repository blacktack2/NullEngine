#include "NE/System/Device.h"

#if defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)

#include "NE/API/Common_SDL2_Vulkan.h"

#include "NE/Core/Engine.h"

null::system::Device::Device(core::Engine& engine)
        :
        m_engine(engine),
        m_deviceData(std::make_unique<DeviceData>())
{
}

null::system::Device::~Device()
{
    vkDestroySurfaceKHR(m_deviceData->instance, m_deviceData->surface, nullptr);
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

bool null::system::Device::WindowInit()
{
    if (!CreateSurface(m_engine.GetWindow().GetWindowData().window, m_deviceData->instance, m_deviceData->surface))
    {
        m_debugMessage = "Failed to create Vulkan surface";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

#endif //defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)
