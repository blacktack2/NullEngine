#include "NE/System/Input.h"

#ifdef NE_BUILD_SDL2

#include "NE/API/Common_SDL2.h"

namespace null
{
    namespace system
    {
        constexpr Keyboard::Key SDL2ToNullKey(SDL_Keycode key)
        {
            switch (key)
            {
                default:
                case SDLK_UNKNOWN            : return Keyboard::Key::Unknown;
                case SDLK_RETURN             : return Keyboard::Key::Return;
                case SDLK_ESCAPE             : return Keyboard::Key::Escape;
                case SDLK_BACKSPACE          : return Keyboard::Key::BackSpace;
                case SDLK_TAB                : return Keyboard::Key::Tab;
                case SDLK_SPACE              : return Keyboard::Key::Space;
                case SDLK_EXCLAIM            : return Keyboard::Key::Exclamation;
                case SDLK_QUOTEDBL           : return Keyboard::Key::DoubleQuote;
                case SDLK_HASH               : return Keyboard::Key::Hash;
                case SDLK_PERCENT            : return Keyboard::Key::Percent;
                case SDLK_DOLLAR             : return Keyboard::Key::Dollar;
                case SDLK_AMPERSAND          : return Keyboard::Key::Ampersand;
                case SDLK_QUOTE              : return Keyboard::Key::SingleQuote;
                case SDLK_LEFTPAREN          : return Keyboard::Key::OpenParenthesis;
                case SDLK_RIGHTPAREN         : return Keyboard::Key::CloseParenthesis;
                case SDLK_ASTERISK           : return Keyboard::Key::Asterisk;
                case SDLK_PLUS               : return Keyboard::Key::Plus;
                case SDLK_COMMA              : return Keyboard::Key::Comma;
                case SDLK_MINUS              : return Keyboard::Key::Minus;
                case SDLK_PERIOD             : return Keyboard::Key::Period;
                case SDLK_SLASH              : return Keyboard::Key::ForwardSlash;
                case SDLK_0                  : return Keyboard::Key::Num0;
                case SDLK_1                  : return Keyboard::Key::Num1;
                case SDLK_2                  : return Keyboard::Key::Num2;
                case SDLK_3                  : return Keyboard::Key::Num3;
                case SDLK_4                  : return Keyboard::Key::Num4;
                case SDLK_5                  : return Keyboard::Key::Num5;
                case SDLK_6                  : return Keyboard::Key::Num6;
                case SDLK_7                  : return Keyboard::Key::Num7;
                case SDLK_8                  : return Keyboard::Key::Num8;
                case SDLK_9                  : return Keyboard::Key::Num9;
                case SDLK_COLON              : return Keyboard::Key::Colon;
                case SDLK_SEMICOLON          : return Keyboard::Key::SemiColon;
                case SDLK_LESS               : return Keyboard::Key::LessThan;
                case SDLK_EQUALS             : return Keyboard::Key::Equals;
                case SDLK_GREATER            : return Keyboard::Key::GreaterThan;
                case SDLK_QUESTION           : return Keyboard::Key::QuestionMark;
                case SDLK_AT                 : return Keyboard::Key::At;
                case SDLK_LEFTBRACKET        : return Keyboard::Key::OpenSquareBracket;
                case SDLK_BACKSLASH          : return Keyboard::Key::BackSlash;
                case SDLK_RIGHTBRACKET       : return Keyboard::Key::CloseSquareBracket;
                case SDLK_CARET              : return Keyboard::Key::Caret;
                case SDLK_UNDERSCORE         : return Keyboard::Key::Underscore;
                case SDLK_BACKQUOTE          : return Keyboard::Key::BackQuote;
                case SDLK_a                  : return Keyboard::Key::A;
                case SDLK_b                  : return Keyboard::Key::B;
                case SDLK_c                  : return Keyboard::Key::C;
                case SDLK_d                  : return Keyboard::Key::D;
                case SDLK_e                  : return Keyboard::Key::E;
                case SDLK_f                  : return Keyboard::Key::F;
                case SDLK_g                  : return Keyboard::Key::G;
                case SDLK_h                  : return Keyboard::Key::H;
                case SDLK_i                  : return Keyboard::Key::I;
                case SDLK_j                  : return Keyboard::Key::J;
                case SDLK_k                  : return Keyboard::Key::K;
                case SDLK_l                  : return Keyboard::Key::L;
                case SDLK_m                  : return Keyboard::Key::M;
                case SDLK_n                  : return Keyboard::Key::N;
                case SDLK_o                  : return Keyboard::Key::O;
                case SDLK_p                  : return Keyboard::Key::P;
                case SDLK_q                  : return Keyboard::Key::Q;
                case SDLK_r                  : return Keyboard::Key::R;
                case SDLK_s                  : return Keyboard::Key::S;
                case SDLK_t                  : return Keyboard::Key::T;
                case SDLK_u                  : return Keyboard::Key::U;
                case SDLK_v                  : return Keyboard::Key::V;
                case SDLK_w                  : return Keyboard::Key::W;
                case SDLK_x                  : return Keyboard::Key::X;
                case SDLK_y                  : return Keyboard::Key::Y;
                case SDLK_z                  : return Keyboard::Key::Z;
                case SDLK_CAPSLOCK           : return Keyboard::Key::CapsLock;
                case SDLK_F1                 : return Keyboard::Key::F1;
                case SDLK_F2                 : return Keyboard::Key::F2;
                case SDLK_F3                 : return Keyboard::Key::F3;
                case SDLK_F4                 : return Keyboard::Key::F4;
                case SDLK_F5                 : return Keyboard::Key::F5;
                case SDLK_F6                 : return Keyboard::Key::F6;
                case SDLK_F7                 : return Keyboard::Key::F7;
                case SDLK_F8                 : return Keyboard::Key::F8;
                case SDLK_F9                 : return Keyboard::Key::F9;
                case SDLK_F10                : return Keyboard::Key::F10;
                case SDLK_F11                : return Keyboard::Key::F11;
                case SDLK_F12                : return Keyboard::Key::F12;
                case SDLK_PRINTSCREEN        : return Keyboard::Key::PrintScreen;
                case SDLK_SCROLLLOCK         : return Keyboard::Key::ScrollLock;
                case SDLK_PAUSE              : return Keyboard::Key::Pause;
                case SDLK_INSERT             : return Keyboard::Key::Insert;
                case SDLK_HOME               : return Keyboard::Key::Home;
                case SDLK_PAGEUP             : return Keyboard::Key::PageUp;
                case SDLK_DELETE             : return Keyboard::Key::Delete;
                case SDLK_END                : return Keyboard::Key::End;
                case SDLK_PAGEDOWN           : return Keyboard::Key::PageDown;
                case SDLK_RIGHT              : return Keyboard::Key::Right;
                case SDLK_LEFT               : return Keyboard::Key::Left;
                case SDLK_DOWN               : return Keyboard::Key::Down;
                case SDLK_UP                 : return Keyboard::Key::Up;
                case SDLK_KP_DIVIDE          : return Keyboard::Key::KeyPadDivide;
                case SDLK_KP_MULTIPLY        : return Keyboard::Key::KeyPadMultiply;
                case SDLK_KP_MINUS           : return Keyboard::Key::KeyPadMinus;
                case SDLK_KP_PLUS            : return Keyboard::Key::KeyPadPlus;
                case SDLK_KP_ENTER           : return Keyboard::Key::KeyPadEnter;
                case SDLK_KP_1               : return Keyboard::Key::KeyPad1;
                case SDLK_KP_2               : return Keyboard::Key::KeyPad2;
                case SDLK_KP_3               : return Keyboard::Key::KeyPad3;
                case SDLK_KP_4               : return Keyboard::Key::KeyPad4;
                case SDLK_KP_5               : return Keyboard::Key::KeyPad5;
                case SDLK_KP_6               : return Keyboard::Key::KeyPad6;
                case SDLK_KP_7               : return Keyboard::Key::KeyPad7;
                case SDLK_KP_8               : return Keyboard::Key::KeyPad8;
                case SDLK_KP_9               : return Keyboard::Key::KeyPad9;
                case SDLK_KP_0               : return Keyboard::Key::KeyPad0;
                case SDLK_KP_PERIOD          : return Keyboard::Key::KeyPadPeriod;
                case SDLK_APPLICATION        : return Keyboard::Key::Application;
                case SDLK_POWER              : return Keyboard::Key::Power;
                case SDLK_KP_EQUALS          : return Keyboard::Key::Equals;
                case SDLK_STOP               : return Keyboard::Key::Stop;
                case SDLK_MUTE               : return Keyboard::Key::Mute;
                case SDLK_VOLUMEUP           : return Keyboard::Key::VolumeUp;
                case SDLK_VOLUMEDOWN         : return Keyboard::Key::VolumeDown;
                case SDLK_KP_COMMA           : return Keyboard::Key::Comma;
                case SDLK_LCTRL              : return Keyboard::Key::LeftControl;
                case SDLK_LSHIFT             : return Keyboard::Key::LeftShift;
                case SDLK_LALT               : return Keyboard::Key::LeftAlt;
                case SDLK_LGUI               : return Keyboard::Key::LeftWindows;
                case SDLK_RCTRL              : return Keyboard::Key::RightControl;
                case SDLK_RSHIFT             : return Keyboard::Key::RightShift;
                case SDLK_RALT               : return Keyboard::Key::RightAlt;
                case SDLK_RGUI               : return Keyboard::Key::RightWindows;
            }
        }

