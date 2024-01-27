#include "NE/System/Window.h"

#ifdef NE_BUILD_SDL2

#include "NE/API/Common_SDL2.h"

bool null::system::Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        m_debugMessage = SDL_GetError();
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
            GetWindowFlagsForDevice() |
            SDL_WINDOW_RESIZABLE      |
            SDL_WINDOW_ALLOW_HIGHDPI
            );
    m_windowData->window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, windowFlags);
    if (m_windowData->window == nullptr)
    {
        m_debugMessage = SDL_GetError();
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    SDL_SetWindowMinimumSize(m_windowData->window, m_minWidth, m_minHeight);
    SDL_SetWindowMaximumSize(m_windowData->window, m_maxWidth, m_maxHeight);

    DeviceInit();

    return true;
}

void null::system::Window::Destroy()
{
    DeviceDestroy();
    if (m_windowData->window)
    {
        SDL_DestroyWindow(m_windowData->window);
    }
    SDL_Quit();
}

#endif //NE_BUILD_SDL2
