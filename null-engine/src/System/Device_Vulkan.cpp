#include "NE/System/Device.h"

#ifdef NE_BUILD_VULKAN

#include "NE/API/Common_Vulkan.h"

#include "NE/Core/Engine.h"

#include "NE/Util/Enum.h"

#include <cstring>
#include <vector>

NE_ENUM_BITMASK_BEGIN(QueueFamily, null::math::uint32)
{
    None           = 0,
    GraphicsFamily = 1 << 0,
    Mask           = 0b1
};
NE_ENUM_BITMASK_END(QueueFamily, null::math::uint32)

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

QueueFamily GetDeviceQueueFamilies(VkPhysicalDevice device)
{
    null::math::uint32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    QueueFamily family = QueueFamily::None;

    for (const VkQueueFamilyProperties& queueFamily : queueFamilies)
    {
        switch (queueFamily.queueFlags)
        {
            default: break;
            case VK_QUEUE_GRAPHICS_BIT: family |= QueueFamily::GraphicsFamily;
        }
    }

    return family;
}

bool IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool isSuitable = true;

    isSuitable |= (GetDeviceQueueFamilies(device) & QueueFamily::Mask) == QueueFamily::Mask;

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

    if (!SelectPhysicalDevice(m_deviceData->instance, m_deviceData->physicalDevice))
    {
        m_debugMessage = "Failed to select physical device";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

#endif //NE_BUILD_VULKAN