        constexpr Mouse::Button SDL2ToNullButton(math::uint8 button)
        {
            switch (button)
            {
            default                : return Mouse::Button::Unknown;
            case SDL_BUTTON_LEFT   : return Mouse::Button::Left;
            case SDL_BUTTON_MIDDLE : return Mouse::Button::Middle;
            case SDL_BUTTON_RIGHT  : return Mouse::Button::Right;
            case SDL_BUTTON_X1     : return Mouse::Button::X1;
            case SDL_BUTTON_X2     : return Mouse::Button::X2;
            }
        }
    }
}

bool null::system::Input::Init()
{
    return true;
}

bool null::system::Input::UpdateStates()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            default:
            {
                debug::AssertFail("Error in SDL. Event type %u not recognized\n", event.type);
                break;
            }
            case SDL_FIRSTEVENT               : break; // not implemented
            case SDL_QUIT:
            {
                return true;
            }
            case SDL_APP_TERMINATING          : break; // not implemented
            case SDL_APP_LOWMEMORY            : break; // not implemented
            case SDL_APP_WILLENTERBACKGROUND  : break; // not implemented
            case SDL_APP_DIDENTERBACKGROUND   : break; // not implemented
            case SDL_APP_WILLENTERFOREGROUND  : break; // not implemented
            case SDL_APP_DIDENTERFOREGROUND   : break; // not implemented
            case SDL_LOCALECHANGED            : break; // not implemented
            case SDL_DISPLAYEVENT             : break; // not implemented
            case SDL_WINDOWEVENT              : break; // not implemented
            case SDL_SYSWMEVENT               : break; // not implemented
            case SDL_KEYDOWN:
            {
                m_keyboard.SetKeyDown(SDL2ToNullKey(event.key.keysym.sym));
                break;
            }
            case SDL_KEYUP:
            {
                m_keyboard.SetKeyUp(SDL2ToNullKey(event.key.keysym.sym));
                break;
            }
            case SDL_TEXTEDITING              : break; // not implemented
            case SDL_TEXTINPUT                : break; // not implemented
            case SDL_KEYMAPCHANGED            : break; // not implemented
            case SDL_MOUSEMOTION:
            {
                m_mouse.SetPosX(event.motion.x);
                m_mouse.SetPosY(event.motion.y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                m_mouse.SetButtonDown(SDL2ToNullButton(event.button.button));
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                m_mouse.SetButtonUp(SDL2ToNullButton(event.button.button));
                break;
            }
            case SDL_MOUSEWHEEL:
            {
                m_mouse.SetScrollX(event.wheel.preciseX);
                m_mouse.SetScrollY(event.wheel.preciseY);
                break;
            }
            case SDL_JOYAXISMOTION            : break; // not implemented
            case SDL_JOYBALLMOTION            : break; // not implemented
            case SDL_JOYHATMOTION             : break; // not implemented
            case SDL_JOYBUTTONDOWN            : break; // not implemented
            case SDL_JOYBUTTONUP              : break; // not implemented
            case SDL_JOYDEVICEADDED           : break; // not implemented
            case SDL_JOYDEVICEREMOVED         : break; // not implemented
            case SDL_CONTROLLERAXISMOTION     : break; // not implemented
            case SDL_CONTROLLERBUTTONDOWN     : break; // not implemented
            case SDL_CONTROLLERBUTTONUP       : break; // not implemented
            case SDL_CONTROLLERDEVICEADDED    : break; // not implemented
            case SDL_CONTROLLERDEVICEREMOVED  : break; // not implemented
            case SDL_CONTROLLERDEVICEREMAPPED : break; // not implemented
            case SDL_CONTROLLERTOUCHPADDOWN   : break; // not implemented
            case SDL_CONTROLLERTOUCHPADMOTION : break; // not implemented
            case SDL_CONTROLLERTOUCHPADUP     : break; // not implemented
            case SDL_CONTROLLERSENSORUPDATE   : break; // not implemented
            case SDL_FINGERDOWN               : break; // not implemented
            case SDL_FINGERUP                 : break; // not implemented
            case SDL_FINGERMOTION             : break; // not implemented
            case SDL_DOLLARGESTURE            : break; // not implemented
            case SDL_DOLLARRECORD             : break; // not implemented
            case SDL_MULTIGESTURE             : break; // not implemented
            case SDL_CLIPBOARDUPDATE          : break; // not implemented
            case SDL_DROPFILE                 : break; // not implemented
            case SDL_DROPTEXT                 : break; // not implemented
            case SDL_DROPBEGIN                : break; // not implemented
            case SDL_DROPCOMPLETE             : break; // not implemented
            case SDL_AUDIODEVICEADDED         : break; // not implemented
            case SDL_AUDIODEVICEREMOVED       : break; // not implemented
            case SDL_SENSORUPDATE             : break; // not implemented
            case SDL_RENDER_TARGETS_RESET     : break; // not implemented
            case SDL_RENDER_DEVICE_RESET      : break; // not implemented
            case SDL_POLLSENTINEL             : break; // not implemented
            case SDL_USEREVENT                : break; // not implemented
            case SDL_LASTEVENT                : break; // not implemented
        }
    }

    return false;
}

#endif //NE_BUILD_SDL2
