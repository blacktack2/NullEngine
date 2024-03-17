#pragma once

#include "NE/Math/MathTypes.h"

#include <cstdint>
#include <limits>

namespace null
{
    namespace math
    {
        constexpr uint8_t NE_MIN_U8 = std::numeric_limits<uint8_t>::min();
        constexpr uint8_t NE_MAX_U8 = std::numeric_limits<uint8_t>::max();
        constexpr  int8_t NE_MIN_S8 = std::numeric_limits< int8_t>::min();
        constexpr  int8_t NE_MAX_S8 = std::numeric_limits< int8_t>::max();

        constexpr uint16_t NE_MIN_U16 = std::numeric_limits<uint16_t>::min();
        constexpr uint16_t NE_MAX_U16 = std::numeric_limits<uint16_t>::max();
        constexpr  int16_t NE_MIN_S16 = std::numeric_limits< int16_t>::min();
        constexpr  int16_t NE_MAX_S16 = std::numeric_limits< int16_t>::max();

        constexpr uint32_t NE_MIN_U32 = std::numeric_limits<uint32_t>::min();
        constexpr uint32_t NE_MAX_U32 = std::numeric_limits<uint32_t>::max();
        constexpr  int32_t NE_MIN_S32 = std::numeric_limits< int32_t>::min();
        constexpr  int32_t NE_MAX_S32 = std::numeric_limits< int32_t>::max();

        constexpr uint64_t NE_MIN_U64 = std::numeric_limits<uint64_t>::min();
        constexpr uint64_t NE_MAX_U64 = std::numeric_limits<uint64_t>::max();
        constexpr  int64_t NE_MIN_S64 = std::numeric_limits< int64_t>::min();
        constexpr  int64_t NE_MAX_S64 = std::numeric_limits< int64_t>::max();

        constexpr float NE_MIN_FLT = std::numeric_limits<float>::min();
        constexpr float NE_MAX_FLT = std::numeric_limits<float>::max();

        constexpr double NE_MIN_DBL = std::numeric_limits<double>::min();
        constexpr double NE_MAX_DBL = std::numeric_limits<double>::max();
    } // namespace math
} // namespace null
