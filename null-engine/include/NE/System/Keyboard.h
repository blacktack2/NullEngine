#pragma once

#include "NE/Core/Core.h"

#include <bitset>
#include <string>

namespace null
{
    namespace system
    {
        class Keyboard
        {
        public:
            // Based on SDL2 Keycodes
            // Values do not map to an ascii code, but are instead indices for an array of keys.
            enum class Key : math::uint8
            {
                Unknown = 0u,
                Return,             //
                Enter = Return,
                Escape,             //
                BackSpace,          //
                Delete,             //
                LeftControl,        //
                RightControl,       //
                LeftShift,          //
                RightShift,         //
                LeftAlt,            //
                RightAlt,           //
                LeftWindows,        //
                LeftCommand = LeftWindows,
                LeftMeta    = LeftWindows,
                RightWindows,        //
                RightCommand = RightWindows,
                RightMeta    = RightWindows,
                Tab,                //
                Space,              //
                Exclamation,        // !
                SingleQuote,        // '
                DoubleQuote,        // "
                BackQuote,          // `
                Grave = BackQuote,
                Hash,               // #
                Percent,            // %
                Dollar,             // $
                Ampersand,          // &
                OpenParenthesis,    // (
                OpenBracket = OpenParenthesis,
                CloseParenthesis,   // )
                CloseBracket = CloseParenthesis,
                OpenSquareParenthesis,  // [
                OpenSquareBracket = OpenSquareParenthesis,
                CloseSquareParenthesis, // ]
                CloseSquareBracket = CloseSquareParenthesis,
                OpenCurlyParenthesis,  // [
                OpenCurlyBracket = OpenCurlyParenthesis,
                CloseCurlyParenthesis, // ]
                CloseCurlyBracket = CloseCurlyParenthesis,
                Plus,               // +
                Add = Plus,
                Minus,              // -
                Subtract = Minus,
                Hyphen   = Minus,
                Asterisk,           // *
                Multiply = Asterisk,
                Star     = Asterisk,
                Caret,              // ^
                LessThan,           // <
                LeftChevron = LessThan,
                GreaterThan,        // >
                RightChevron = GreaterThan,
                Equals,             // =
                Period,             // .
                FullStop = Period,
                Comma,              // ,
                QuestionMark,       // ?
                Colon,              // :
                SemiColon,          // ;
                At,                 // @
                ForwardSlash,       // /
                BackSlash,          // (\)
                Num0,               // 0
                Num1,               // 1
                Num2,               // 2
                Num3,               // 3
                Num4,               // 4
                Num5,               // 5
                Num6,               // 6
                Num7,               // 7
                Num8,               // 8
                Num9,               // 9
                Underscore,         // _
                A,                  // aA
                B,                  // bB
                C,                  // cC
                D,                  // dD
                E,                  // eE
                F,                  // fF
                G,                  // gG
                H,                  // hH
                I,                  // iI
                J,                  // jJ
                K,                  // kK
                L,                  // lL
                M,                  // mM
                N,                  // nN
                O,                  // oO
                P,                  // pP
                Q,                  // qQ
                R,                  // rR
                S,                  // sS
                T,                  // tT
                U,                  // uU
                V,                  // vV
                W,                  // wW
                X,                  // xX
                Y,                  // yY
                Z,                  // zZ
                Application,        //
                Power,              //
                Home,               //
                End,                //
                Insert,             //
                PrintScreen,        //
                ScrollLock,         //
                CapsLock,           //
                NumLock,            //
                KeyPadPlus,         // +
                NumPadPlus = KeyPadPlus,
                KeyPadMinus,        // -
                NumPadMinus = KeyPadMinus,
                KeyPadMultiply,     // *
                NumPadMultiply = KeyPadMultiply,
                KeyPadDivide,       // /
                NumPadDivide = KeyPadDivide,
                KeyPadEnter,        //
                NumPadEnter = KeyPadEnter,
                KeyPad0,            // 0
                NumPad0 = KeyPad0,
                KeyPad1,            // 1
                NumPad1 = KeyPad1,
                KeyPad2,            // 2
                NumPad2 = KeyPad2,
                KeyPad3,            // 3
                NumPad3 = KeyPad3,
                KeyPad4,            // 4
                NumPad4 = KeyPad4,
                KeyPad5,            // 5
                NumPad5 = KeyPad5,
                KeyPad6,            // 6
                NumPad6 = KeyPad6,
                KeyPad7,            // 7
                NumPad7 = KeyPad7,
                KeyPad8,            // 8
                NumPad8 = KeyPad8,
                KeyPad9,            // 9
                NumPad9 = KeyPad9,
                KeyPadPeriod,       // .
                NumPadPeriod = KeyPadPeriod,
                KeyPadEquals,       // =
                NumPadEquals = KeyPadEquals,
                KeyPadComma,        // ,
                NumPadComma = KeyPadComma,
                F1,                 // F1
                F2,                 // F2
                F3,                 // F3
                F4,                 // F4
                F5,                 // F5
                F6,                 // F6
                F7,                 // F7
                F8,                 // F8
                F9,                 // F9
                F10,                // F10
                F11,                // F11
                F12,                // F12
                Pause,              //
                Stop,               //
                PageUp,             //
                PageDown,           //
                Left,               //
                Right,              //
                Up,                 //
                Down,               //
                Mute,               //
                VolumeUp,           //
                VolumeDown,         //

                _Count
            };
        public:
            Keyboard();
            ~Keyboard();

            void PrepareStates();
            void CommitStates();

            void SetKeyDown(Key key)
            {
                m_keysPressed[(std::size_t)key] = ~m_keys[(std::size_t)key];
                m_keys[(std::size_t)key] = 1;
            }
            void SetKeyUp(Key key)
            {
                m_keys[(std::size_t)key] = 0;
                m_keysReleased[(std::size_t)key] = 1;
            }

            bool IsKeyDown(Key key) const
            {
                return m_keys[(std::size_t)key];
            }
            bool WasKeyPressed(Key key) const
            {
                return m_keysPressed[(std::size_t)key];
            }
            bool WasKeyReleased(Key key) const
            {
                return m_keysReleased[(std::size_t)key];
            }

            void DebugPrint() const;

            static std::string GetKeyDebugName(Key key);
        private:
            typedef std::bitset<(std::size_t)Key::_Count> keyset_t;
        private:
            keyset_t m_keys;
            keyset_t m_keysPressed;
            keyset_t m_keysReleased;
        };
    } // namespace system
} // namespace null
