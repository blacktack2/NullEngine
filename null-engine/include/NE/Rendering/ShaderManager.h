#pragma once

#include "NE/Core/Core.h"

#include "NE/ShaderList.h"

#include "Shader.h"

#include <vector>
#include <unordered_map>

namespace null
{
    namespace render
    {
        class ShaderManager
        {
        public:
            ShaderManager(core::Engine& engine);
            ~ShaderManager();

            bool Init();

            Shader* GetShader(ShaderId shader);
            ShaderProgram* GetShaderProgram(const ShaderProgramDesc& desc);
        private:
            core::Engine& m_engine;

            Shader m_shaders[(shader_id)ShaderId::_Max];
            std::unordered_map<math::uint64, ShaderProgram*> m_shaderPrograms;
        };
    } // namespace render
} // namespace null
