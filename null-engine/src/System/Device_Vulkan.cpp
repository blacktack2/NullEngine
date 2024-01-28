#include "NE/System/Device.h"

#ifdef NE_BUILD_VULKAN

#include "NE/API/Common_Vulkan.h"

#include "NE/Core/Engine.h"

#include "NE/Util/Enum.h"

#include <array>
#include <cstring>
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

QueueFamilySet GetDeviceQueueFamilies(null::system::DeviceData& deviceData)
{
    null::math::uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(deviceData.physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(deviceData.physicalDevice, &queueFamilyCount, queueFamilies.data());

    QueueFamilySet queueFamilySet;

    for (null::math::size i = 0; i < queueFamilyCount; ++i)
    {
        const VkQueueFamilyProperties& queueFamily = queueFamilies[i];
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily] = i;
        }
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(deviceData.physicalDevice, i, deviceData.surface, &presentSupport);
        if (presentSupport)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily] = i;
        }
    }

    return queueFamilySet;
}

SwapChainSupportData GetSwapChainSupport(null::system::DeviceData& deviceData)
{
    SwapChainSupportData data;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(deviceData.physicalDevice, deviceData.surface, &data.capabilities);

    null::math::uint32 formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(deviceData.physicalDevice, deviceData.surface, &formatCount, nullptr);
    if (formatCount > 0)
    {
        data.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(deviceData.physicalDevice, deviceData.surface, &formatCount, data.formats.data());
    }

    null::math::uint32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(deviceData.physicalDevice, deviceData.surface, &presentModeCount, nullptr);
    if (formatCount > 0)
    {
        data.presentModes.resize(formatCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(deviceData.physicalDevice, deviceData.surface, &presentModeCount, data.presentModes.data());
    }

    return data;
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

bool IsDeviceSuitable(null::system::DeviceData& deviceData, const std::vector<std::string>& deviceExtensions)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(deviceData.physicalDevice, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(deviceData.physicalDevice, &deviceFeatures);

    if (!AreExtensionsSupported(deviceExtensions))
    {
        null::debug::AssertFail("Logical device extensions not supported.\n");
        return false;
    }

    SwapChainSupportData swapChainSupport = GetSwapChainSupport(deviceData);
    if (swapChainSupport.formats.empty() || swapChainSupport.presentModes.empty())
    {
        null::debug::AssertFail("Swap-chain not supported.\n");
        return false;
    }

    return true;
}

bool CreateInstance(null::system::DeviceData& deviceData, const char* applicationName, const std::vector<std::string>& instanceExtensions)
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

    result = vkCreateInstance(&instanceCreateInfo, nullptr, &deviceData.instance);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create Vulkan instance\n");
        return false;
    }

    return true;
}

#ifdef NE_DEBUG
bool SetupDebugMessenger(null::system::DeviceData& deviceData, void* userData)
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
    debugCreateInfo.pfnUserCallback = null::system::DebugCallback;
    debugCreateInfo.pUserData = &userData;

    auto debugMessengerCreate = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(deviceData.instance, "vkCreateDebugUtilsMessengerEXT"));
    if (debugMessengerCreate)
    {
        result = debugMessengerCreate(deviceData.instance, &debugCreateInfo, nullptr, &deviceData.debugMessenger);
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

bool SelectPhysicalDevice(null::system::DeviceData& deviceData, const std::vector<std::string>& instanceExtensions, std::vector<std::string>& deviceExtensions)
{
    null::math::uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(deviceData.instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        null::debug::AssertFail("Failed to find GPUs with Vulkan support\n");
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(deviceData.instance, &deviceCount, devices.data());

    for (VkPhysicalDevice& device : devices)
    {
        deviceData.physicalDevice = device;
        GetDeviceExtensions(device, deviceExtensions);

        if (IsDeviceSuitable(deviceData, deviceExtensions))
        {
            deviceData.physicalDevice = device;
            break;
        }
        deviceData.physicalDevice = VK_NULL_HANDLE;
    }

    if (deviceData.physicalDevice == VK_NULL_HANDLE)
    {
        null::debug::AssertFail("Failed to find a suitable GPU\n");
        return false;
    }

    return true;
}

bool CreateLogicalDevice(null::system::DeviceData& deviceData, QueueFamilySet& queueFamilySet)
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

    result = vkCreateDevice(deviceData.physicalDevice, &createInfo, nullptr, &deviceData.device);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create logical device\n");
        return false;
    }

    return true;
}

bool null::system::Device::Init()
{
    const WindowDeviceData& windowDeviceData = m_engine.GetWindow().GetWindowDeviceData();

    std::vector<std::string> instanceExtensions;
    std::vector<std::string> deviceExtensions;

    if (!GetInstanceExtensions(instanceExtensions))
    {
        m_debugMessage = "Failed to determine required instance extensions";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
    instanceExtensions.insert(instanceExtensions.end(), windowDeviceData.requiredExtensions.begin(), windowDeviceData.requiredExtensions.end());

    if (!CreateInstance(*m_deviceData, m_engine.GetApplicationName(), instanceExtensions))
    {
        m_debugMessage = "Failed to create Vulkan instance";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

#ifdef NE_DEBUG
    if (!SetupDebugMessenger(*m_deviceData, &m_engine))
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

    if (!SelectPhysicalDevice(*m_deviceData, instanceExtensions, deviceExtensions))
    {
        m_debugMessage = "Failed to select physical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    QueueFamilySet queueFamilySet = GetDeviceQueueFamilies(*m_deviceData);
    if (!queueFamilySet.IsValid())
    {
        m_debugMessage = "Missing required queue families";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    if (!CreateLogicalDevice(*m_deviceData, queueFamilySet))
    {
        m_debugMessage = "Failed to create logical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    vkGetDeviceQueue(
        m_deviceData->device,
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily].value(),
        0,
        &m_deviceData->graphicsQueue
    );
    vkGetDeviceQueue(
        m_deviceData->device,
        queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily].value(),
        0,
        &m_deviceData->presentQueue
    );

    return true;
}

void null::system::Device::Destroy()
{
#ifdef NE_DEBUG
    auto debugMessengerDestroy = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_deviceData->instance, "vkDestroyDebugUtilsMessengerEXT"));
    if (debugMessengerDestroy)
    {
        debugMessengerDestroy(m_deviceData->instance, m_deviceData->debugMessenger, nullptr);
    }
    else
    {
        debug::AssertFail("Unable to safely destroy Vulkan debug messenger\n");
    }
#endif //NE_DEBUG
    if (m_deviceData->instance)
    {
        vkDestroyDevice(m_deviceData->device, nullptr);
        vkDestroyInstance(m_deviceData->instance, nullptr);
    }
}

#endif //NE_BUILD_VULKAN
