/**
 * This file follows with the structure and macro definitions specified in VectorMath.def X-Macro definition file.
 */

#ifndef NE_MATH_INLINE_IMPL
#include "VectorMath.h"
#endif //NE_MATH_INLINE_IMPL

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

        NE_MATH_INL_CEX NE_VECTOR1::NE_VECTOR1(const NE_VECTOR1& other)
            : x(other.x)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR1::NE_VECTOR1(NE_VECTOR1&& other)
            : x(other.x)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator=(const NE_VECTOR1& other)
        {
            x = other.x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator=(NE_VECTOR1&& other)
        {
            x = other.x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator=(NE_COMPONENT x)
        {
            this->x = x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1::operator NE_COMPONENT() const
        {
            return x;
        }

        NE_MATH_INL_CEX NE_COMPONENT& NE_VECTOR1::operator[](std::size_t idx)
        {
            return *(&x + idx);
        }

        NE_MATH_INL_CEX NE_COMPONENT NE_VECTOR1::operator[](std::size_t idx) const
        {
            return *(&x + idx);
        }

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator+=(NE_COMPONENT scalar)
        {
            x += scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator+=(NE_VECTOR1_ARG other)
        {
            x += other.x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator-=(NE_COMPONENT scalar)
        {
            x -= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator-=(NE_VECTOR1_ARG other)
        {
            x -= other.x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator*=(NE_COMPONENT scalar)
        {
            x *= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator*=(NE_VECTOR1_ARG other)
        {
            x *= other.x;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator/=(NE_COMPONENT scalar)
        {
            x /= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator/=(NE_VECTOR1_ARG other)
        {
            x /= other.x;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR1 NE_VECTOR1::operator%=(NE_COMPONENT scalar)
        {
            x %= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1 NE_VECTOR1::operator%=(NE_VECTOR1_ARG other)
        {
            x %= other.x;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_MODULO

        #ifdef NE_VECTORMATH_OP_INC_DEC
        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator++()
        {
            x++;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1 NE_VECTOR1::operator++(int)
        {
            NE_VECTOR1 copy = NE_VECTOR1(++x);
            return copy;
        }

        NE_MATH_INL_CEX NE_VECTOR1& NE_VECTOR1::operator--()
        {
            x--;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR1 NE_VECTOR1::operator--(int)
        {
            NE_VECTOR1 copy = NE_VECTOR1(--x);
            return copy;
        }
        #endif //NE_VECTORMATH_OP_INC_DEC

        #ifdef NE_VECTORMATH_OP_COMPARISON
        NE_MATH_INL_CEX Bool1 operator==(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return Bool1(scalar == vector.x);
        }

        NE_MATH_INL_CEX Bool1 operator==(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return Bool1(vector.x == scalar);
        }

        NE_MATH_INL_CEX Bool1 operator==(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return Bool1(vectorA.x == vectorB.x);
        }

        NE_MATH_INL_CEX Bool1 operator!=(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return Bool1(scalar != vector.x);
        }

        NE_MATH_INL_CEX Bool1 operator!=(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return Bool1(vector.x != scalar);
        }

        NE_MATH_INL_CEX Bool1 operator!=(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return Bool1(vectorA.x != vectorB.x);
        }
        #endif //NE_VECTORMATH_OP_COMPARISON

        #ifdef NE_VECTORMATH_OP_LOGICAL
        NE_MATH_INL_CEX Bool1 operator!(NE_VECTOR1_ARG vector)
        {
            return Bool1(!vector.x);
        }

        NE_MATH_INL_CEX Bool1 operator&&(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return Bool1(scalar && vector.x);
        }

        NE_MATH_INL_CEX Bool1 operator&&(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return Bool1(vector.x && scalar);
        }

        NE_MATH_INL_CEX Bool1 operator&&(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return Bool1(vectorA.x && vectorB.x);
        }

        NE_MATH_INL_CEX Bool1 operator||(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return Bool1(scalar || vector.x);
        }

        NE_MATH_INL_CEX Bool1 operator||(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return Bool1(vector.x || scalar);
        }

        NE_MATH_INL_CEX Bool1 operator||(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return Bool1(vectorA.x || vectorB.x);
        }
        #endif //NE_VECTORMATH_OP_LOGICAL

        #ifdef NE_VECTORMATH_OP_BITWISE
        NE_MATH_INL_CEX NE_VECTOR1 operator~(NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(~vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator&(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar & vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator&(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x & scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator&(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x & vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator|(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar | vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator|(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x | scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator|(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x | vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator^(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar ^ vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator^(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x ^ scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator^(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x ^ vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator<<(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar << vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator<<(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x << scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator<<(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x << vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator>>(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar >> vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator>>(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x >> scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator>>(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x >> vectorB.x);
        }
        #endif //NE_VECTORMATH_OP_BITWISE

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR1 operator+(NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(+vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator-(NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(-vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator+(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar + vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator+(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x + scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator+(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x + vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator-(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar - vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator-(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x - scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator-(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x - vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator*(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar * vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator*(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x * scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator*(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x * vectorB.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator/(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar / vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator/(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x / scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator/(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x / vectorB.x);
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR1 operator%(NE_COMPONENT scalar, NE_VECTOR1_ARG vector)
        {
            return NE_VECTOR1(scalar % vector.x);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator%(NE_VECTOR1_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR1(vector.x % scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR1 operator%(NE_VECTOR1_ARG vectorA, NE_VECTOR1_ARG vectorB)
        {
            return NE_VECTOR1(vectorA.x % vectorB.x);
        }
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

        NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2(const NE_VECTOR2& other)
            : x(other.x), y(other.y)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2(NE_VECTOR2&& other)
            : x(other.x), y(other.y)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator=(const NE_VECTOR2& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator=(NE_VECTOR2&& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        NE_MATH_INL_CEX NE_COMPONENT& NE_VECTOR2::operator[](std::size_t idx)
        {
            return *(&x + idx);
        }

        NE_MATH_INL_CEX NE_COMPONENT NE_VECTOR2::operator[](std::size_t idx) const
        {
            return *(&x + idx);
        }

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator+=(NE_COMPONENT scalar)
        {
            x += scalar;
            y += scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator+=(NE_VECTOR2_ARG other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator-=(NE_COMPONENT scalar)
        {
            x -= scalar;
            y -= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator-=(NE_VECTOR2_ARG other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator*=(NE_COMPONENT scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator*=(NE_VECTOR2_ARG other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator/=(NE_COMPONENT scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator/=(NE_VECTOR2_ARG other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR2 NE_VECTOR2::operator%=(NE_COMPONENT scalar)
        {
            x %= scalar;
            y %= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2 NE_VECTOR2::operator%=(NE_VECTOR2_ARG other)
        {
            x %= other.x;
            y %= other.y;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_MODULO

        #ifdef NE_VECTORMATH_OP_INC_DEC
        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator++()
        {
            x++;
            y++;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2 NE_VECTOR2::operator++(int)
        {
            NE_VECTOR2 copy = NE_VECTOR2(++x, ++y);
            return copy;
        }

        NE_MATH_INL_CEX NE_VECTOR2& NE_VECTOR2::operator--()
        {
            x--;
            y--;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR2 NE_VECTOR2::operator--(int)
        {
            NE_VECTOR2 copy = NE_VECTOR2(--x, --y);
            return copy;
        }
        #endif //NE_VECTORMATH_OP_INC_DEC

        #ifdef NE_VECTORMATH_OP_COMPARISON
        NE_MATH_INL_CEX Bool2 operator==(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return Bool2(scalar == vector.x, scalar == vector.y);
        }

        NE_MATH_INL_CEX Bool2 operator==(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return Bool2(vector.x == scalar, vector.y == scalar);
        }

        NE_MATH_INL_CEX Bool2 operator==(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return Bool2(vectorA.x == vectorB.x, vectorA.x == vectorB.y);
        }

        NE_MATH_INL_CEX Bool2 operator!=(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return Bool2(scalar != vector.x, scalar != vector.y);
        }

        NE_MATH_INL_CEX Bool2 operator!=(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return Bool2(vector.x != scalar, vector.y != scalar);
        }

        NE_MATH_INL_CEX Bool2 operator!=(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return Bool2(vectorA.x != vectorB.x, vectorA.y != vectorB.y);
        }
        #endif //NE_VECTORMATH_OP_COMPARISON

        #ifdef NE_VECTORMATH_OP_LOGICAL
        NE_MATH_INL_CEX Bool2 operator!(NE_VECTOR2_ARG vector)
        {
            return Bool2(!vector.x, !vector.y);
        }

        NE_MATH_INL_CEX Bool2 operator&&(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return Bool2(scalar && vector.x, scalar && vector.x);
        }

        NE_MATH_INL_CEX Bool2 operator&&(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return Bool2(vector.x && scalar, vector.y && scalar);
        }

        NE_MATH_INL_CEX Bool2 operator&&(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return Bool2(vectorA.x && vectorB.x, vectorA.y && vectorB.y);
        }

        NE_MATH_INL_CEX Bool2 operator||(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return Bool2(scalar || vector.x, scalar || vector.y);
        }

        NE_MATH_INL_CEX Bool2 operator||(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return Bool2(vector.x || scalar, vector.y || scalar);
        }

        NE_MATH_INL_CEX Bool2 operator||(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return Bool2(vectorA.x || vectorB.x, vectorA.y || vectorB.y);
        }
        #endif //NE_VECTORMATH_OP_LOGICAL

        #ifdef NE_VECTORMATH_OP_BITWISE
        NE_MATH_INL_CEX NE_VECTOR2 operator~(NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(~vector.x, ~vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator&(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar & vector.x, scalar & vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator&(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x & scalar, vector.y & scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator&(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x & vectorB.x, vectorA.y & vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator|(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar | vector.x, scalar & vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator|(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x | scalar, vector.y | scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator|(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x | vectorB.x, vectorA.y | vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator^(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar ^ vector.x, scalar ^ vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator^(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x ^ scalar, vector.y ^ scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator^(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x ^ vectorB.x, vectorA.y ^ vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator<<(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar << vector.x, scalar << vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator<<(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x << scalar, vector.y << scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator<<(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x << vectorB.x, vectorA.y << vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator>>(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar >> vector.x, scalar >> vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator>>(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x >> scalar, vector.y >> scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator>>(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x >> vectorB.x, vectorA.y >> vectorB.y);
        }
        #endif //NE_VECTORMATH_OP_BITWISE

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR2 operator+(NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(+vector.x, +vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator-(NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(-vector.x, -vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator+(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar + vector.x, scalar + vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator+(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x + scalar, vector.y + scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator+(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x + vectorB.x, vectorA.y + vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator-(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar - vector.x, scalar - vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator-(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x - scalar, vector.y - scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator-(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x - vectorB.x, vectorA.y - vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator*(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar * vector.x, scalar * vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator*(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x * scalar, vector.y * scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator*(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x * vectorB.x, vectorA.y * vectorB.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator/(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar / vector.x, scalar / vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator/(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x / scalar, vector.y / scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator/(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x / vectorB.x, vectorA.y / vectorB.y);
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR2 operator%(NE_COMPONENT scalar, NE_VECTOR2_ARG vector)
        {
            return NE_VECTOR2(scalar % vector.x, scalar % vector.y);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator%(NE_VECTOR2_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR2(vector.x % scalar, vector.y % scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR2 operator%(NE_VECTOR2_ARG vectorA, NE_VECTOR2_ARG vectorB)
        {
            return NE_VECTOR2(vectorA.x % vectorB.x, vectorA.y % vectorB.y);
        }
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

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(const NE_VECTOR3& other)
            : x(other.x), y(other.y), z(other.z)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_VECTOR3&& other)
        : x(other.x), y(other.y), z(other.z)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator=(const NE_VECTOR3& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator=(NE_VECTOR3&& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        NE_MATH_INL_CEX NE_COMPONENT& NE_VECTOR3::operator[](std::size_t idx)
        {
            return *(&x + idx);
        }

        NE_MATH_INL_CEX NE_COMPONENT NE_VECTOR3::operator[](std::size_t idx) const
        {
            return *(&x + idx);
        }

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator+=(NE_COMPONENT scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator+=(NE_VECTOR3_ARG other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator-=(NE_COMPONENT scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator-=(NE_VECTOR3_ARG other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator*=(NE_COMPONENT scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator*=(NE_VECTOR3_ARG other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator/=(NE_COMPONENT scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator/=(NE_VECTOR3_ARG other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR3 NE_VECTOR3::operator%=(NE_COMPONENT scalar)
        {
            x %= scalar;
            y %= scalar;
            z %= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3 NE_VECTOR3::operator%=(NE_VECTOR3_ARG other)
        {
            x %= other.x;
            y %= other.y;
            z %= other.z;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_MODULO

        #ifdef NE_VECTORMATH_OP_INC_DEC
        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator++()
        {
            x++;
            y++;
            z++;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3 NE_VECTOR3::operator++(int)
        {
            NE_VECTOR3 copy = NE_VECTOR3(++x, ++y, ++z);
            return copy;
        }

        NE_MATH_INL_CEX NE_VECTOR3& NE_VECTOR3::operator--()
        {
            x--;
            y--;
            z--;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR3 NE_VECTOR3::operator--(int)
        {
            NE_VECTOR3 copy = NE_VECTOR3(--x, --y, --z);
            return copy;
        }
        #endif //NE_VECTORMATH_OP_INC_DEC

        #ifdef NE_VECTORMATH_OP_COMPARISON
        NE_MATH_INL_CEX Bool3 operator==(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return Bool3(scalar == vector.x, scalar == vector.y, scalar == vector.z);
        }

        NE_MATH_INL_CEX Bool3 operator==(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return Bool3(vector.x == scalar, vector.y == scalar, vector.z == scalar);
        }

        NE_MATH_INL_CEX Bool3 operator==(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return Bool3(vectorA.x == vectorB.x, vectorA.y == vectorB.y, vectorA.z == vectorB.z);
        }

        NE_MATH_INL_CEX Bool3 operator!=(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return Bool3(scalar != vector.x, scalar != vector.y, scalar != vector.z);
        }

        NE_MATH_INL_CEX Bool3 operator!=(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return Bool3(vector.x != scalar, vector.y != scalar, vector.z != scalar);
        }

        NE_MATH_INL_CEX Bool3 operator!=(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return Bool3(vectorA.x != vectorB.x, vectorA.y != vectorB.y, vectorA.z != vectorB.z);
        }
        #endif //NE_VECTORMATH_OP_COMPARISON

        #ifdef NE_VECTORMATH_OP_LOGICAL
        NE_MATH_INL_CEX Bool3 operator!(NE_VECTOR3_ARG vector)
        {
            return Bool3(!vector.x, !vector.y, !vector.z);
        }

        NE_MATH_INL_CEX Bool3 operator&&(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return Bool3(scalar && vector.x, scalar && vector.y, scalar && vector.z);
        }

        NE_MATH_INL_CEX Bool3 operator&&(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return Bool3(vector.x && scalar, vector.y && scalar, vector.z && scalar);
        }

        NE_MATH_INL_CEX Bool3 operator&&(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return Bool3(vectorA.x && vectorB.x, vectorA.y && vectorB.y, vectorA.z && vectorB.z);
        }

        NE_MATH_INL_CEX Bool3 operator||(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return Bool3(scalar || vector.x, scalar || vector.y, scalar || vector.z);
        }

        NE_MATH_INL_CEX Bool3 operator||(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return Bool3(vector.x || scalar, vector.y || scalar, vector.z || scalar);
        }

        NE_MATH_INL_CEX Bool3 operator||(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return Bool3(vectorA.x || vectorB.x, vectorA.y || vectorB.y, vectorA.z || vectorB.z);
        }
        #endif //NE_VECTORMATH_OP_LOGICAL

        #ifdef NE_VECTORMATH_OP_BITWISE
        NE_MATH_INL_CEX NE_VECTOR3 operator~(NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(~vector.x, ~vector.y, ~vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator&(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar & vector.x, scalar & vector.y, scalar & vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator&(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x & scalar, vector.y & scalar, vector.z & scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator&(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x & vectorB.x, vectorA.y & vectorB.y, vectorA.z & vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator|(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar | vector.x, scalar | vector.y, scalar | vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator|(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x | scalar, vector.y | scalar, vector.z | scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator|(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x | vectorB.x, vectorA.y | vectorB.y, vectorA.z | vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator^(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar ^ vector.x, scalar ^ vector.y, scalar ^ vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator^(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x ^ scalar, vector.y ^ scalar, vector.z ^ scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator^(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x ^ vectorB.x, vectorA.y ^ vectorB.y, vectorA.z ^ vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator<<(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar << vector.x, scalar << vector.y, scalar << vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator<<(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x << scalar, vector.y << scalar, vector.z << scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator<<(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x << vectorB.x, vectorA.y << vectorB.y, vectorA.z << vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator>>(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar >> vector.x, scalar >> vector.y, scalar >> vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator>>(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x >> scalar, vector.y >> scalar, vector.z >> scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator>>(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x >> vectorB.x, vectorA.y >> vectorB.y, vectorA.z >> vectorB.z);
        }
        #endif //NE_VECTORMATH_OP_BITWISE

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR3 operator+(NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(+vector.x, +vector.y, +vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator-(NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(-vector.x, -vector.y, -vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator+(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar + vector.x, scalar + vector.y, scalar + vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator+(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x + scalar, vector.y + scalar, vector.z + scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator+(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x + vectorB.x, vectorA.y + vectorB.y, vectorA.z + vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator-(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar - vector.x, scalar - vector.y, scalar - vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator-(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x - scalar, vector.y - scalar, vector.z - scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator-(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x - vectorB.x, vectorA.y - vectorB.y, vectorA.z - vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator*(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator*(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator*(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x * vectorB.x, vectorA.y * vectorB.y, vectorA.z * vectorB.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator/(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar / vector.x, scalar / vector.y, scalar / vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator/(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x / scalar, vector.y / scalar, vector.z / scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator/(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x / vectorB.x, vectorA.y / vectorB.y, vectorA.z / vectorB.z);
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR3 operator%(NE_COMPONENT scalar, NE_VECTOR3_ARG vector)
        {
            return NE_VECTOR3(scalar % vector.x, scalar % vector.y, scalar % vector.z);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator%(NE_VECTOR3_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR3(vector.x % scalar, vector.y % scalar, vector.z % scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR3 operator%(NE_VECTOR3_ARG vectorA, NE_VECTOR3_ARG vectorB)
        {
            return NE_VECTOR3(vectorA.x % vectorB.x, vectorA.y % vectorB.y, vectorA.z % vectorB.z);
        }
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


        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(const NE_VECTOR4& other)
            : x(other.x), y(other.y), z(other.z), w(other.w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_VECTOR4&& other)
            : x(other.x), y(other.y), z(other.z), w(other.w)
        {
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator=(const NE_VECTOR4& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator=(NE_VECTOR4&& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }

        NE_MATH_INL_CEX NE_COMPONENT& NE_VECTOR4::operator[](std::size_t idx)
        {
            return *(&x + idx);
        }

        NE_MATH_INL_CEX NE_COMPONENT NE_VECTOR4::operator[](std::size_t idx) const
        {
            return *(&x + idx);
        }

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator+=(NE_COMPONENT scalar)
        {
            x += scalar;
            y += scalar;
            z += scalar;
            w += scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator+=(NE_VECTOR4_ARG other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator-=(NE_COMPONENT scalar)
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            w -= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator-=(NE_VECTOR4_ARG other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator*=(NE_COMPONENT scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator*=(NE_VECTOR4_ARG other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator/=(NE_COMPONENT scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator/=(NE_VECTOR4_ARG other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR4 NE_VECTOR4::operator%=(NE_COMPONENT scalar)
        {
            x %= scalar;
            y %= scalar;
            z %= scalar;
            w %= scalar;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4 NE_VECTOR4::operator%=(NE_VECTOR4_ARG other)
        {
            x %= other.x;
            y %= other.y;
            z %= other.z;
            w %= other.w;
            return *this;
        }
        #endif //NE_VECTORMATH_OP_MODULO

        #ifdef NE_VECTORMATH_OP_INC_DEC
                NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator++()
        {
            x++;
            y++;
            z++;
            w++;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4 NE_VECTOR4::operator++(int)
        {
            NE_VECTOR4 copy = NE_VECTOR4(++x, ++y, ++z, ++w);
            return copy;
        }

        NE_MATH_INL_CEX NE_VECTOR4& NE_VECTOR4::operator--()
        {
            x--;
            y--;
            z--;
            w--;
            return *this;
        }

        NE_MATH_INL_CEX NE_VECTOR4 NE_VECTOR4::operator--(int)
        {
            NE_VECTOR4 copy = NE_VECTOR4(--x, --y, --z, --w);
            return copy;
        }
        #endif //NE_VECTORMATH_OP_INC_DEC

        #ifdef NE_VECTORMATH_OP_COMPARISON
        NE_MATH_INL_CEX Bool4 operator==(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return Bool4(scalar == vector.x, scalar == vector.y, scalar == vector.z, scalar == vector.w);
        }

        NE_MATH_INL_CEX Bool4 operator==(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return Bool4(vector.x == scalar, vector.y == scalar, vector.z == scalar, vector.w == scalar);
        }

        NE_MATH_INL_CEX Bool4 operator==(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return Bool4(vectorA.x == vectorB.x, vectorA.y == vectorB.y, vectorA.z == vectorB.z, vectorA.w == vectorB.w);
        }

        NE_MATH_INL_CEX Bool4 operator!=(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return Bool4(scalar != vector.x, scalar != vector.y, scalar != vector.z, scalar != vector.w);
        }

        NE_MATH_INL_CEX Bool4 operator!=(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return Bool4(vector.x != scalar, vector.y != scalar, vector.z != scalar, vector.w != scalar);
        }

        NE_MATH_INL_CEX Bool4 operator!=(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return Bool4(vectorA.x != vectorB.x, vectorA.y != vectorB.y, vectorA.z != vectorB.z, vectorA.w != vectorB.w);
        }
        #endif //NE_VECTORMATH_OP_COMPARISON

        #ifdef NE_VECTORMATH_OP_LOGICAL
        NE_MATH_INL_CEX Bool4 operator!(NE_VECTOR4_ARG vector)
        {
            return Bool4(!vector.x, !vector.y, !vector.z, !vector.w);
        }

        NE_MATH_INL_CEX Bool4 operator&&(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return Bool4(scalar && vector.x, scalar && vector.y, scalar && vector.z, scalar && vector.w);
        }

        NE_MATH_INL_CEX Bool4 operator&&(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return Bool4(vector.x && scalar, vector.y && scalar, vector.z && scalar, vector.w && scalar);
        }

        NE_MATH_INL_CEX Bool4 operator&&(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return Bool4(vectorA.x && vectorB.x, vectorA.y && vectorB.y, vectorA.z && vectorB.z, vectorA.w && vectorB.w);
        }

        NE_MATH_INL_CEX Bool4 operator||(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return Bool4(scalar || vector.x, scalar || vector.y, scalar || vector.z, scalar || vector.w);
        }

        NE_MATH_INL_CEX Bool4 operator||(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return Bool4(vector.x || scalar, vector.y || scalar, vector.z || scalar, vector.w || scalar);
        }

        NE_MATH_INL_CEX Bool4 operator||(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return Bool4(vectorA.x || vectorB.x, vectorA.y || vectorB.y, vectorA.z || vectorB.z, vectorA.w || vectorB.w);
        }
        #endif //NE_VECTORMATH_OP_LOGICAL

        #ifdef NE_VECTORMATH_OP_BITWISE
        NE_MATH_INL_CEX NE_VECTOR4 operator~(NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(~vector.x, ~vector.y, ~vector.z, ~vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator&(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar & vector.x, scalar & vector.y, scalar & vector.z, scalar & vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator&(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x & scalar, vector.y & scalar, vector.z & scalar, vector.w & scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator&(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x & vectorB.x, vectorA.y & vectorB.y, vectorA.z & vectorB.z, vectorA.w & vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator|(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar | vector.x, scalar | vector.y, scalar | vector.z, scalar | vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator|(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x | scalar, vector.y | scalar, vector.z | scalar, vector.w | scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator|(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x | vectorB.x, vectorA.y | vectorB.y, vectorA.z | vectorB.z, vectorA.w | vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator^(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar ^ vector.x, scalar ^ vector.y, scalar ^ vector.z, scalar ^ vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator^(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x ^ scalar, vector.y ^ scalar, vector.z ^ scalar, vector.w ^ scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator^(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x ^ vectorB.x, vectorA.y ^ vectorB.y, vectorA.z ^ vectorB.z, vectorA.w ^ vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator<<(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar << vector.x, scalar << vector.y, scalar << vector.z, scalar << vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator<<(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x << scalar, vector.y << scalar, vector.z << scalar, vector.w << scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator<<(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x << vectorB.x, vectorA.y << vectorB.y, vectorA.z << vectorB.z, vectorA.w << vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator>>(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar >> vector.x, scalar >> vector.y, scalar >> vector.z, scalar >> vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator>>(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x >> scalar, vector.y >> scalar, vector.z >> scalar, vector.w >> scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator>>(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x >> vectorB.x, vectorA.y >> vectorB.y, vectorA.z >> vectorB.z, vectorA.w >> vectorB.w);
        }
        #endif //NE_VECTORMATH_OP_BITWISE

        #ifdef NE_VECTORMATH_OP_ARITHMETIC
        NE_MATH_INL_CEX NE_VECTOR4 operator+(NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(+vector.x, +vector.y, +vector.z, +vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator-(NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(-vector.x, -vector.y, -vector.z, -vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator+(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar + vector.x, scalar + vector.y, scalar + vector.z, scalar + vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator+(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x + scalar, vector.y + scalar, vector.z + scalar, vector.w + scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator+(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x + vectorB.x, vectorA.y + vectorB.y, vectorA.z + vectorB.z, vectorA.w + vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator-(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar - vector.x, scalar - vector.y, scalar - vector.z, scalar - vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator-(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x - scalar, vector.y - scalar, vector.z - scalar, vector.w - scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator-(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x - vectorB.x, vectorA.y - vectorB.y, vectorA.z - vectorB.z, vectorA.w - vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator*(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator*(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator*(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x * vectorB.x, vectorA.y * vectorB.y, vectorA.z * vectorB.z, vectorA.w * vectorB.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator/(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator/(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x / scalar, vector.y / scalar, vector.z / scalar, vector.w / scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator/(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x / vectorB.x, vectorA.y / vectorB.y, vectorA.z / vectorB.z, vectorA.w / vectorB.w);
        }
        #endif //NE_VECTORMATH_OP_ARITHMETIC

        #ifdef NE_VECTORMATH_OP_MODULO
        NE_MATH_INL_CEX NE_VECTOR4 operator%(NE_COMPONENT scalar, NE_VECTOR4_ARG vector)
        {
            return NE_VECTOR4(scalar % vector.x, scalar % vector.y, scalar % vector.z, scalar % vector.w);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator%(NE_VECTOR4_ARG vector, NE_COMPONENT scalar)
        {
            return NE_VECTOR4(vector.x % scalar, vector.y % scalar, vector.z % scalar, vector.w % scalar);
        }

        NE_MATH_INL_CEX NE_VECTOR4 operator%(NE_VECTOR4_ARG vectorA, NE_VECTOR4_ARG vectorB)
        {
            return NE_VECTOR4(vectorA.x % vectorB.x, vectorA.y % vectorB.y, vectorA.z % vectorB.z, vectorA.w % vectorB.w);
        }
        #endif //NE_VECTORMATH_OP_MODULO
    } // namespace math
} // namespace null