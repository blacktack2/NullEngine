#include "NE/Rendering/GraphicsDevice.h"

#ifdef NE_BUILD_VULKAN

#include "NE/API/Common_Vulkan.h"

#include "NE/Core/Engine.h"

#include "NE/Util/Enum.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <limits>
#include <optional>
#include <vector>

NE_ENUM_ENUMERATOR_BEGIN(QueueFamily, null::math::uint32)
{
    GraphicsFamily = 0,
    PresentationFamily,
    _Max
};
NE_ENUM_ENUMERATOR_END(QueueFamily, null::math::uint32)

struct QueueFamilySet
{
    std::array<std::optional<null::math::uint32>, (null::math::size)QueueFamily::_Max> queueFamilies;

    bool IsValid()
    {
        for (const auto& queueFamily : queueFamilies)
        {
            if (!queueFamily.has_value())
            {
                return false;
            }
        }
        return true;
    }
};

struct SwapChainSupportData
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

const char constexpr* validationLayers[] =
{
#ifdef NE_DEBUG
    "VK_LAYER_KHRONOS_validation"
#endif //NE_DEBUG
};


const char constexpr* requiredDeviceExtensions[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

bool CheckValidationLayerSupport()
#ifdef NE_DEBUG
{
    null::math::uint32 layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers)
    {
        bool layerFound = false;

        for (const VkLayerProperties& layerProperties : availableLayers)
        {
            if (std::strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            null::debug::AssertFail("Vulkan validation layer [%s] requested, but not available.", layerName);
            return false;
        }
    }

    return true;
}
#else
{
    return true;
}
#endif //NE_DEBUG

QueueFamilySet GetDeviceQueueFamilies(null::render::GraphicsDeviceData& graphicsDeviceData)
{
    null::math::uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(graphicsDeviceData.physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(graphicsDeviceData.physicalDevice, &queueFamilyCount, queueFamilies.data());

    QueueFamilySet queueFamilySet;

    for (null::math::size i = 0; i < queueFamilyCount; ++i)
    {
        const VkQueueFamilyProperties& queueFamily = queueFamilies[i];
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily] = i;
        }
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(graphicsDeviceData.physicalDevice, i, graphicsDeviceData.surface, &presentSupport);
        if (presentSupport)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily] = i;
        }
    }

    return queueFamilySet;
}

VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const VkSurfaceFormatKHR& format : availableFormats)
    {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
        {
            return format;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    for (const VkPresentModeKHR& presentMode : availablePresentModes)
    {
        if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return presentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D ChooseSwapExtent(const null::system::Window& window, const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width == std::numeric_limits<null::math::uint32>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        VkExtent2D actualExtent =
        {
            (null::math::uint32)window.GetWidth(),
            (null::math::uint32)window.GetHeight()
        };

        actualExtent.width  = std::clamp(actualExtent.width,  capabilities.minImageExtent.width,  capabilities.maxImageExtent.width );
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

SwapChainSupportData GetSwapChainSupport(null::render::GraphicsDeviceData& graphicsDeviceData)
{
    SwapChainSupportData data;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(graphicsDeviceData.physicalDevice, graphicsDeviceData.surface, &data.capabilities);

    null::math::uint32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(graphicsDeviceData.physicalDevice, graphicsDeviceData.surface, &formatCount, nullptr);
    if (formatCount > 0)
    {
        data.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(graphicsDeviceData.physicalDevice, graphicsDeviceData.surface, &formatCount, data.formats.data());
    }

    null::math::uint32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(graphicsDeviceData.physicalDevice, graphicsDeviceData.surface, &presentModeCount, nullptr);
    if (formatCount > 0)
    {
        data.presentModes.resize(formatCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(graphicsDeviceData.physicalDevice, graphicsDeviceData.surface, &presentModeCount, data.presentModes.data());
    }

    return data;
}

bool CreateSwapChain(null::render::GraphicsDeviceData& graphicsDeviceData, const null::system::Window& window, QueueFamilySet& queueFamilySet)
{
    VkResult result;

    SwapChainSupportData swapChainSupport = GetSwapChainSupport(graphicsDeviceData);

    VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR  presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = ChooseSwapExtent(window, swapChainSupport.capabilities);

    null::math::uint32 imageCount = std::clamp(
        swapChainSupport.capabilities.minImageCount + 1,
        swapChainSupport.capabilities.minImageCount,
        swapChainSupport.capabilities.maxImageCount > 0 ? swapChainSupport.capabilities.maxImageCount : null::math::NE_MAX_U32
    );

    null::math::uint32 queueFamilyIndices[] = {
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily].value(),
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily].value(),
    };

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = graphicsDeviceData.surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily] == queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily])
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    result = vkCreateSwapchainKHR(graphicsDeviceData.device, &createInfo, nullptr, &graphicsDeviceData.swapChain);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create Vulkan swapchain\n");
        return false;
    }

    result = vkGetSwapchainImagesKHR(graphicsDeviceData.device, graphicsDeviceData.swapChain, &imageCount, nullptr);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to get swapchain image count\n");
        return false;
    }
    graphicsDeviceData.swapChainImages.resize(imageCount);
    result = vkGetSwapchainImagesKHR(graphicsDeviceData.device, graphicsDeviceData.swapChain, &imageCount, graphicsDeviceData.swapChainImages.data());
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to get swapchain images\n");
        return false;
    }

    graphicsDeviceData.swapChainImageFormat = surfaceFormat.format;
    graphicsDeviceData.swapChainExtent = extent;

    return true;
}

