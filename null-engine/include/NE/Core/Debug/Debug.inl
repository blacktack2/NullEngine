/**
 * Debug.cpp
 */

#ifdef NE_DEBUG_STANDARD_IMPL

#include <csignal>
#include <cstdarg>
#include <iostream>

void null::debug::Break()
{
    std::raise(SIGINT);
}

void null::debug::Message(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    std::vprintf(message, args);
    va_end(args);
}

void null::debug::Assert(bool condition)
{
    if (condition)
    {
        Break();
    }
}

void null::debug::Assert(bool condition, const char* message, ...)
{
    if (condition)
    {
        va_list args;
        va_start(args, message);
        AssertFail(message, args);
        va_end(args);
    }
}

void null::debug::AssertFail(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    Message(message, args);
    va_end(args);
    Break();
}

#endif //NE_DEBUG_STANDARD_IMPL
