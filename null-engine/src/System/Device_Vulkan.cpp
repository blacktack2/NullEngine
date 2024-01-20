#include "NE/System/Device.h"

#ifdef NE_BUILD_VULKAN

#include "NE/Core/Engine.h"

#include "NE/API/Common_Vulkan.h"

#include <cstring>
#include <vector>

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

bool IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool isSuitable = true;

    // TODO - Implement validation checks

    return isSuitable;
}

null::system::Device::Device(core::Engine& engine)
    :
    m_engine(engine),
    m_deviceData(std::make_unique<DeviceData>())
{

}

null::system::Device::~Device()
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
        vkDestroyInstance(m_deviceData->instance, nullptr);
    }
}

bool null::system::Device::Init()
{
    if (!CheckValidationLayerSupport())
    {
        null::debug::AssertFail("Required validation layer is not available.");
        return false;
    }

    const WindowDeviceData& windowDeviceData = m_engine.GetWindow().GetWindowDeviceData();

    VkResult result;

    VkApplicationInfo appInfo;
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext              = nullptr;
    appInfo.pApplicationName   = m_engine.GetApplicationName();
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.pEngineName        = "Null-Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_3;

    math::uint32 extensionCount;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to retrieve extension count from Vulkan";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to retrieve extension names from Vulkan";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    std::vector<const char*> extensionNames(extensionCount);
    for (math::uint32 i = 0; i < extensionCount; ++i)
    {
        extensionNames[i] = extensionProperties[i].extensionName;
    }
#ifdef NE_DEBUG
    extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif //NE_DEBUG
    extensionNames.insert(extensionNames.end(), windowDeviceData.requiredExtensions.begin(), windowDeviceData.requiredExtensions.end());

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext                   = nullptr;
    instanceCreateInfo.flags                   = 0;
    instanceCreateInfo.pApplicationInfo        = &appInfo;
    instanceCreateInfo.enabledLayerCount       = (sizeof(validationLayers) / sizeof(const char*));
    instanceCreateInfo.ppEnabledLayerNames     = validationLayers;
    instanceCreateInfo.enabledExtensionCount   = extensionNames.size();
    instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();

    result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_deviceData->instance);
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to create Vulkan instance";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

#ifdef NE_DEBUG
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
    debugCreateInfo.pfnUserCallback = DebugCallback;
    debugCreateInfo.pUserData = &m_engine;

    auto debugMessengerCreate = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_deviceData->instance, "vkCreateDebugUtilsMessengerEXT"));
    if (debugMessengerCreate)
    {
        result = debugMessengerCreate(m_deviceData->instance, &debugCreateInfo, nullptr, &m_deviceData->debugMessenger);
        if (result != VK_SUCCESS)
        {
            m_debugMessage = "Failed to assign Vulkan debug callback";
            debug::AssertFail("%s\n", m_debugMessage.c_str());
            return false;
        }
    }
    else
    {
        m_debugMessage = "Missing extension for Vulkan debug callback";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
#endif //NE_DEBUG

    math::uint32 deviceCount = 0;
    vkEnumeratePhysicalDevices(m_deviceData->instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        m_debugMessage = "Failed to find GPUs with Vulkan support";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_deviceData->instance, &deviceCount, devices.data());

    for (const VkPhysicalDevice& device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            m_deviceData->physicalDevice = device;
            break;
        }
    }

    if (m_deviceData->physicalDevice == VK_NULL_HANDLE)
    {
        m_debugMessage = "Failed to find a suitable GPU";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

#endif //NE_BUILD_VULKAN
