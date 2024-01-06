#include "NE/System/Input.h"

null::system::Input::Input(null::core::Engine &engine)
    : m_engine(engine)
{

}

null::system::Input::~Input()
{

}

bool null::system::Input::Update()
{
    m_keyboard.PrepareStates();
    m_mouse.PrepareStates();
    m_gamepad.PrepareStates();

    if (UpdateStates())
    {
        return true;
    }

    m_keyboard.CommitStates();
    m_mouse.CommitStates();
    m_gamepad.CommitStates();

    return false;
}
