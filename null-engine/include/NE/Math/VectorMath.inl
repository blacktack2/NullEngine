/**
 * This file follows with the structure and macro definitions specified in VectorMath.def X-Macro definition file.
 */
 
using namespace null;
using namespace math;

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

NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2()
{
}

NE_MATH_INL_CEX NE_VECTOR2::NE_VECTOR2(NE_COMPONENT value)
    : x(value), y(value)
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

NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3()
{
}

NE_MATH_INL_CEX NE_VECTOR3::NE_VECTOR3(NE_COMPONENT value)
    : x(value), y(value), z(value)
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

NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4()
{
}

NE_MATH_INL_CEX NE_VECTOR4::NE_VECTOR4(NE_COMPONENT value)
    : x(value), y(value), z(value), w(value)
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
