#include "NE/System/Device.h"

#ifdef NE_BUILD_VULKAN

#include "NE/API/Common_Vulkan.h"

#include <vector>

null::system::Device::Device(core::Engine& engine)
    :
    m_engine(engine),
    m_deviceData(std::make_unique<DeviceData>())
{

}

null::system::Device::~Device()
{
    if (m_deviceData->instance)
    {
        vkDestroyInstance(m_deviceData->instance, nullptr);
    }
}

bool null::system::Device::Init()
{
    VkResult result;

    VkApplicationInfo appInfo;
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext              = nullptr;
    appInfo.pApplicationName   = "Foobar";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
    appInfo.pEngineName        = "Null-Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    std::vector<const char*> layerNames;

    math::uint32 extensionCount;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to retrieve extension count from vulkan";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }
    std::vector<VkExtensionProperties> extensionProperties(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to retrieve extension names from vulkan";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    std::vector<const char*> extensionNames(extensionCount);
    for (math::uint32 i = 0; i < extensionCount; ++i)
    {
        extensionNames[i] = extensionProperties[i].extensionName;
    }

    VkInstanceCreateInfo createInfo;
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext                   = nullptr;
    createInfo.flags                   = 0;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledLayerCount       = layerNames.size();
    createInfo.ppEnabledLayerNames     = layerNames.data();
    createInfo.enabledExtensionCount   = extensionNames.size();
    createInfo.ppEnabledExtensionNames = extensionNames.data();

    result = vkCreateInstance(&createInfo, nullptr, &m_deviceData->instance);
    if (result != VK_SUCCESS)
    {
        m_debugMessage = "Failed to create vulkan instance";
        debug::AssertFail("%s\n", m_debugMessage.c_str());
        return false;
    }

    return true;
}

#endif //NE_BUILD_VULKAN
