#include "NE/Core/Core.h"

#include "NE/Math/Math.h"

int main()
{
    null::math::Float1 f(1);
    null::math::Float2 f2(2);
    null::math::Float3 f3(3);
    null::math::Float4 f4(4);
    null::math::Integer1 i(1);
    null::math::Integer2 i2(2);
    null::math::Integer3 i3(3);
    null::math::Integer4 i4(4);
    null::debug::Message("Float1: %.2f\n", f.x);
    null::debug::Message("Float2: %.2f %.2f\n", f2.x, f2.y);
    null::debug::Message("Float3: %.2f %.2f %.2f\n", f3.x, f3.y, f3.z);
    null::debug::Message("Float4: %.2f %.2f %.2f %.2f\n", f4.x, f4.y, f4.z, f4.w);
    null::debug::Message("Integer1: %d\n", i.x);
    null::debug::Message("Integer2: %d %d\n", i2.x, i2.y);
    null::debug::Message("Integer3: %d %d %d\n", i3.x, i3.y, i3.z);
    null::debug::Message("Integer4: %d %d %d %d\n", i4.x, i4.y, i4.z, i4.w);
    return 0;
}
