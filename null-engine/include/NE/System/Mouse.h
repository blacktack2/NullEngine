#ifndef NULLENGINE_MOUSE_H
#define NULLENGINE_MOUSE_H

#include "NE/Core/Core.h"

#include <bitset>
#include <string>

namespace null
{
    namespace system
    {
        class Mouse
        {
        public:
            enum class Button : math::uint8
            {
                Unknown = 0u,
                Left,
                Middle,
                Right,
                X1,
                X2,

                _Count
            };
        public:
            Mouse();
            ~Mouse();

            void PrepareStates();
            void CommitStates();

            void SetButtonDown(Button key)
            {
                m_buttonsPressed[(std::size_t)key] = ~m_buttons[(std::size_t)key];
                m_buttons[(std::size_t)key] = 1;
            }
            void SetButtonUp(Button key)
            {
                m_buttons[(std::size_t)key] = 0;
                m_buttonsReleased[(std::size_t)key] = 1;
            }

            void SetPosX(float x)
            {
                m_posDX += x - m_posX;
                m_posX = x;
            }
            void SetPosY(float y)
            {
                m_posDY += y - m_posY;
                m_posY = y;
            }

            void SetScrollX(float scrollX)
            {
                m_scrollX = scrollX;
            }
            void SetScrollY(float scrollY)
            {
                m_scrollY = scrollY;
            }

            bool IsButtonDown(Button key) const
            {
                return m_buttons[(std::size_t)key];
            }
            bool WasButtonPressed(Button key) const
            {
                return m_buttonsPressed[(std::size_t)key];
            }
            bool WasButtonReleased(Button key) const
            {
                return m_buttonsReleased[(std::size_t)key];
            }

            bool WasMouseMoved() const
            {
                return m_posDX != 0.0f || m_posDY != 0.0f;
            }
            float GetPosX() const
            {
                return m_posX;
            }
            float GetPosY() const
            {
                return m_posY;
            }
            float GetMovementX() const
            {
                return m_posDX;
            }
            float GetMovementY() const
            {
                return m_posDY;
            }

            float GetScrollX() const
            {
                return m_scrollX;
            }
            float GetScrollY() const
            {
                return m_scrollY;
            }

            void DebugPrint() const;

            static std::string GetButtonDebugName(Button button);
        private:
            typedef std::bitset<(std::size_t)Button::_Count> buttonset_t;
        private:
            buttonset_t m_buttons;
            buttonset_t m_buttonsPressed;
            buttonset_t m_buttonsReleased;

            math::sint32 m_posX = 0;
            math::sint32 m_posY = 0;
            math::sint32 m_posDX = 0;
            math::sint32 m_posDY = 0;

            float m_scrollX = 0.0f;
            float m_scrollY = 0.0f;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_MOUSE_H
