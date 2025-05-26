#include "NE/Rendering/RenderPass.h"

#include "NE/Core/Engine.h"

null::render::RenderPass::RenderPass(null::core::Engine &engine)
    : m_engine(engine)
{

}

null::render::RenderPass::~RenderPass()
{

}

null::core::Engine &null::render::RenderPass::GetEngine()
{
    return m_engine;
}

const null::core::Engine &null::render::RenderPass::GetEngine() const
{
    return m_engine;
}

null::system::Window &null::render::RenderPass::GetWindow()
{
    return m_engine.GetWindow();
}

const null::system::Window &null::render::RenderPass::GetWindow() const
{
    return m_engine.GetWindow();
}

null::render::GraphicsDevice &null::render::RenderPass::GetGraphicsDevice()
{
    return m_engine.GetGraphicsDevice();
}

const null::render::GraphicsDevice &null::render::RenderPass::GetDevice() const
{
    return m_engine.GetDevice();
}

null::system::Input &null::render::RenderPass::GetInput()
{
    return m_engine.GetInput();
}

const null::system::Input &null::render::RenderPass::GetInput() const
{
    return m_engine.GetInput();
}
