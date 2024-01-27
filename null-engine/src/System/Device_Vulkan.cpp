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

const char constexpr* validationLayers[] =
{
#ifdef NE_DEBUG
    "VK_LAYER_KHRONOS_validation"
#endif //NE_DEBUG
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

QueueFamilySet GetDeviceQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR& surface)
{
    null::math::uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    QueueFamilySet queueFamilySet;

    for (null::math::size i = 0; i < queueFamilyCount; ++i)
    {
        const VkQueueFamilyProperties& queueFamily = queueFamilies[i];
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::GraphicsFamily] = i;
        }
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport)
        {
            queueFamilySet.queueFamilies[(null::math::size)QueueFamily::PresentationFamily] = i;
        }
    }

    return queueFamilySet;
}

bool IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool isSuitable = true;

    return isSuitable;
}

bool CreateInstance(VkInstance& instance, const char* applicationName, const std::vector<const char*>& requiredExtensions)
{
    if (!CheckValidationLayerSupport())
    {
        null::debug::AssertFail("Required validation layer is not available.");
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

    std::vector<const char*> extensionNames(extensionCount);
    for (null::math::uint32 i = 0; i < extensionCount; ++i)
    {
        extensionNames[i] = extensionProperties[i].extensionName;
    }
#ifdef NE_DEBUG
    extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif //NE_DEBUG
    extensionNames.insert(extensionNames.end(), requiredExtensions.begin(), requiredExtensions.end());

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext                   = nullptr;
    instanceCreateInfo.flags                   = 0;
    instanceCreateInfo.pApplicationInfo        = &appInfo;
    instanceCreateInfo.enabledLayerCount       = (sizeof(validationLayers) / sizeof(const char*));
    instanceCreateInfo.ppEnabledLayerNames     = validationLayers;
    instanceCreateInfo.enabledExtensionCount   = extensionNames.size();
    instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();

    result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        null::debug::AssertFail("Failed to create Vulkan instance\n");
        return false;
    }

    return true;
}

#ifdef NE_DEBUG
bool SetupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger, void* userData)
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

    auto debugMessengerCreate = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
    if (debugMessengerCreate)
    {
        result = debugMessengerCreate(instance, &debugCreateInfo, nullptr, &debugMessenger);
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

bool SelectPhysicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice)
{
    null::math::uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        null::debug::AssertFail("Failed to find GPUs with Vulkan support\n");
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const VkPhysicalDevice& device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE)
    {
        null::debug::AssertFail("Failed to find a suitable GPU\n");
        return false;
    }

    return true;
}

bool CreateLogicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice, VkDevice& device, QueueFamilySet& queueFamilySet)
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
    createInfo.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos    = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = queueCreateInfos.size();
    createInfo.pEnabledFeatures     = &deviceFeatures;

    result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
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

    if (!CreateInstance(m_deviceData->instance, m_engine.GetApplicationName(), windowDeviceData.requiredExtensions))
    {
        m_debugMessage = "Failed to create Vulkan instance";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

#ifdef NE_DEBUG
    if (!SetupDebugMessenger(m_deviceData->instance, m_deviceData->debugMessenger, &m_engine))
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

    if (!SelectPhysicalDevice(m_deviceData->instance, m_deviceData->physicalDevice))
    {
        m_debugMessage = "Failed to select physical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    QueueFamilySet queueFamilySet = GetDeviceQueueFamilies(m_deviceData->physicalDevice, m_deviceData->surface);
    if (!queueFamilySet.IsValid())
    {
        m_debugMessage = "Missing required queue families";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    if (!CreateLogicalDevice(m_deviceData->instance, m_deviceData->physicalDevice, m_deviceData->device, queueFamilySet))
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