bool CreateSwapChainViews(null::render::GraphicsDeviceData& graphicsDeviceData)
{
    VkResult result;

    graphicsDeviceData.swapChainImageViews.resize(graphicsDeviceData.swapChainImages.size());

    for (null::math::size i = 0; i < graphicsDeviceData.swapChainImageViews.size(); ++i)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image    = graphicsDeviceData.swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format   = graphicsDeviceData.swapChainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel   = 0;
        createInfo.subresourceRange.levelCount     = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount     = 1;
        result = vkCreateImageView(graphicsDeviceData.device, &createInfo, nullptr, &graphicsDeviceData.swapChainImageViews[i]);
        if (result != VK_SUCCESS)
        {
            null::debug::AssertFail("Failed to create view for swapchain image %u\n", i);
            return false;
        }
    }

    return true;
}

bool GetInstanceExtensions(std::vector<std::string>& extensions)
{
    VkResult result;

    null::math::uint32 extensionCount;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to retrieve extension count from Vulkan\n");
        return false;
    }
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to retrieve extension names from Vulkan\n");
        return false;
    }

    extensions = std::vector<std::string>(extensionCount);
    for (null::math::uint32 i = 0; i < extensionCount; ++i)
    {
        extensions[i] = extensionProperties[i].extensionName;
    }
#ifdef NE_DEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif //NE_DEBUG

    return true;
}

bool GetDeviceExtensions(VkPhysicalDevice& physicalDevice, std::vector<std::string>& extensions)
{
    VkResult result;

    extensions.clear();

    null::math::uint32 extensionCount;
    result = vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to retrieve available extension count\n");
        return false;
    }

    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    result = vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensionProperties.data());
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to retrieve available extensions\n");
        return false;
    }

    for (null::math::size i = 0; i < extensionCount; ++i)
    {
        extensions.push_back(extensionProperties[i].extensionName);
    }

    return true;
}

bool AreExtensionsSupported(const std::vector<std::string>& deviceExtensions)
{
    for (std::string_view requiredExt : requiredDeviceExtensions)
    {
        bool isAvailable = false;
        for (std::string_view deviceExt : deviceExtensions)
        {
            if (requiredExt == deviceExt)
            {
                isAvailable = true;
                break;
            }
        }
        if (!isAvailable)
        {
            null::debug::AssertFail("Vulkan extension [%s] not supported by device\n", requiredExt);
            return false;
        }
    }

    return true;
}

bool IsDeviceSuitable(null::render::GraphicsDeviceData& graphicsDeviceData, const std::vector<std::string>& deviceExtensions)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(graphicsDeviceData.physicalDevice, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(graphicsDeviceData.physicalDevice, &deviceFeatures);

    if (!AreExtensionsSupported(deviceExtensions))
    {
        null::debug::AssertFail("Logical device extensions not supported.\n");
        return false;
    }

    SwapChainSupportData swapChainSupport = GetSwapChainSupport(graphicsDeviceData);
    if (swapChainSupport.formats.empty() || swapChainSupport.presentModes.empty())
    {
        null::debug::AssertFail("Swap-chain not supported.\n");
        return false;
    }

    return true;
}

