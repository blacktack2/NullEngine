#version 460 core

layout(location = 0) in FragmentIn
{
    vec3 colour;
} fgmIn;

layout(location = 0) out vec4 colour0;

void main()
{
    colour0 = vec4(fgmIn.colour, 1.0f);
}
