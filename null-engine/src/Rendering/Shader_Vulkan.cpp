#include "NE/Rendering/Shader.h"

#ifdef NE_BUILD_VULKAN

#include "NE/API/Common_Vulkan.h"
#include "NE/Rendering/GraphicsDevice.h"

VkShaderStageFlagBits NeStageToVulkan(null::render::ShaderStage stage)
{
    switch (stage)
    {
        default:
            null::debug::AssertFail("Unsupported shader stage '%d'", (int)stage);
            return VK_SHADER_STAGE_VERTEX_BIT;
        case null::render::ShaderStage::Vertex   : return VK_SHADER_STAGE_VERTEX_BIT;
        case null::render::ShaderStage::Fragment : return VK_SHADER_STAGE_FRAGMENT_BIT;
        case null::render::ShaderStage::TessCont : return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case null::render::ShaderStage::TessEval : return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case null::render::ShaderStage::Geometry : return VK_SHADER_STAGE_GEOMETRY_BIT;
        case null::render::ShaderStage::Compute  : return VK_SHADER_STAGE_COMPUTE_BIT;
    }
}

null::render::Shader::Shader()
    :
    m_shaderData(nullptr)
{

}

null::render::Shader::~Shader()
{
    if (m_shaderData)
    {
    }
}

bool null::render::Shader::Init(GraphicsDevice& graphicsDevice, null::render::ShaderStage stage, const void* data, null::math::size dataSize, const char* name)
{
    m_graphicsDevice = &graphicsDevice;
    m_shaderData = std::make_unique<ShaderData>();
    m_stage = stage;
    m_name = name;

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = dataSize;
    createInfo.pCode = (math::uint32*)data;

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(m_graphicsDevice->GetGraphicsDeviceData().device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        debug::AssertFail("Failed to create shader '%s'\n", name);
        return false;
    }

    VkPipelineShaderStageCreateInfo stageInfo{};
    stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stageInfo.stage = NeStageToVulkan(m_stage);
    stageInfo.module = shaderModule;
    stageInfo.pName = "main";

    vkDestroyShaderModule(m_graphicsDevice->GetGraphicsDeviceData().device, shaderModule, nullptr);

    return true;
}

null::render::ShaderProgram::ShaderProgram()
{

}

null::render::ShaderProgram::~ShaderProgram()
{

}

null::render::ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
    if (desc.compute)
    {
        debug::Assert(
                !(IsShaderIdNull(desc.vertex) || IsShaderIdNull(desc.fragment) || IsShaderIdNull(desc.tessCont) || IsShaderIdNull(desc.tessEval) || IsShaderIdNull(desc.geometry)),
                "Compute shaders are not compatible with other stages. Other stages will be ignored\n"
                );
        debug::AssertFail("Not implemented\n");
    }
    else
    {
        debug::Assert(desc.vertex, "Vertex shaders are required for non-compute shaders\n");
        debug::Assert(IsShaderIdNull(desc.tessCont) == IsShaderIdNull(desc.tessEval), "Must have both or neither of each tesselation stage\n");
    }
}

#endif //NE_BUILD_VULKAN
