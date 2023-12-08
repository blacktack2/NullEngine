/**
 * This file follows with the structure and macro definitions specified in VectorMath.def X-Macro definition file.
 */

#ifndef NE_MATH_INLINE_IMPL
#include "VectorMath.h"
#endif //NE_MATH_INLINE_IMPL

#define NE_VECTOR_COPY_SWAP_IMPL(N)                                                 \
NE_MATH_INL_CEX NE_VECTORN(N)::NE_VECTORN(N)(const NE_VECTORN(N)& other)            \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = other[i];                                  \
}                                                                                   \
NE_MATH_INL_CEX NE_VECTORN(N)::NE_VECTORN(N)(NE_VECTORN(N)&& other)                 \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = other[i];                                  \
}                                                                                   \
NE_MATH_INL_CEX NE_VECTORN(N)& NE_VECTORN(N)::operator=(const NE_VECTORN(N)& other) \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = other[i];                                  \
    return *this;                                                                   \
}                                                                                   \
NE_MATH_INL_CEX NE_VECTORN(N)& NE_VECTORN(N)::operator=(NE_VECTORN(N)&& other)      \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = other[i];                                  \
    return *this;                                                                   \
}

#define NE_INDEX_IMPL(N, Class)                                       \
NE_MATH_INL_CEX NE_COMPONENT& Class::operator[](std::size_t idx)      \
{                                                                     \
    return v[idx];                                                    \
}                                                                     \
NE_MATH_INL_CEX NE_COMPONENT Class::operator[](std::size_t idx) const \
{                                                                     \
    return v[idx];                                                    \
}

#define NE_VECTOR_INDEX_IMPL(N) NE_INDEX_IMPL(N, NE_VECTORN(N))

#define NE_VECTOR_ASSIGNMENT_IMPL(N, Op)                                            \
NE_MATH_INL_CEX NE_VECTORN(N)& NE_VECTORN(N)::operator Op (NE_COMPONENT scalar)     \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = v[i] Op scalar;                            \
    return *this;                                                                   \
}                                                                                   \
NE_MATH_INL_CEX NE_VECTORN(N)& NE_VECTORN(N)::operator Op (NE_VECTORN_ARG(N) other) \
{                                                                                   \
    for (uint8 i = 0; i < N; ++i) v[i] = v[i] Op other[i];                          \
    return *this;                                                                   \
}

#define NE_VECTOR_INC_DEC_IMPL(N, Op)                          \
NE_MATH_INL_CEX NE_VECTORN(N)& NE_VECTORN(N)::operator Op ()   \
{                                                              \
    for (uint8 i = 0; i < N; ++i) v[i] = v[i] Op;              \
    return *this;                                              \
}                                                              \
NE_MATH_INL_CEX NE_VECTORN(N) NE_VECTORN(N)::operator Op (int) \
{                                                              \
    NE_VECTORN(N) out;                                         \
    for (uint8 i = 0; i < N; ++i) out[i] = Op v[i];            \
    return out;                                                \
}

#define NE_VECTOR_FREE_UNARY_IMPL(N, Op)                             \
NE_MATH_INL_CEX NE_VECTORN(N) operator Op (NE_VECTORN_ARG(N) vector) \
{                                                                    \
    NE_VECTORN(N) out;                                               \
    for (uint8 i = 0; i < N; ++i) out[i] = Op vector[i];             \
    return out;                                                      \
}

#define NE_VECTOR_FREE_BINARY_IMPL(N, Op)                                                   \
NE_MATH_INL_CEX NE_VECTORN(N) operator Op (NE_VECTORN_ARG(N) vector, NE_COMPONENT scalar)   \
{                                                                                           \
    NE_VECTORN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = vector[i] Op scalar;                             \
    return out;                                                                             \
}                                                                                           \
NE_MATH_INL_CEX NE_VECTORN(N) operator Op (NE_COMPONENT scalar, NE_VECTORN_ARG(N) vector)   \
{                                                                                           \
    NE_VECTORN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = scalar Op vector[i];                             \
    return out;                                                                             \
}                                                                                           \
NE_MATH_INL_CEX NE_VECTORN(N) operator Op (NE_VECTORN_ARG(N) left, NE_VECTORN_ARG(N) right) \
{                                                                                           \
    NE_VECTORN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = left[i] Op right[i];                             \
    return out;                                                                             \
}

