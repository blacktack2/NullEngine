#include <NE/Math/Math.h>

#include <gtest/gtest.h>

#define NE_TEST_MIN 0.0f
#define NE_TEST_MAX 2.0f
#define NE_TEST_STEP 0.1f
#define NE_TEST_ASSERT_EQ(val1, val2) ASSERT_FLOAT_EQ(val1, val2)
#define NE_VECTORMATH_VECTOR_CLASS(n) Float##n
#define NE_VECTORMATH_VECTOR_CLASS_ARG(n) Float##n##_arg
#define NE_VECTORMATH_VECTOR_CLASS_TEST(n) Float##n##Test
#define NE_VECTORMATH_VECTOR_TYPE float

#include "VectorTest.def"

#undef NE_TEST_MIN
#undef NE_TEST_MAX
#undef NE_TEST_STEP
#undef NE_TEST_ASSERT_EQ
#undef NE_VECTORMATH_VECTOR_CLASS
#undef NE_VECTORMATH_VECTOR_CLASS_ARG
#undef NE_VECTORMATH_VECTOR_CLASS_TEST
#undef NE_VECTORMATH_VECTOR_TYPE

#define NE_TEST_MIN 0
#define NE_TEST_MAX 20
#define NE_TEST_STEP 1
#define NE_TEST_ASSERT_EQ(val1, val2) ASSERT_EQ(val1, val2)
#define NE_VECTORMATH_VECTOR_CLASS(n) Integer##n
#define NE_VECTORMATH_VECTOR_CLASS_ARG(n) Integer##n##_arg
#define NE_VECTORMATH_VECTOR_CLASS_TEST(n) Integer##n##Test
#define NE_VECTORMATH_VECTOR_TYPE int

#include "VectorTest.def"

#undef NE_TEST_MIN
#undef NE_TEST_MAX
#undef NE_TEST_STEP
#undef NE_TEST_ASSERT_EQ
#undef NE_VECTORMATH_VECTOR_CLASS
#undef NE_VECTORMATH_VECTOR_CLASS_ARG
#undef NE_VECTORMATH_VECTOR_CLASS_TEST
#undef NE_VECTORMATH_VECTOR_TYPE
