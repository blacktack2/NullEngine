#include "NE/Core/Core.h"

#include "NE/Math/Math.h"

template<int N, const char* fmt, typename T>
void PrintVec(const T& vec)
{
    for (int i = 0; i < N; ++i)
    {
        null::debug::Message(fmt, vec[i]);
        null::debug::Message(" ");
    }
    null::debug::Message("\n");
}

const char fmtFlt[] = "%.2f";
const char fmtInt[] = "%d";

int main()
{
    null::math::Float1 f1(1);
    null::math::Float2 f2(2);
    null::math::Float3 f3(3);
    null::math::Float4 f4(4);
    null::math::FloatQuat fQ(1, 2, 3, 4);
    PrintVec<1, fmtFlt>(f1);
    PrintVec<2, fmtFlt>(f2);
    PrintVec<3, fmtFlt>(f3);
    PrintVec<4, fmtFlt>(f4);
    PrintVec<1, fmtFlt>(f1 + 5);
    PrintVec<2, fmtFlt>(f2 + 5);
    PrintVec<3, fmtFlt>(f3 + 5);
    PrintVec<4, fmtFlt>(f4 + 5);
    PrintVec<1, fmtFlt>(f1 + f1);
    PrintVec<2, fmtFlt>(f2 + f2);
    PrintVec<3, fmtFlt>(f3 + f3);
    PrintVec<4, fmtFlt>(f4 + f4);
    PrintVec<4, fmtFlt>(fQ);

    null::math::Integer1 i1(1);
    null::math::Integer2 i2(2);
    null::math::Integer3 i3(3);
    null::math::Integer4 i4(4);
    PrintVec<1, fmtInt>(i1);
    PrintVec<2, fmtInt>(i2);
    PrintVec<3, fmtInt>(i3);
    PrintVec<4, fmtInt>(i4);
    PrintVec<1, fmtInt>(i1 + 5);
    PrintVec<2, fmtInt>(i2 + 5);
    PrintVec<3, fmtInt>(i3 + 5);
    PrintVec<4, fmtInt>(i4 + 5);
    PrintVec<1, fmtInt>(i1 + i1);
    PrintVec<2, fmtInt>(i2 + i2);
    PrintVec<3, fmtInt>(i3 + i3);
    PrintVec<4, fmtInt>(i4 + i4);

    return 0;
}
