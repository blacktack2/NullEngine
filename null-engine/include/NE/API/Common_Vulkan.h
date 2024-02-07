#ifndef NULLENGINE_COMMON_VULKAN_H
#define NULLENGINE_COMMON_VULKAN_H

#ifdef NE_BUILD_VULKAN

#include <vulkan/vulkan.h>

#include <vector>

namespace null
{
    namespace system
    {
        struct DeviceData
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
#ifdef NE_DEBUG
            VkDebugUtilsMessengerEXT debugMessenger;
#endif //NE_DEBUG
        };
        struct WindowDeviceData
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
} // namespace null

#endif //NE_BUILD_VULKAN

#endif //NULLENGINE_COMMON_VULKAN_H
