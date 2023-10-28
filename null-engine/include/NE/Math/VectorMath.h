/**
 * Math library loosely based on hlsl types and functionality:
 * - Includes swizzle operators
 * - Operators (+-*\/ etc.) are per-component
 */
#ifndef NULLENGINE_VECTOR_H
#define NULLENGINE_VECTOR_H

#include "MathTypes.h"

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

#define NE_VECTORMATH_VECTOR_CLASS(n) Float##n
#define NE_VECTORMATH_VECTOR_CLASS_ARG(n) Float##n##_arg
#define NE_VECTORMATH_VECTOR_TYPE float

#include "VectorMath.def"

#undef NE_VECTORMATH_VECTOR_CLASS
#undef NE_VECTORMATH_VECTOR_CLASS_ARG
#undef NE_VECTORMATH_VECTOR_TYPE

#define NE_VECTORMATH_VECTOR_CLASS(n) Integer##n
#define NE_VECTORMATH_VECTOR_CLASS_ARG(n) Integer##n##_arg
#define NE_VECTORMATH_VECTOR_TYPE null::math::sint32

#include "VectorMath.def"

#undef NE_VECTORMATH_VECTOR_CLASS
#undef NE_VECTORMATH_VECTOR_CLASS_ARG
#undef NE_VECTORMATH_VECTOR_TYPE

#endif //NULLENGINE_VECTOR_H
