#ifndef HELLOTRIANGLE_RENDERPASS_H
#define HELLOTRIANGLE_RENDERPASS_H

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
        private:
            core::Engine& m_engine;
        };
    } // namespace render
} // namespace null

#endif //HELLOTRIANGLE_RENDERPASS_H
