#include "NE/Core/Engine.h"

#include "NE/System/Device.h"
#include "NE/System/Window.h"

null::core::Engine::Engine()
    : m_window(*this), m_device(*this)
{

}

null::core::Engine::~Engine()
{

}

bool null::core::Engine::Init()
{
    if (!m_window.Init())
    {
        m_debugMessage = "Failed to load window";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    if (!m_device.Init())
    {
        m_debugMessage = "Failed to load graphics device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}
