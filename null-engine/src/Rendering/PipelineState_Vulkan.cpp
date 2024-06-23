#include "NE/Rendering/PipelineState.h"

#include "NE/API/Common_Vulkan.h"
#include "NE/Core/Variant.h"

null::render::PipelineState::PipelineState()
{

}

null::render::PipelineState::~PipelineState()
{

}

void null::render::PipelineState::Init()
{
    std::vector<VkDynamicState> dynamicStates{};

    VkViewport viewport{};
    std::visit(VariantVisitor(
        [&viewport](const auto& vp)
        {
            viewport.x        = vp.x;
            viewport.y        = vp.y;
            viewport.width    = vp.width;
            viewport.height   = vp.height;
            viewport.minDepth = vp.zMin;
            viewport.maxDepth = vp.zMax;
        }
    ), m_viewport);
    std::visit(VariantVisitor(
        [&dynamicStates](const ViewportDynamic& vp) { dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT); },
        [&dynamicStates](const ViewportStatic&  vp) {}
    ), m_viewport);

    VkRect2D scissor{};
    std::visit(VariantVisitor(
        [&scissor](const auto& sc)
        {
            scissor.offset = { sc.x, sc.y };
            scissor.extent = { sc.width, sc.height };
        }
    ), m_scissor);
    std::visit(VariantVisitor(
            [&dynamicStates](const ScissorDynamic& vp) { dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR); },
            [&dynamicStates](const ScissorStatic&  vp) {}
    ), m_scissor);

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = dynamicStates.size();
    dynamicState.pDynamicStates    = dynamicStates.data();

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports    = &viewport;
    viewportState.scissorCount  = 1;
    viewportState.pScissors     = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable        = m_rasterizer.enableDepthClamp;
    rasterizer.rasterizerDiscardEnable = m_rasterizer.enableRasterizerDiscard;
    rasterizer.polygonMode             = NullPolygonModeToVulkan(m_rasterizer.polygonMode);
    rasterizer.lineWidth               = m_rasterizer.lineWidth;
    rasterizer.frontFace               = NullFaceWindingToVulkan(m_rasterizer.faceWinding);
    rasterizer.depthBiasEnable         = m_rasterizer.depthBias.enable;
    rasterizer.depthBiasConstantFactor = m_rasterizer.depthBias.constant;
    rasterizer.depthBiasClamp          = m_rasterizer.depthBias.clamp;
    rasterizer.depthBiasSlopeFactor    = m_rasterizer.depthBias.slope;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable   = VK_FALSE;
    multisampling.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading      = 1.0f;
    multisampling.pSampleMask           = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable      = VK_FALSE;

    VkPipelineColorBlendAttachmentState colorBlendAttachments[Framebuffer::s_maxTargets];

    for (math::uint32 i = 0; i < Framebuffer::s_maxTargets; ++i)
    {
        auto& target = m_framebuffer.targets[i];
        auto& blendState = target.blendState;

        colorBlendAttachments[i].colorWriteMask      = NullColourMaskToVulkan(blendState.colourWriteMask);
        colorBlendAttachments[i].blendEnable         = blendState.enable;
        colorBlendAttachments[i].srcColorBlendFactor = NullBlendFactorToVulkan(blendState.srcColour);
        colorBlendAttachments[i].dstColorBlendFactor = NullBlendFactorToVulkan(blendState.dstColour);
        colorBlendAttachments[i].colorBlendOp        = NullBlendOpToVulkan(blendState.blendOpColour);
        colorBlendAttachments[i].srcAlphaBlendFactor = NullBlendFactorToVulkan(blendState.srcAlpha);
        colorBlendAttachments[i].dstAlphaBlendFactor = NullBlendFactorToVulkan(blendState.dstAlpha);
        colorBlendAttachments[i].alphaBlendOp        = NullBlendOpToVulkan(blendState.blendOpAlpha);
    }

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = Framebuffer::s_maxTargets;
    colorBlending.pAttachments = colorBlendAttachments;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;
}
