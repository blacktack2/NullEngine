/**
 * Debug.h
 */
#ifndef EXAMPLE_DEBUG_H
#define EXAMPLE_DEBUG_H

#ifdef NE_CUSTOM_DEBUG_IMPL
#define NE_DEBUG_DECL(decl) decl;
#elif defined(NE_CUSTOM_INLINE_IMPL)
#define NE_DEBUG_DECL(decl) inline decl;
#elif defined(NE_DEBUG) || defined(NE_RELEASE)
#define NE_DEBUG_DECL(decl) inline decl;
#define NE_DEBUG_STANDARD_IMPL
#else
#define NE_DEBUG_DECL(decl) inline decl {};
#endif

namespace null
{
    namespace debug
    {
        NE_DEBUG_DECL(void Break())
        NE_DEBUG_DECL(void Message(const char* message, ...))
        NE_DEBUG_DECL(void Assert(bool condition))
        NE_DEBUG_DECL(void Assert(bool condition, const char* message, ...))
        NE_DEBUG_DECL(void AssertFail(const char* message, ...))
    }
}

#ifdef NE_DEBUG_STANDARD_IMPL
#include "Debug.inl"
#endif

#endif //EXAMPLE_DEBUG_H