#define NE_VECTOR_FREE_UNARY_COMP_IMPL(N, Op)                      \
NE_MATH_INL_CEX NE_BOOLN(N) operator Op (NE_VECTORN_ARG(N) vector) \
{                                                                  \
    NE_BOOLN(N) out;                                               \
    for (uint8 i = 0; i < N; ++i) out[i] = Op vector[i];           \
    return out;                                                    \
}

#define NE_VECTOR_FREE_BINARY_COMP_IMPL(N, Op)                                            \
NE_MATH_INL_CEX NE_BOOLN(N) operator Op (NE_VECTORN_ARG(N) vector, NE_COMPONENT scalar)   \
{                                                                                         \
    NE_BOOLN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = vector[i] Op scalar;                           \
    return out;                                                                           \
}                                                                                         \
NE_MATH_INL_CEX NE_BOOLN(N) operator Op (NE_COMPONENT scalar, NE_VECTORN_ARG(N) vector)   \
{                                                                                         \
    NE_BOOLN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = scalar Op vector[i];                           \
    return out;                                                                           \
}                                                                                         \
NE_MATH_INL_CEX NE_BOOLN(N) operator Op (NE_VECTORN_ARG(N) left, NE_VECTORN_ARG(N) right) \
{                                                                                         \
    NE_BOOLN(N) out;                                                                      \
    for (uint8 i = 0; i < N; ++i) out[i] = left[i] Op right[i];                           \
    return out;                                                                           \
}

namespace null
{
    namespace math
    {
        NE_MATH_INL_CEX NE_VECTOR1::NE_VECTOR1()
        {
        }

        NE_MATH_INL_CEX NE_VECTOR1::NE_VECTOR1(NE_COMPONENT x)
            : x(x)
        {
        }

