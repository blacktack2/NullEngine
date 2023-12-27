#ifndef HELLOTRIANGLE_PIPELINEMANAGER_H
#define HELLOTRIANGLE_PIPELINEMANAGER_H

#include "NE/Core/Core.h"

#include <vector>

namespace null
{
    namespace render
    {
        class RenderPass;

        /**
         * Description structure for a full render-pipeline.
         */
        struct PipelineDesc
        {
            std::vector<RenderPass*> pipeline;
        };

        /**
         * Handler class for managing the render-pipeline.
         */
        class PipelineManager
        {
        public:
            PipelineManager(core::Engine& engine);
            ~PipelineManager();

            void Init();

            /**
             *
             * @param pipeline
             */
            void SetPipeline(const PipelineDesc& pipeline);

            void Render();
        private:
            core::Engine& m_engine;

            PipelineDesc m_renderPipeline;
        };
    } // namespace render
} // namespace null

#endif //HELLOTRIANGLE_PIPELINEMANAGER_H
