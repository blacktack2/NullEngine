#pragma once

#define NE_ENUM_ENUMERATOR_BEGIN(enumType, dataType) \
enum class enumType : dataType

#define NE_ENUM_ENUMERATOR_END(enumType, dataType)

#define NE_ENUM_BITMASK_BEGIN(enumType, dataType) \
enum class enumType : dataType

// Defines utility functions for bitmask enums. ~ operator is used as a bool cast operator
#define NE_ENUM_BITMASK_END(enumType, dataType)                                       \
inline enumType operator & (enumType a, enumType b)                                   \
{                                                                                     \
    return static_cast<enumType>(static_cast<dataType>(a) & static_cast<dataType>(b));\
}                                                                                     \
inline enumType& operator &= (enumType& a, enumType b)                                \
{                                                                                     \
    return a = a & b;                                                                 \
}                                                                                     \
inline enumType operator | (enumType a, enumType b)                                   \
{                                                                                     \
    return static_cast<enumType>(static_cast<dataType>(a) | static_cast<dataType>(b));\
}                                                                                     \
inline enumType& operator |= (enumType& a, enumType b)                                \
{                                                                                     \
    return a = a | b;                                                                 \
}                                                                                     \
inline bool operator ~ (enumType a)                                                   \
{                                                                                     \
    return (bool)a;                                                                   \
}
