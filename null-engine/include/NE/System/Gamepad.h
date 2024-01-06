#ifndef NULLENGINE_GAMEPAD_H
#define NULLENGINE_GAMEPAD_H

#include "NE/Core/Core.h"

#include <bitset>
#include <string>

namespace null
{
    namespace system
    {
        class Gamepad
        {
        public:
            enum class Button : math::uint8
            {
                Unknown = 0u,
                A,
                B,
                X,
                Y,
                Back,
                Guide,
                Start,
                LeftStick,
                RightStick,
                LeftShoulder,
                RightShoulder,
                DPadUp,
                DPadDown,
                DPadLeft,
                DPadRight,
                Misc1,
                Share      = Misc1, // XBox Series X
                Microphone = Misc1, // PS5/Amazon Luna
                Capture    = Misc1, // Nintendo Switch Pro
                Misc2,
                PaddleP1 = Misc2, // Xbox-Elite
                Misc3,
                PaddleP2 = Misc3, // Xbox-Elite
                Misc4,
                PaddleP3 = Misc4, // Xbox-Elite
                Misc5,
                PaddleP4 = Misc5, // Xbox-Elite
                Touchpad, // PS4/PS5

                _Count
            };
        public:
            Gamepad();
            ~Gamepad();

            void PrepareStates();
            void CommitStates();
        private:
            typedef std::bitset<(std::size_t)Button::_Count> buttonset_t;
        private:
            buttonset_t m_buttons;
            buttonset_t m_buttonsPressed;
            buttonset_t m_buttonsReleased;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_GAMEPAD_H