bool CreateInstance(null::render::GraphicsDeviceData& graphicsDeviceData, const char* applicationName, const std::vector<std::string>& instanceExtensions)
{
    if (!CheckValidationLayerSupport())
    {
        null::debug::AssertFail("Required validation layer is not available.\n");
        return false;
    }

    VkResult result;

    VkApplicationInfo appInfo;
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext              = nullptr;
    appInfo.pApplicationName   = applicationName;
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.pEngineName        = "Null-Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_3;

    std::vector<const char*> extensions(instanceExtensions.size());
    for (null::math::size i = 0; i < instanceExtensions.size(); ++i)
    {
        extensions[i] = instanceExtensions[i].c_str();
    }
    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext                   = nullptr;
    instanceCreateInfo.flags                   = 0;
    instanceCreateInfo.pApplicationInfo        = &appInfo;
    instanceCreateInfo.enabledLayerCount       = (sizeof(validationLayers) / sizeof(const char*));
    instanceCreateInfo.ppEnabledLayerNames     = validationLayers;
    instanceCreateInfo.enabledExtensionCount   = extensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

    result = vkCreateInstance(&instanceCreateInfo, nullptr, &graphicsDeviceData.instance);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create Vulkan instance\n");
        return false;
    }

    return true;
}

#ifdef NE_DEBUG
bool SetupDebugMessenger(null::render::GraphicsDeviceData& graphicsDeviceData, void* userData)
{
    VkResult result;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity =
//            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = null::render::DebugCallback;
    debugCreateInfo.pUserData = &userData;

    auto debugMessengerCreate = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(graphicsDeviceData.instance, "vkCreateDebugUtilsMessengerEXT"));
    if (debugMessengerCreate)
    {
        result = debugMessengerCreate(graphicsDeviceData.instance, &debugCreateInfo, nullptr, &graphicsDeviceData.debugMessenger);
        if (result != VK_SUCCESS)
        {
            null::debug::AssertFail("Failed to assign Vulkan debug callback\n");
            return false;
        }
    }
    else
    {
        null::debug::AssertFail("Missing extension for Vulkan debug callback\n");
        return false;
    }

    return true;
}
#endif //NE_DEBUG

bool SelectPhysicalDevice(null::render::GraphicsDeviceData& graphicsDeviceData, const std::vector<std::string>& instanceExtensions, std::vector<std::string>& deviceExtensions)
{
    null::math::uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(graphicsDeviceData.instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        null::debug::AssertFail("Failed to find GPUs with Vulkan support\n");
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(graphicsDeviceData.instance, &deviceCount, devices.data());

    for (VkPhysicalDevice& device : devices)
    {
        graphicsDeviceData.physicalDevice = device;
        GetDeviceExtensions(device, deviceExtensions);

        if (IsDeviceSuitable(graphicsDeviceData, deviceExtensions))
        {
            graphicsDeviceData.physicalDevice = device;
            break;
        }
        graphicsDeviceData.physicalDevice = VK_NULL_HANDLE;
    }

    if (graphicsDeviceData.physicalDevice == VK_NULL_HANDLE)
    {
        null::debug::AssertFail("Failed to find a suitable GPU\n");
        return false;
    }

    return true;
}

bool CreateLogicalDevice(null::render::GraphicsDeviceData& graphicsDeviceData, QueueFamilySet& queueFamilySet)
{
    VkResult result;

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    float queuePriority = 1.0f;
    for (std::optional<null::math::uint32> queueFamily : queueFamilySet.queueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily.value();
        queueCreateInfo.queueCount       = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos       = queueCreateInfos.data();
    createInfo.queueCreateInfoCount    = queueCreateInfos.size();
    createInfo.pEnabledFeatures        = &deviceFeatures;
    createInfo.enabledExtensionCount   = sizeof(requiredDeviceExtensions) / sizeof(const char*);
    createInfo.ppEnabledExtensionNames = requiredDeviceExtensions;

    result = vkCreateDevice(graphicsDeviceData.physicalDevice, &createInfo, nullptr, &graphicsDeviceData.device);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create logical device\n");
        return false;
    }

    return true;
}

bool CreatePipelineLayout(null::render::GraphicsDeviceData& graphicsDeviceData)
{
    VkResult result;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount         = 0;
    pipelineLayoutInfo.pSetLayouts            = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges    = nullptr;

    result = vkCreatePipelineLayout(graphicsDeviceData.device, &pipelineLayoutInfo, nullptr, &graphicsDeviceData.pipelineLayout);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create pipeline layout\n");
        return false;
    }
    return true;
}

