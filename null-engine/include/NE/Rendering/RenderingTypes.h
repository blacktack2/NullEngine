#pragma once

#include "NE/Math/MathTypes.h"

#include "NE/Util/Enum.h"

namespace null
{
    typedef null::math::size shader_id;
    constexpr shader_id g_nullShaderId = std::numeric_limits<shader_id>::max();

    namespace render
    {
        class RenderPass;

        struct PipelineDesc;
        class PipelineManager;

        struct MeshDesc;
        class Mesh;

        struct ShaderData;
        class Shader;
        struct ShaderProgramDesc;
        class ShaderProgram;

        /**
         * Enumeration covering the valid index buffer strides. The value of each type corresponds to the actual
         * stride in bytes.
         */
        enum class IndexType : math::size
        {
            Uint8  = sizeof(math::uint8),
            Uint16 = sizeof(math::uint16),
            Uint32 = sizeof(math::uint32),
            Uint64 = sizeof(math::uint64),
        };
        /**
         * Enumeration covering the valid formats vertex data can take to form primitives.
         * If the loaded graphics API does not support a requested primitive type PointList will be used by default
         * and an assert will be thrown (no errors will be thrown so take caution around this event). Most of these
         * should be supported by most APIs though, so this is unlikely to be an issue (and I will try document any
         * exceptions that I implement for).
         */
        enum class PrimitiveType : math::uint8
        {
            // Every vertex forms a point.
            PointList = 0,
            // Every distinct pair of vertices form a line with no overlap (vertices 0-1 form the first, vertices
            // 2-3 form the second, etc.).
            LineList,
            // Every consecutive pair vertices form a line (vertices 0-1 form the first, vertices 1-2 form the
            // second, etc.).
            LineStrip,
            // As with LineStrip but the first and final vertices also form a line.
            // UNSUPPORTED: Vulkan
            LineLoop,
            // Every distinct trio of vertices form a triangle with no overlap (vertices 0-2 form the first,
            // vertices 3-5 form the second, etc.).
            TriangleList,
            // Every consecutive trios vertices form a triangle (vertices 0-2 form the first, vertices 1-3 form the
            // second, ect.).
            TriangleStrip,
            // Every consecutive pair of vertices form a triangle with vertex 0 (vertices 0,1,2 form the first,
            // vertices 0,2,3 form the second, etc.).
            TriangleFan,
            // Every distinct set of four vertices form a quad with no overlap (vertices 0-3 form the first,
            // vertices 4-7 form the second, etc.).
            QuadList,
            // Every set of four vertices starting from an even index for, a quad (vertices 0-3 form the first,
            // vertices 2-5 form the second, etc.).
            QuadStrip,
            // Similar to LineList, TriangleList, and QuadList every distinct set of N vertices will form a
            // primitive with no overlap, where N is a user defined constant (see
            // null::system::Device::SetPatchCount).
            PatchList,

            _Max
        };

        enum class PolygonMode : math::uint8
        {
            Fill = 0,
            Line,
            Point,

            _Max
        };

        enum class CullMode : math::uint8
        {
            None = 0,
            Front,
            Back,
            Both,

            _Max
        };

        enum class FaceWinding : math::uint8
        {
            Clockwise = 0,
            AntiClockwise,

            _Max
        };

        NE_ENUM_BITMASK_BEGIN(ColourMask, math::uint8)
        {
            None = 0,
            R = 1 << 0,
            G = 1 << 1,
            B = 1 << 2,
            A = 1 << 3,

            RG = R | G,
            RB = R | B,
            RA = R | A,
            GB = G | B,
            GA = G | A,
            BA = B | A,

            RGB = R | G | B,
            RGA = R | B | A,
            RBA = R | B | A,
            GBA = G | B | A,

            RGBA = R | G | B | A,
        };
        NE_ENUM_BITMASK_END(ColourMask, math::uint8)

        enum class BlendFactor : math::uint8
        {
            Zero = 0,
            One,
            SrcColour,
            SrcColourInv,
            DstColour,
            DstColourInv,
            SrcAlpha,
            SrcAlphaInv,
            DstAlpha,
            DstAlphaInv,
            ConstColour,
            ConstColourInv,
            ConstAlpha,
            ConstAlphaInv,
            SrcAlphaSaturate,
            Src1Colour,
            Src1ColourInv,
            Src1Alpha,
            Src1AlphaInv,

            _Max
        };

        enum class BlendOp : math::uint8
        {
            Add = 0,
            Subtract,
            SubtractInv,
            Min,
            Max,

            _Max
        };

        inline bool IsShaderIdNull(shader_id id)
        {
            return id == g_nullShaderId;
        }
    } // namespace render
} // namespace null
