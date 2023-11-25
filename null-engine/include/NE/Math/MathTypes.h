#ifndef EXAMPLE_MATHTYPES_H
#define EXAMPLE_MATHTYPES_H

#include "NE/Common.h"

#include <cstddef>

namespace null
{
    namespace math
    {
        // Primitive types
        typedef unsigned char uint8;
        typedef          char sint8;
        typedef unsigned short uint16;
        typedef          short sint16;
        typedef unsigned int uint32;
        typedef          int sint32;
        typedef unsigned long long uint64;
        typedef          long long sint64;

#define NE_VECTORMATH_CLASS_DECL(classname)       class classname; typedef const classname& classname##_arg;
#define NE_VECTORMATH_CLASS_DECL_NOREF(classname) class classname; typedef classname classname##_arg;
#define NE_VECTOR_CLASS_DECL(type)\
NE_VECTORMATH_CLASS_DECL_NOREF(type##1)\
NE_VECTORMATH_CLASS_DECL(type##2)\
NE_VECTORMATH_CLASS_DECL(type##3)\
NE_VECTORMATH_CLASS_DECL(type##4)\

#define NE_MATRIX_CLASS_DECL(type)\
NE_VECTORMATH_CLASS_DECL_NOREF(type##1x1)\
NE_VECTORMATH_CLASS_DECL(type##2x2)\
NE_VECTORMATH_CLASS_DECL(type##3x3)\
NE_VECTORMATH_CLASS_DECL(type##4x4)\
NE_VECTORMATH_CLASS_DECL(type##3x4)\

#define NE_QUAT_CLASS_DECL(type) \
NE_VECTORMATH_CLASS_DECL(type##Quat)\

        // VectorMath types

        NE_VECTOR_CLASS_DECL(Bool);

        NE_VECTOR_CLASS_DECL(Float);
        NE_MATRIX_CLASS_DECL(Float);
        NE_QUAT_CLASS_DECL(Float);

        NE_VECTOR_CLASS_DECL(Double);
        NE_MATRIX_CLASS_DECL(Double);
        NE_QUAT_CLASS_DECL(Double);

        NE_VECTOR_CLASS_DECL(Integer);
        NE_MATRIX_CLASS_DECL(Integer);

        NE_VECTOR_CLASS_DECL(Long);
        NE_MATRIX_CLASS_DECL(Long);
    }
}

#endif //EXAMPLE_MATHTYPES_H
