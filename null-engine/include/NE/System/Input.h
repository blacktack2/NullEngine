#ifndef NULLENGINE_INPUT_H
#define NULLENGINE_INPUT_H

#include "NE/Core/Core.h"

#include "NE/System/Gamepad.h"
#include "NE/System/Keyboard.h"
#include "NE/System/Mouse.h"

namespace null
{
    namespace system
    {
        class Input
        {
        public:
            Input(core::Engine& engine);
            ~Input();

            /**
             * @return true on success, otherwise false. If false is returned use Input::GetDebugMessage to get an
             * error message
             */
            bool Init();

            /**
             * @return true if application has requested quit, otherwise false.
             */
            bool Update();

            Gamepad& GetGamepad()
            {
                return m_gamepad;
            }
            const Gamepad& GetGamepad() const
            {
                return m_gamepad;
            }

            Keyboard& GetKeyboard()
            {
                return m_keyboard;
            }
            const Keyboard& GetKeyboard() const
            {
                return m_keyboard;
            }

            Mouse& GetMouse()
            {
                return m_mouse;
            }
            const Mouse& GetMouse() const
            {
                return m_mouse;
            }

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }
        private:
            bool UpdateStates();
        private:
            core::Engine& m_engine;

            Gamepad  m_gamepad;
            Keyboard m_keyboard;
            Mouse    m_mouse;

            std::string m_debugMessage;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_INPUT_H
