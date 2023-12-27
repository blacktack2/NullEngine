#include "NE/Rendering/PipelineManager.h"

#include "NE/Core/Engine.h"

#include "NE/Rendering/RenderPass.h"

null::render::PipelineManager::PipelineManager(null::core::Engine &engine)
    : m_engine(engine)
{

}

null::render::PipelineManager::~PipelineManager()
{

}

void null::render::PipelineManager::Init()
{

}

void null::render::PipelineManager::SetPipeline(const PipelineDesc& pipeline)
{
    // Clean up old pipeline
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->Destroy();
    }

    m_renderPipeline = pipeline;

    // Initialize new pipeline
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->PreInit();
    }
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->Init();
    }
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->PostInit();
    }
}

void null::render::PipelineManager::Render()
{
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->PreDraw();
    }
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->Draw();
    }
    for (RenderPass* pass : m_renderPipeline.pipeline)
    {
        pass->PostDraw();
    }
}
