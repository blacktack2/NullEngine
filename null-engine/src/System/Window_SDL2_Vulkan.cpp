#include "NE/System/Window.h"

#if defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)

#include "NE/API/Common_SDL2_Vulkan.h"

null::system::Window::Window(core::Engine& engine)
    :
    m_engine(engine),
    m_windowData(std::make_unique<WindowData>()),
    m_windowGraphicsDeviceData(std::make_unique<WindowGraphicsDeviceData>())
{
}

null::system::Window::~Window()
{
    Destroy();
}

bool null::system::Window::DeviceInit()
{
    SDL_bool result;

    math::uint32 numExtensions = 0;
    result = SDL_Vulkan_GetInstanceExtensions(m_windowData->window, &numExtensions, nullptr);
    if (result == SDL_FALSE)
    {
        m_debugMessage = "Failed to retrieve SDL2 required extension count";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    m_windowGraphicsDeviceData->requiredExtensions = std::vector<const char*>(numExtensions);

    result = SDL_Vulkan_GetInstanceExtensions(m_windowData->window, &numExtensions, m_windowGraphicsDeviceData->requiredExtensions.data());
    if (result == SDL_FALSE)
    {
        m_debugMessage = "Failed to retrieve SDL2 required extension names";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

void null::system::Window::DeviceDestroy()
{

}

SDL_WindowFlags null::system::GetWindowFlagsForDevice()
{
    return SDL_WINDOW_VULKAN;
}

#endif //defined(NE_BUILD_SDL2) && defined(NE_BUILD_VULKAN)
