
#include <NE/System/Mouse.h>

#include "NE/System/Input.h"

null::system::Mouse::Mouse()
{

}

null::system::Mouse::~Mouse()
{

}

void null::system::Mouse::PrepareStates()
{
    m_buttonsPressed  = buttonset_t();
    m_buttonsReleased = buttonset_t();

    m_posDX = 0;
    m_posDY = 0;

    m_scrollX = 0;
    m_scrollY = 0;
}

void null::system::Mouse::CommitStates()
{

}

void null::system::Mouse::DebugPrint() const
{
    debug::Message("Debug-printing mouse data\n");
    for (math::uint32 i = 0; i < m_buttons.size(); ++i)
    {
        if (m_buttons[i])
        {
            debug::Message("Held: %s\n", GetButtonDebugName((Button)i).c_str());
        }
        if (m_buttonsPressed[i])
        {
            debug::Message("Pressed: %s\n", GetButtonDebugName((Button)i).c_str());
        }
        if (m_buttonsReleased[i])
        {
            debug::Message("Released: %s\n", GetButtonDebugName((Button)i).c_str());
        }
    }
    if (WasMouseMoved())
    {
        debug::Message("Mouse moved by (%d,%d) to (%d, %d)", m_posDX, m_posDY, m_posX, m_posY);
    }
}

std::string null::system::Mouse::GetButtonDebugName(null::system::Mouse::Button button)
{
    switch (button)
    {
        default             : return "Button::Unknown";
        case Button::Left   : return "Button::Left";
        case Button::Middle : return "Button::Middle";
        case Button::Right  : return "Button::Right";
        case Button::X1     : return "Button::X1";
        case Button::X2     : return "Button::X2";
    }
}