        NE_VECTOR_COPY_SWAP_IMPL(1)

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator=(NE_COMPONENT x)
        {
            this->x = x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1::operator NE_COMPONENT() const
        {
            return x;
        }

        NE_VECTOR_INDEX_IMPL(1)

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_ASSIGNMENT_IMPL(1, +=)
        NE_VECTOR_ASSIGNMENT_IMPL(1, -=)
        NE_VECTOR_ASSIGNMENT_IMPL(1, *=)
        NE_VECTOR_ASSIGNMENT_IMPL(1, /=)
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_ASSIGNMENT_IMPL(1, %=)
        #endif //NE_VECTORMATH_OP_MODULO

        #ifdef NE_VECTORMATH_OP_INC_DEC
        NE_VECTOR_INC_DEC_IMPL(1, ++)
        NE_VECTOR_INC_DEC_IMPL(1, --)
        #endif //NE_VECTORMATH_OP_INC_DEC

        #ifdef NE_VECTORMATH_OP_COMPARISON
        NE_VECTOR_FREE_BINARY_COMP_IMPL(1, ==)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(1, !=)
        #endif //NE_VECTORMATH_OP_COMPARISON

        #ifdef NE_VECTORMATH_OP_LOGICAL
        NE_VECTOR_FREE_UNARY_COMP_IMPL(1, !)

        NE_VECTOR_FREE_BINARY_COMP_IMPL(1, &&)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(1, ||)
        #endif //NE_VECTORMATH_OP_LOGICAL

        #ifdef NE_VECTORMATH_OP_BITWISE
        NE_VECTOR_FREE_UNARY_IMPL(1, ~)

        NE_VECTOR_FREE_BINARY_IMPL(1, &)
        NE_VECTOR_FREE_BINARY_IMPL(1, |)
        NE_VECTOR_FREE_BINARY_IMPL(1, ^)
        NE_VECTOR_FREE_BINARY_IMPL(1, <<)
        NE_VECTOR_FREE_BINARY_IMPL(1, >>)
        #endif //NE_VECTORMATH_OP_BITWISE

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_FREE_UNARY_IMPL(1, +)
        NE_VECTOR_FREE_UNARY_IMPL(1, -)

        NE_VECTOR_FREE_BINARY_IMPL(1, +)
        NE_VECTOR_FREE_BINARY_IMPL(1, -)
        NE_VECTOR_FREE_BINARY_IMPL(1, *)
        NE_VECTOR_FREE_BINARY_IMPL(1, /)
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_FREE_BINARY_IMPL(1, %)
        #endif //NE_VECTORMATH_OP_MODULO

        NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2()
        {
        }

        NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2(NE_COMPONENT scalar)
            : x(scalar), y(scalar)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2(NE_COMPONENT x, NE_COMPONENT y)
            : x(x), y(y)
        {
        }

        NE_VECTOR_COPY_SWAP_IMPL(2)

        NE_VECTOR_INDEX_IMPL(2)

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_ASSIGNMENT_IMPL(2, +=)
        NE_VECTOR_ASSIGNMENT_IMPL(2, -=)
        NE_VECTOR_ASSIGNMENT_IMPL(2, *=)
        NE_VECTOR_ASSIGNMENT_IMPL(2, /=)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_ASSIGNMENT_IMPL(2, %=)
#endif //NE_VECTORMATH_OP_MODULO

#ifdef NE_VECTORMATH_OP_INC_DEC
        NE_VECTOR_INC_DEC_IMPL(2, ++)
        NE_VECTOR_INC_DEC_IMPL(2, --)
#endif //NE_VECTORMATH_OP_INC_DEC

#ifdef NE_VECTORMATH_OP_COMPARISON
        NE_VECTOR_FREE_BINARY_COMP_IMPL(2, ==)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(2, !=)
#endif //NE_VECTORMATH_OP_COMPARISON

#ifdef NE_VECTORMATH_OP_LOGICAL
        NE_VECTOR_FREE_UNARY_COMP_IMPL(2, !)

        NE_VECTOR_FREE_BINARY_COMP_IMPL(2, &&)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(2, ||)
#endif //NE_VECTORMATH_OP_LOGICAL

#ifdef NE_VECTORMATH_OP_BITWISE
        NE_VECTOR_FREE_UNARY_IMPL(2, ~)

        NE_VECTOR_FREE_BINARY_IMPL(2, &)
        NE_VECTOR_FREE_BINARY_IMPL(2, |)
        NE_VECTOR_FREE_BINARY_IMPL(2, ^)
        NE_VECTOR_FREE_BINARY_IMPL(2, <<)
        NE_VECTOR_FREE_BINARY_IMPL(2, >>)
#endif //NE_VECTORMATH_OP_BITWISE

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_FREE_UNARY_IMPL(2, +)
        NE_VECTOR_FREE_UNARY_IMPL(2, -)

        NE_VECTOR_FREE_BINARY_IMPL(2, +)
        NE_VECTOR_FREE_BINARY_IMPL(2, -)
        NE_VECTOR_FREE_BINARY_IMPL(2, *)
        NE_VECTOR_FREE_BINARY_IMPL(2, /)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_FREE_BINARY_IMPL(2, %)
#endif //NE_VECTORMATH_OP_MODULO

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3()
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_COMPONENT scalar)
            : x(scalar), y(scalar), z(scalar)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_COMPONENT x, NE_COMPONENT y, NE_COMPONENT z)
            : x(x), y(y), z(z)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_VECTOR2_ARG xy, NE_COMPONENT z)
            : x(xy.x), y(xy.y), z(z)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_COMPONENT x, NE_VECTOR2_ARG yz)
            : x(x), y(yz.x), z(yz.y)
        {
        }

        NE_VECTOR_COPY_SWAP_IMPL(3)

        NE_VECTOR_INDEX_IMPL(3)

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_ASSIGNMENT_IMPL(3, +=)
        NE_VECTOR_ASSIGNMENT_IMPL(3, -=)
        NE_VECTOR_ASSIGNMENT_IMPL(3, *=)
        NE_VECTOR_ASSIGNMENT_IMPL(3, /=)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_ASSIGNMENT_IMPL(3, %=)
