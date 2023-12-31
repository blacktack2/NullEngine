#include "NE/System/Window.h"

#ifdef NE_BUILD_SDL2

#include "NE/API/Common_SDL2.h"

null::system::Window::Window(core::Engine& engine)
    :
    m_engine(engine),
    m_windowData(std::make_unique<WindowData>())
{

}

null::system::Window::~Window()
{
    if (m_windowData->window)
    {
        SDL_DestroyWindow(m_windowData->window);
    }
    SDL_Quit();
}

bool null::system::Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        m_debugMessage = SDL_GetError();
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(
            SDL_WINDOW_VULKAN    |
            SDL_WINDOW_RESIZABLE |
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

    return true;
}
#endif //NE_BUILD_SDL2
