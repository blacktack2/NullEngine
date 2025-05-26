#pragma once

#ifdef NE_BUILD_VULKAN

#include "NE/Core/Core.h"

#include <vulkan/vulkan.h>

#include <vector>

namespace null
{
    namespace system
    {
        struct GraphicsDeviceData
        {
            VkInstance               instance;
            VkPhysicalDevice         physicalDevice = VK_NULL_HANDLE;
            VkDevice                 device;
            VkSurfaceKHR             surface;
            VkQueue                  graphicsQueue;
            VkQueue                  presentQueue;
            VkSwapchainKHR           swapChain;
            std::vector<VkImage>     swapChainImages;
            std::vector<VkImageView> swapChainImageViews;
            VkFormat                 swapChainImageFormat;
            VkExtent2D               swapChainExtent;
            VkPipelineLayout         pipelineLayout;
#ifdef NE_DEBUG
            VkDebugUtilsMessengerEXT debugMessenger;
#endif //NE_DEBUG
        };
        struct WindowGraphicsDeviceData
        {
            std::vector<const char*> requiredExtensions;
        };

        static const char* VulkanDebugSeverityToString(VkDebugUtilsMessageSeverityFlagBitsEXT severity)
        {
            switch (severity)
            {
            default: return "UNKNOWN";
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT : return "VERBOSE";
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    : return "INFO";
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT : return "WARNING";
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   : return "ERROR";
            }
        }

        static const char* VulkanDebugTypeToString(VkDebugUtilsMessageTypeFlagsEXT type)
        {
            switch (type)
            {
            default: return "UNKNOWN";
            case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT     : return "GENERAL";
            case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  : return "VALIDATION";
            case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT : return "PERFORMANCE";
            }
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
                                                            void* userData)
        {
            core::Engine* engine = static_cast<core::Engine*>(userData);

            if (messageSeverity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
            {
                null::debug::Message("Vulkan error: severity=%s | type=%s | message=%s",
                                     null::system::VulkanDebugSeverityToString(messageSeverity),
                                     null::system::VulkanDebugTypeToString(messageType),
                                     callbackData->pMessage
                );
            }
            else
            {
                null::debug::AssertFail("Vulkan error: severity=%s | type=%s | message=%s\n",
                                        null::system::VulkanDebugSeverityToString(messageSeverity),
                                        null::system::VulkanDebugTypeToString(messageType),
                                        callbackData->pMessage
                );
            }

            return VK_FALSE;
        }
    } // namespace system
    namespace render
    {
        struct ShaderData
        {
        };

        inline VkPrimitiveTopology NullPrimitiveToVulkan(PrimitiveType primitive)
        {
            switch (primitive)
            {
                case PrimitiveType::LineLoop  :
                case PrimitiveType::QuadList  :
                case PrimitiveType::QuadStrip :
                    debug::AssertFail("Primitive type %d not supported in Vulkan. Defaulting to triangle list", (int)primitive);
                    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                default:
                    debug::AssertFail("Unknown primitive type %d. Defaulting to triangle list", (int)primitive);
                    return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

                case PrimitiveType::PointList     : return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
                case PrimitiveType::LineList      : return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
                case PrimitiveType::LineStrip     : return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
                case PrimitiveType::TriangleList  : return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                case PrimitiveType::TriangleStrip : return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
                case PrimitiveType::TriangleFan   : return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
                case PrimitiveType::PatchList     : return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
            }
        }

        inline VkPolygonMode NullPolygonModeToVulkan(PolygonMode mode)
        {
            switch (mode)
            {
                default:
                    debug::AssertFail("Unknown mode type %d. Defaulting to fill", (int)mode);
                    return VK_POLYGON_MODE_FILL;

                case PolygonMode::Fill  : return VK_POLYGON_MODE_FILL;
                case PolygonMode::Line  : return VK_POLYGON_MODE_LINE;
                case PolygonMode::Point : return VK_POLYGON_MODE_POINT;
            }
        }

        inline VkFrontFace NullFaceWindingToVulkan(FaceWinding winding)
        {
            switch (winding)
            {
                default:
                    debug::AssertFail("Unknown winding type %d. Defaulting to clockwise", (int)winding);
                    return VK_FRONT_FACE_CLOCKWISE;

                case FaceWinding::Clockwise     : return VK_FRONT_FACE_CLOCKWISE;
                case FaceWinding::AntiClockwise : return VK_FRONT_FACE_COUNTER_CLOCKWISE;
            }
        }

        inline VkColorComponentFlagBits NullColourMaskToVulkan(ColourMask mask)
        {
            return (VkColorComponentFlagBits)(
                (~(mask & ColourMask::R) ? (int)VK_COLOR_COMPONENT_R_BIT : 0) |
                (~(mask & ColourMask::G) ? (int)VK_COLOR_COMPONENT_G_BIT : 0) |
                (~(mask & ColourMask::B) ? (int)VK_COLOR_COMPONENT_B_BIT : 0) |
                (~(mask & ColourMask::A) ? (int)VK_COLOR_COMPONENT_A_BIT : 0)
            );
        }

        inline VkBlendFactor NullBlendFactorToVulkan(BlendFactor blend)
        {
            switch (blend)
            {
                default:
                    debug::AssertFail("Unknown blend factor %d. Defaulting to zero", (int)blend);
                    return VK_BLEND_FACTOR_ZERO;

                case BlendFactor::Zero             : return VK_BLEND_FACTOR_ZERO;
                case BlendFactor::One              : return VK_BLEND_FACTOR_ONE;
                case BlendFactor::SrcColour        : return VK_BLEND_FACTOR_SRC_COLOR;
                case BlendFactor::SrcColourInv     : return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
                case BlendFactor::DstColour        : return VK_BLEND_FACTOR_DST_COLOR;
                case BlendFactor::DstColourInv     : return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
                case BlendFactor::SrcAlpha         : return VK_BLEND_FACTOR_SRC_ALPHA;
                case BlendFactor::SrcAlphaInv      : return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
                case BlendFactor::DstAlpha         : return VK_BLEND_FACTOR_DST_ALPHA;
                case BlendFactor::DstAlphaInv      : return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
                case BlendFactor::ConstColour      : return VK_BLEND_FACTOR_CONSTANT_COLOR;
                case BlendFactor::ConstColourInv   : return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
                case BlendFactor::ConstAlpha       : return VK_BLEND_FACTOR_CONSTANT_ALPHA;
                case BlendFactor::ConstAlphaInv    : return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
                case BlendFactor::SrcAlphaSaturate : return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
                case BlendFactor::Src1Colour       : return VK_BLEND_FACTOR_SRC1_COLOR;
                case BlendFactor::Src1ColourInv    : return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
                case BlendFactor::Src1Alpha        : return VK_BLEND_FACTOR_SRC1_ALPHA;
                case BlendFactor::Src1AlphaInv     : return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
            }
        }

        inline VkBlendOp NullBlendOpToVulkan(BlendOp op)
        {
            switch (op)
            {
                default:
                    debug::AssertFail("Unknown blend operation %d. Defaulting to add", (int)op);
                    return VK_BLEND_OP_ADD;

                case BlendOp::Add         : return VK_BLEND_OP_ADD;
                case BlendOp::Subtract    : return VK_BLEND_OP_SUBTRACT;
                case BlendOp::SubtractInv : return VK_BLEND_OP_REVERSE_SUBTRACT;
                case BlendOp::Min         : return VK_BLEND_OP_MIN;
                case BlendOp::Max         : return VK_BLEND_OP_MAX;
            }
        }
    }
} // namespace null

#endif //NE_BUILD_VULKAN