#endif //NE_VECTORMATH_OP_MODULO

#ifdef NE_VECTORMATH_OP_INC_DEC
        NE_VECTOR_INC_DEC_IMPL(3, ++)
        NE_VECTOR_INC_DEC_IMPL(3, --)
#endif //NE_VECTORMATH_OP_INC_DEC

#ifdef NE_VECTORMATH_OP_COMPARISON
        NE_VECTOR_FREE_BINARY_COMP_IMPL(3, ==)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(3, !=)
#endif //NE_VECTORMATH_OP_COMPARISON

#ifdef NE_VECTORMATH_OP_LOGICAL
        NE_VECTOR_FREE_UNARY_COMP_IMPL(3, !)

        NE_VECTOR_FREE_BINARY_COMP_IMPL(3, &&)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(3, ||)
#endif //NE_VECTORMATH_OP_LOGICAL

#ifdef NE_VECTORMATH_OP_BITWISE
        NE_VECTOR_FREE_UNARY_IMPL(3, ~)

        NE_VECTOR_FREE_BINARY_IMPL(3, &)
        NE_VECTOR_FREE_BINARY_IMPL(3, |)
        NE_VECTOR_FREE_BINARY_IMPL(3, ^)
        NE_VECTOR_FREE_BINARY_IMPL(3, <<)
        NE_VECTOR_FREE_BINARY_IMPL(3, >>)
#endif //NE_VECTORMATH_OP_BITWISE

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_FREE_UNARY_IMPL(3, +)
        NE_VECTOR_FREE_UNARY_IMPL(3, -)

        NE_VECTOR_FREE_BINARY_IMPL(3, +)
        NE_VECTOR_FREE_BINARY_IMPL(3, -)
        NE_VECTOR_FREE_BINARY_IMPL(3, *)
        NE_VECTOR_FREE_BINARY_IMPL(3, /)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_FREE_BINARY_IMPL(3, %)
#endif //NE_VECTORMATH_OP_MODULO

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4()
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT scalar)
            : x(scalar), y(scalar), z(scalar), w(scalar)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT x, NE_COMPONENT y, NE_COMPONENT z, NE_COMPONENT w)
            : x(x), y(y), z(z), w(w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_VECTOR2_ARG xy, NE_COMPONENT z, NE_COMPONENT w)
            : x(xy.x), y(xy.y), z(z), w(w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT x, NE_VECTOR2_ARG yz, NE_COMPONENT w)
            : x(x), y(yz.x), z(yz.y), w(w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT x, NE_COMPONENT y, NE_VECTOR2_ARG zw)
            : x(x), y(y), z(zw.x), w(zw.y)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_VECTOR2_ARG xy, NE_VECTOR2_ARG zw)
            : x(xy.x), y(xy.y), z(zw.x), w(zw.y)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_VECTOR3_ARG xyz, NE_COMPONENT w)
            : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT x, NE_VECTOR3_ARG yzw)
            : x(x), y(yzw.x), z(yzw.y), w(yzw.z)
        {
        }

        NE_VECTOR_COPY_SWAP_IMPL(4)

        NE_VECTOR_INDEX_IMPL(4)

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_ASSIGNMENT_IMPL(4, +=)
        NE_VECTOR_ASSIGNMENT_IMPL(4, -=)
        NE_VECTOR_ASSIGNMENT_IMPL(4, *=)
        NE_VECTOR_ASSIGNMENT_IMPL(4, /=)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_ASSIGNMENT_IMPL(4, %=)
