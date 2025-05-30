#pragma once

#include "NE/Core/Core.h"

namespace null
{
    namespace render
    {
        class RenderPass
        {
        public:
            RenderPass(core::Engine& engine);
            virtual ~RenderPass() = 0;

            virtual void PreInit() {}
            virtual void Init() {}
            virtual void PostInit() {}

            virtual void Destroy() {}

            virtual void PreDraw() {}
            virtual void PostDraw() {}
            virtual void Draw() {}
        protected:
            core::Engine& GetEngine();
            const core::Engine& GetEngine() const;
            system::Window& GetWindow();
            const system::Window& GetWindow() const;
            render::GraphicsDevice& GetGraphicsDevice();
            const render::GraphicsDevice& GetDevice() const;
            system::Input& GetInput();
            const system::Input& GetInput()  const;
        private:
            core::Engine& m_engine;
        };
    } // namespace render
} // namespace null
