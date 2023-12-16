/**
 * Math library loosely based on hlsl types and functionality.
 */
#ifndef NULLENGINE_VECTOR_H
#define NULLENGINE_VECTOR_H

#include "NE/Math/MathTypes.h"
#include "NE/Core/Debug/Debug.h"

#ifndef NE_MATH_DISABLE_INLINE
#define NE_MATH_INLINE_IMPL
#endif //NE_MATH_DISABLE_INLINE

#ifdef NE_MATH_INLINE_IMPL
#define NE_MATH_INL inline
#define NE_MATH_CEX constexpr
#else
#define NE_MATH_INL
#define NE_MATH_CEX
#endif //NE_MATH_INLINE_IMPL

#define NE_MATH_INL_CEX NE_MATH_INL NE_MATH_CEX

// BoolN
#define NE_VECTORMATH_VECTOR_CLASS Bool
#define NE_VECTORMATH_VECTOR_TYPE bool

#define NE_VECTORMATH_OP_COMPARISON
#define NE_VECTORMATH_OP_LOGICAL

#include "Vector.def"

// FloatN
#define NE_VECTORMATH_VECTOR_CLASS Float
#define NE_VECTORMATH_VECTOR_TYPE float

#define NE_VECTORMATH_QUATERNION

#define NE_VECTORMATH_OP_COMPARISON
#define NE_VECTORMATH_OP_LOGICAL
#define NE_VECTORMATH_OP_ARITHMETIC

#include "Vector.def"

// IntegerN
#define NE_VECTORMATH_VECTOR_CLASS Integer
#define NE_VECTORMATH_VECTOR_TYPE null::math::sint32

#define NE_VECTORMATH_OP_COMPARISON
#define NE_VECTORMATH_OP_LOGICAL
#define NE_VECTORMATH_OP_BITWISE
#define NE_VECTORMATH_OP_BITSHIFT
#define NE_VECTORMATH_OP_ARITHMETIC
#define NE_VECTORMATH_OP_MODULO
#define NE_VECTORMATH_OP_INC_DEC

#include "Vector.def"

#endif //NULLENGINE_VECTOR_H