#endif //NE_VECTORMATH_OP_MODULO

#ifdef NE_VECTORMATH_OP_INC_DEC
        NE_VECTOR_INC_DEC_IMPL(4, ++)
        NE_VECTOR_INC_DEC_IMPL(4, --)
#endif //NE_VECTORMATH_OP_INC_DEC

#ifdef NE_VECTORMATH_OP_COMPARISON
        NE_VECTOR_FREE_BINARY_COMP_IMPL(4, ==)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(4, !=)
#endif //NE_VECTORMATH_OP_COMPARISON

#ifdef NE_VECTORMATH_OP_LOGICAL
        NE_VECTOR_FREE_UNARY_COMP_IMPL(4, !)

        NE_VECTOR_FREE_BINARY_COMP_IMPL(4, &&)
        NE_VECTOR_FREE_BINARY_COMP_IMPL(4, ||)
#endif //NE_VECTORMATH_OP_LOGICAL

#ifdef NE_VECTORMATH_OP_BITWISE
        NE_VECTOR_FREE_UNARY_IMPL(4, ~)

        NE_VECTOR_FREE_BINARY_IMPL(4, &)
        NE_VECTOR_FREE_BINARY_IMPL(4, |)
        NE_VECTOR_FREE_BINARY_IMPL(4, ^)
        NE_VECTOR_FREE_BINARY_IMPL(4, <<)
        NE_VECTOR_FREE_BINARY_IMPL(4, >>)
#endif //NE_VECTORMATH_OP_BITWISE

#ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_VECTOR_FREE_UNARY_IMPL(4, +)
        NE_VECTOR_FREE_UNARY_IMPL(4, -)

        NE_VECTOR_FREE_BINARY_IMPL(4, +)
        NE_VECTOR_FREE_BINARY_IMPL(4, -)
        NE_VECTOR_FREE_BINARY_IMPL(4, *)
        NE_VECTOR_FREE_BINARY_IMPL(4, /)
#endif //NE_VECTORMATH_OP_ARITHMETIC

#ifdef NE_VECTORMATH_OP_MODULO
        NE_VECTOR_FREE_BINARY_IMPL(4, %)
#endif //NE_VECTORMATH_OP_MODULO

#ifdef NE_VECTORMATH_QUATERNION
        NE_MATH_INL_CEX NE_QUAT::NE_QUAT()
        {
        }

        NE_MATH_INL_CEX NE_QUAT::NE_QUAT(NE_COMPONENT scalar)
            : x(0), y(0), z(0), w(scalar)
        {
        }

        NE_MATH_INL_CEX NE_QUAT::NE_QUAT(NE_COMPONENT x, NE_COMPONENT y, NE_COMPONENT z)
            : x(x), y(y), z(z), w(0)
        {
        }

        NE_MATH_INL_CEX NE_QUAT::NE_QUAT(NE_COMPONENT x, NE_COMPONENT y, NE_COMPONENT z, NE_COMPONENT scalar)
            : x(x), y(y), z(z), w(scalar)
        {
        }

        NE_INDEX_IMPL(4, NE_QUAT)
#endif //NE_VECTORMATH_QUATERNION
    } // namespace math
} // namespace null


#undef NE_VECTOR_COPY_SWAP_IMPL
#undef NE_INDEX_IMPL
#undef NE_VECTOR_INDEX_IMPL
#undef NE_VECTOR_ASSIGNMENT_IMPL
#undef NE_VECTOR_INC_DEC_IMPL
#undef NE_VECTOR_FREE_UNARY_IMPL
#undef NE_VECTOR_FREE_BINARY_IMPL
#undef NE_VECTOR_FREE_UNARY_COMP_IMPL
#undef NE_VECTOR_FREE_BINARY_COMP_IMPL