bool null::render::GraphicsDevice::Init()
{
    const system::WindowGraphicsDeviceData& windowGraphicsDeviceData = m_engine.GetWindow().GetGraphicsDeviceWindowData();

    std::vector<std::string> instanceExtensions;
    std::vector<std::string> deviceExtensions;

    if (!GetInstanceExtensions(instanceExtensions))
    {
        m_debugMessage = "Failed to determine required instance extensions";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
    instanceExtensions.insert(instanceExtensions.end(), windowGraphicsDeviceData.requiredExtensions.begin(), windowGraphicsDeviceData.requiredExtensions.end());

    if (!CreateInstance(*m_graphicsDeviceData, m_engine.GetApplicationName(), instanceExtensions))
    {
        m_debugMessage = "Failed to create Vulkan instance";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

#ifdef NE_DEBUG
    if (!SetupDebugMessenger(*m_graphicsDeviceData, &m_engine))
    {
        m_debugMessage = "Failed to setup debug messenger";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
#endif //NE_DEBUG

    if (!WindowInit())
    {
        return false;
    }

    if (!SelectPhysicalDevice(*m_graphicsDeviceData, instanceExtensions, deviceExtensions))
    {
        m_debugMessage = "Failed to select physical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    QueueFamilySet queueFamilySet = GetDeviceQueueFamilies(*m_graphicsDeviceData);
    if (!queueFamilySet.IsValid())
    {
        m_debugMessage = "Missing required queue families";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    if (!CreateLogicalDevice(*m_graphicsDeviceData, queueFamilySet))
    {
        m_debugMessage = "Failed to create logical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    vkGetDeviceQueue(
        m_graphicsDeviceData->device,
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily].value(),
        0,
        &m_graphicsDeviceData->graphicsQueue
    );
    vkGetDeviceQueue(
        m_graphicsDeviceData->device,
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily].value(),
        0,
        &m_graphicsDeviceData->presentQueue
    );

    if (!CreateSwapChain(*m_graphicsDeviceData, m_engine.GetWindow(), queueFamilySet))
    {
        m_debugMessage = "Failed to create swapchain images";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
    if (!CreateSwapChainViews(*m_graphicsDeviceData))
    {
        m_debugMessage = "Failed to create swapchain views";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

void null::render::GraphicsDevice::Destroy()
{
    vkDestroyPipelineLayout(m_graphicsDeviceData->device, m_graphicsDeviceData->pipelineLayout, nullptr);

#ifdef NE_DEBUG
    auto debugMessengerDestroy = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_graphicsDeviceData->instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (debugMessengerDestroy)
    {
        debugMessengerDestroy(m_graphicsDeviceData->instance, m_graphicsDeviceData->debugMessenger, nullptr);
    }
    else
    {
        debug::AssertFail("Unable to safely destroy Vulkan debug messenger\n");
    }
#endif //NE_DEBUG

    if (m_graphicsDeviceData->instance)
    {
        for (auto imageView : m_graphicsDeviceData->swapChainImageViews)
        {
            vkDestroyImageView(m_graphicsDeviceData->device, imageView, nullptr);
        }
        vkDestroySwapchainKHR(m_graphicsDeviceData->device, m_graphicsDeviceData->swapChain, nullptr);
        vkDestroyDevice(m_graphicsDeviceData->device, nullptr);
        vkDestroySurfaceKHR(m_graphicsDeviceData->instance, m_graphicsDeviceData->surface, nullptr);
        vkDestroyInstance(m_graphicsDeviceData->instance, nullptr);
    }
}

#endif //NE_BUILD_VULKAN
