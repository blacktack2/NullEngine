#pragma once

#include "NE/Core/Core.h"

#include <memory>
#include <string>
#include <vector>

namespace null
{
    namespace render
    {
        enum class ShaderStage
        {
            Vertex,
            Fragment,
            TessCont,
            Hull = TessCont,
            TessEval,
            Domain = TessEval,
            Geometry,
            Compute,

            _Max
        };

        class Shader
        {
        public:
            Shader();
            ~Shader();

            bool Init(GraphicsDevice& graphicsDevice, ShaderStage stage, const void* data, math::size dataSize, const char* name);

            ShaderData& GetShaderData()
            {
                return *m_shaderData;
            }
            const ShaderData& GetShaderData() const
            {
                return *m_shaderData;
            }
        private:
            GraphicsDevice* m_graphicsDevice;

            std::unique_ptr<ShaderData> m_shaderData;

            std::string m_name;
            ShaderStage m_stage;
        };

        struct ShaderProgramDesc
        {
            shader_id vertex   = g_nullShaderId;
            shader_id fragment = g_nullShaderId;
            shader_id tessCont = g_nullShaderId;
            shader_id tessEval = g_nullShaderId;
            shader_id geometry = g_nullShaderId;
            shader_id compute  = g_nullShaderId;

            ShaderProgramDesc(shader_id compute)
                : compute(compute)
            {}
            ShaderProgramDesc(shader_id vertex, shader_id fragment)
                : vertex(vertex), fragment(fragment)
            {}
            ShaderProgramDesc(shader_id vertex, shader_id geometry, shader_id fragment)
                    : vertex(vertex), geometry(geometry), fragment(fragment)
            {}
            ShaderProgramDesc(shader_id vertex, shader_id tessCont, shader_id tessEval, shader_id fragment)
                    : vertex(vertex), tessCont(tessCont), tessEval(tessEval), fragment(fragment)
            {}
            ShaderProgramDesc(shader_id vertex, shader_id tessCont, shader_id tessEval, shader_id geometry, shader_id fragment)
                    : vertex(vertex), tessCont(tessCont), tessEval(tessEval), geometry(geometry), fragment(fragment)
            {}
        };

        class ShaderProgram
        {
        public:
            ShaderProgram();
            ~ShaderProgram();
            ShaderProgram(const ShaderProgramDesc& desc);
        private:
            std::vector<Shader*> m_shaders;
        };
    } // namespace render
} // namespace null
