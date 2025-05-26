#include "NE/Rendering/ShaderManager.h"

#include "NE/Core/Engine.h"

#include <fstream>
#include <filesystem>

null::render::ShaderManager::ShaderManager(core::Engine& engine)
    : m_engine(engine)
{
}

null::render::ShaderManager::~ShaderManager()
{

}

bool null::render::ShaderManager::Init()
{
    for (shader_id i = 0; i < (shader_id)ShaderId::_Max; ++i)
    {
        ShaderSourceDesc& source = g_shaderSources[i];

        std::ifstream stream{source.sourceFile, std::ios::ate | std::ios::binary};
        if (!stream)
        {
            debug::AssertFail("Failed to open shader file '%s'", source.sourceFile);
            return false;
        }

        math::size fileSize = stream.tellg();
        std::vector<char> data;
        data.resize(fileSize);

        stream.seekg(0);
        stream.read(data.data(), fileSize);

        m_shaders[i].Init(m_engine.GetGraphicsDevice(), source.stage, data.data(), data.size(), std::filesystem::path(source.sourceFile).filename().c_str());
    }
    return true;
}

null::render::Shader *null::render::ShaderManager::GetShader(ShaderId shader)
{
    return &m_shaders[(shader_id)shader];
}

null::render::ShaderProgram* null::render::ShaderManager::GetShaderProgram(const null::render::ShaderProgramDesc& desc)
{
    math::uint64 programID = 0;
    // This implementation leaves room for a total of 1023 shaders.
    if (desc.vertex   != g_nullShaderId) programID |= (desc.vertex   & 0x03FF) <<  0;
    if (desc.fragment != g_nullShaderId) programID |= (desc.fragment & 0x03FF) << 10;
    if (desc.tessCont != g_nullShaderId) programID |= (desc.tessCont & 0x03FF) << 20;
    if (desc.tessEval != g_nullShaderId) programID |= (desc.tessEval & 0x03FF) << 30;
    if (desc.geometry != g_nullShaderId) programID |= (desc.geometry & 0x03FF) << 40;
    if (desc.compute  != g_nullShaderId) programID |= (desc.compute  & 0x03FF) << 50;

    auto progItr = m_shaderPrograms.find(programID);
    if (progItr == m_shaderPrograms.end())
    {
        progItr->second = new ShaderProgram(desc);
    }
    return progItr->second;
}
