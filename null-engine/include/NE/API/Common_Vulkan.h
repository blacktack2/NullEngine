#ifndef NULLENGINE_COMMON_VULKAN_H
#define NULLENGINE_COMMON_VULKAN_H

#ifdef NE_BUILD_VULKAN

#include <vulkan/vulkan.h>

namespace null
{
    namespace system
    {
        struct DeviceData
        {
            VkInstance instance;
        };
    } // namespace system
} // namespace null

#endif //NE_BUILD_VULKAN

#endif //NULLENGINE_COMMON_VULKAN_H
