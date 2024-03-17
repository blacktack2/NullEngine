#version 460 core

const vec2 g_positions[3] = vec2[]
(
    vec2( 0.0f, -0.5f),
    vec2( 0.5f,  0.5f),
    vec2(-0.5f,  0.5f)
);
const vec3 g_colours[3] = vec3[]
(
    vec3(1.0f, 0.0f, 0.0f),
    vec3(0.0f, 1.0f, 0.0f),
    vec3(0.0f, 0.0f, 1.0f)
);

layout(location = 0) out VertexOut
{
    vec3 colour;
} vtxOut;

void main()
{
    gl_Position = vec4(g_positions[gl_VertexIndex], 0.0f, 1.0f);
    vtxOut.colour = g_colours[gl_VertexIndex];
}
