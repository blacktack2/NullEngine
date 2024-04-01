#pragma once

#include "NE/Math/MathTypes.h"

namespace null
{
    typedef null::math::size shader_id;
    constexpr shader_id g_nullShaderId = std::numeric_limits<shader_id>::max();

    namespace render
    {
        class RenderPass;

        struct PipelineDesc;
        class PipelineManager;

        struct MeshDesc;
        class Mesh;

        struct ShaderData;
        class Shader;
        struct ShaderProgramDesc;
        class ShaderProgram;
    } // namespace render
} // namespace null
