#ifndef NULLENGINE_ENUM_H
#define NULLENGINE_ENUM_H

#define NE_ENUM_ENUMERATOR_BEGIN(enumType, dataType) \
enum class enumType : dataType

#define NE_ENUM_ENUMERATOR_END(enumType, dataType)

#define NE_ENUM_BITMASK_BEGIN(enumType, dataType) \
enum class enumType : dataType

#define NE_ENUM_BITMASK_END(enumType, dataType)                                       \
enumType operator & (enumType a, enumType b)                                          \
{                                                                                     \
    return static_cast<enumType>(static_cast<dataType>(a) & static_cast<dataType>(b));\
}                                                                                     \
enumType& operator &= (enumType& a, enumType b)                                        \
{                                                                                     \
    return a = a & b;                                                                        \
}                                                                                     \
enumType operator | (enumType a, enumType b)                                          \
{                                                                                     \
    return static_cast<enumType>(static_cast<dataType>(a) | static_cast<dataType>(b));\
}                                                                                     \
enumType& operator |= (enumType& a, enumType b)                                        \
{                                                                                     \
    return a = a | b;                                                                        \
}

#endif //NULLENGINE_ENUM_H
