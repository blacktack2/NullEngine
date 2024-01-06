
#include <NE/System/Keyboard.h>

null::system::Keyboard::Keyboard()
{

}

null::system::Keyboard::~Keyboard()
{

}

void null::system::Keyboard::PrepareStates()
{
    m_keysPressed  = keyset_t();
    m_keysReleased = keyset_t();
}

void null::system::Keyboard::CommitStates()
{

}

void null::system::Keyboard::DebugPrint() const
{
    debug::Message("Debug-printing key data\n");
    for (math::uint32 i = 0; i < m_keys.size(); ++i)
    {
        if (m_keys[i])
        {
            debug::Message("Held: %s\n", GetKeyDebugName((Key)i).c_str());
        }
        if (m_keysPressed[i])
        {
            debug::Message("Pressed: %s\n", GetKeyDebugName((Key)i).c_str());
        }
        if (m_keysReleased[i])
        {
            debug::Message("Released: %s\n", GetKeyDebugName((Key)i).c_str());
        }
    }
}

std::string null::system::Keyboard::GetKeyDebugName(null::system::Keyboard::Key key)
{
    switch (key)
    {
        default:
        case Key::Unknown                : return "Key::Unknown";
        case Key::Return                 : return "Key::Return";
        case Key::Escape                 : return "Key::Escape";
        case Key::BackSpace              : return "Key::BackSpace";
        case Key::Delete                 : return "Key::Delete";
        case Key::LeftControl            : return "Key::LeftControl";
        case Key::RightControl           : return "Key::RightControl";
        case Key::LeftShift              : return "Key::LeftShift";
        case Key::RightShift             : return "Key::RightShift";
        case Key::LeftAlt                : return "Key::LeftAlt";
        case Key::RightAlt               : return "Key::RightAlt";
        case Key::LeftWindows            : return "Key::LeftWindows";
        case Key::RightWindows           : return "Key::RightWindows";
        case Key::Tab                    : return "Key::Tab";
        case Key::Space                  : return "Key::Space";
        case Key::Exclamation            : return "Key::Exclamation";
        case Key::SingleQuote            : return "Key::SingleQuote";
        case Key::DoubleQuote            : return "Key::DoubleQuote";
        case Key::BackQuote              : return "Key::BackQuote";
        case Key::Hash                   : return "Key::Hash";
        case Key::Percent                : return "Key::Percent";
        case Key::Dollar                 : return "Key::Dollar";
        case Key::Ampersand              : return "Key::Ampersand";
        case Key::OpenParenthesis        : return "Key::OpenParenthesis";
        case Key::CloseParenthesis       : return "Key::CloseParenthesis";
        case Key::OpenSquareParenthesis  : return "Key::OpenSquareParenthesis";
        case Key::CloseSquareParenthesis : return "Key::CloseSquareParenthesis";
        case Key::OpenCurlyParenthesis   : return "Key::OpenCurlyParenthesis";
        case Key::CloseCurlyParenthesis  : return "Key::CloseCurlyParenthesis";
        case Key::Plus                   : return "Key::Plus";
        case Key::Minus                  : return "Key::Minus";
        case Key::Asterisk               : return "Key::Asterisk";
        case Key::Caret                  : return "Key::Caret";
        case Key::LessThan               : return "Key::LessThan";
        case Key::GreaterThan            : return "Key::GreaterThan";
        case Key::Equals                 : return "Key::Equals";
        case Key::Period                 : return "Key::Period";
        case Key::Comma                  : return "Key::Comma";
        case Key::QuestionMark           : return "Key::QuestionMark";
        case Key::Colon                  : return "Key::Colon";
        case Key::SemiColon              : return "Key::SemiColon";
        case Key::At                     : return "Key::At";
        case Key::ForwardSlash           : return "Key::ForwardSlash";
        case Key::BackSlash              : return "Key::BackSlash";
        case Key::Num0                   : return "Key::Num0";
        case Key::Num1                   : return "Key::Num1";
        case Key::Num2                   : return "Key::Num2";
        case Key::Num3                   : return "Key::Num3";
        case Key::Num4                   : return "Key::Num4";
        case Key::Num5                   : return "Key::Num5";
        case Key::Num6                   : return "Key::Num6";
        case Key::Num7                   : return "Key::Num7";
        case Key::Num8                   : return "Key::Num8";
        case Key::Num9                   : return "Key::Num9";
        case Key::Underscore             : return "Key::Underscore";
        case Key::A                      : return "Key::A";
        case Key::B                      : return "Key::B";
        case Key::C                      : return "Key::C";
        case Key::D                      : return "Key::D";
        case Key::E                      : return "Key::E";
        case Key::F                      : return "Key::F";
        case Key::G                      : return "Key::G";
        case Key::H                      : return "Key::H";
        case Key::I                      : return "Key::I";
        case Key::J                      : return "Key::J";
        case Key::K                      : return "Key::K";
        case Key::L                      : return "Key::L";
        case Key::M                      : return "Key::M";
        case Key::N                      : return "Key::N";
        case Key::O                      : return "Key::O";
        case Key::P                      : return "Key::P";
        case Key::Q                      : return "Key::Q";
        case Key::R                      : return "Key::R";
        case Key::S                      : return "Key::S";
        case Key::T                      : return "Key::T";
        case Key::U                      : return "Key::U";
        case Key::V                      : return "Key::V";
        case Key::W                      : return "Key::W";
        case Key::X                      : return "Key::X";
        case Key::Y                      : return "Key::Y";
        case Key::Z                      : return "Key::Z";
        case Key::Application            : return "Key::Application";
        case Key::Power                  : return "Key::Power";
        case Key::Home                   : return "Key::Home";
        case Key::End                    : return "Key::End";
        case Key::Insert                 : return "Key::Insert";
        case Key::PrintScreen            : return "Key::PrintScreen";
        case Key::ScrollLock             : return "Key::ScrollLock";
        case Key::CapsLock               : return "Key::CapsLock";
        case Key::NumLock                : return "Key::NumLock";
        case Key::KeyPadPlus             : return "Key::KeyPadPlus";
        case Key::KeyPadMinus            : return "Key::KeyPadMinus";
        case Key::KeyPadMultiply         : return "Key::KeyPadMultiply";
        case Key::KeyPadDivide           : return "Key::KeyPadDivide";
        case Key::KeyPadEnter            : return "Key::KeyPadEnter";
        case Key::KeyPad0                : return "Key::KeyPad0";
        case Key::KeyPad1                : return "Key::KeyPad1";
        case Key::KeyPad2                : return "Key::KeyPad2";
        case Key::KeyPad3                : return "Key::KeyPad3";
        case Key::KeyPad4                : return "Key::KeyPad4";
        case Key::KeyPad5                : return "Key::KeyPad5";
        case Key::KeyPad6                : return "Key::KeyPad6";
        case Key::KeyPad7                : return "Key::KeyPad7";
        case Key::KeyPad8                : return "Key::KeyPad8";
        case Key::KeyPad9                : return "Key::KeyPad9";
        case Key::KeyPadPeriod           : return "Key::KeyPadPeriod";
        case Key::KeyPadEquals           : return "Key::KeyPadEquals";
        case Key::KeyPadComma            : return "Key::KeyPadComma";
        case Key::F1                     : return "Key::F1";
        case Key::F2                     : return "Key::F2";
        case Key::F3                     : return "Key::F3";
        case Key::F4                     : return "Key::F4";
        case Key::F5                     : return "Key::F5";
        case Key::F6                     : return "Key::F6";
        case Key::F7                     : return "Key::F7";
        case Key::F8                     : return "Key::F8";
        case Key::F9                     : return "Key::F9";
        case Key::F10                    : return "Key::F10";
        case Key::F11                    : return "Key::F11";
        case Key::F12                    : return "Key::F12";
        case Key::Pause                  : return "Key::Pause";
        case Key::Stop                   : return "Key::Stop";
        case Key::PageUp                 : return "Key::PageUp";
        case Key::PageDown               : return "Key::PageDown";
        case Key::Left                   : return "Key::Left";
        case Key::Right                  : return "Key::Right";
        case Key::Up                     : return "Key::Up";
        case Key::Down                   : return "Key::Down";
        case Key::Mute                   : return "Key::Mute";
        case Key::VolumeUp               : return "Key::VolumeUp";
        case Key::VolumeDown             : return "Key::VolumeDown";
    }
}
