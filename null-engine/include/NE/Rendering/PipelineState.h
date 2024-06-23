#pragma once

#include "NE/Core/Core.h"

#include <variant>

namespace null
{
    namespace render
    {
        struct ViewportDynamic
        {
            float x;
            float y;
            float width;
            float height;
            float zMin;
            float zMax;

            ViewportDynamic(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float zMin = 0.0f, float zMax = 1.0f)
                    : x(x), y(y), width(width), height(height), zMin(zMin), zMax(zMax)
            {}
        };
        struct ViewportStatic
        {
            float x;
            float y;
            float width;
            float height;
            float zMin;
            float zMax;

            ViewportStatic(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float zMin = 0.0f, float zMax = 1.0f)
                : x(x), y(y), width(width), height(height), zMin(zMin), zMax(zMax)
            {}
        };

        struct ScissorDynamic
        {
            math::sint32 x;
            math::sint32 y;
            math::uint32 width;
            math::uint32 height;

            ScissorDynamic(math::sint32 x = 0.0f, math::sint32 y = 0.0f, math::uint32 width = 0.0f, math::uint32 height = 0.0f)
                : x(x), y(y), width(width), height(height)
            {}
        };
        struct ScissorStatic
        {
            math::sint32 x;
            math::sint32 y;
            math::uint32 width;
            math::uint32 height;

            ScissorStatic(math::sint32 x = 0.0f, math::sint32 y = 0.0f, math::uint32 width = 0.0f, math::uint32 height = 0.0f)
                : x(x), y(y), width(width), height(height)
            {}
        };

        struct Rasterizer
        {
            float lineWidth = 1.0f;
            PolygonMode polygonMode = PolygonMode::Fill;

            CullMode cullMode = CullMode::Back;
            FaceWinding faceWinding = FaceWinding::Clockwise;

            bool enableDepthClamp = false;
            bool enableRasterizerDiscard = false;

            struct
            {
                float constant = 0.0f;
                float clamp    = 0.0f;
                float slope    = 0.0f;
                bool  enable   = false;
            } depthBias;
        };

        struct Framebuffer
        {
            static inline constexpr math::size s_maxTargets = 8;

            struct Target
            {
                struct BlendState
                {
                    ColourMask  colourWriteMask = ColourMask::None;
                    BlendFactor srcColour       = BlendFactor::One;
                    BlendFactor srcAlpha        = BlendFactor::One;
                    BlendFactor dstColour       = BlendFactor::Zero;
                    BlendFactor dstAlpha        = BlendFactor::Zero;
                    BlendOp     blendOpColour   = BlendOp::Add;
                    BlendOp     blendOpAlpha    = BlendOp::Add;
                    bool enable = false;
                } blendState;
            } targets[s_maxTargets];
        };

        class PipelineState
        {
        public:
            PipelineState();
            ~PipelineState();

            void Init();
        private:
            std::variant<ViewportDynamic, ViewportStatic> m_viewport;
            std::variant<ScissorDynamic, ScissorStatic>   m_scissor;

            Rasterizer m_rasterizer;
            Framebuffer m_framebuffer;
        };
    } // namespace render
} // namespace null
