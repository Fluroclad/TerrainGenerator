// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#include "Device.hpp"

Device::Device(VkInstance instance) {
	uint32_t device_count = 0;

	vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

	if (device_count == 0) {
		throw std::runtime_error("Failed to find a GPU with Vulkan Support!");
	}

	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

	for (const auto& device : devices) {
		if (IsDeviceSuitable(device)) {
			//throw std::runtime_error("DEVICE IS SUITABLE!");
			m_physical_device = device;
			break;
		}
	}
	
	if (m_physical_device == VK_NULL_HANDLE) {
		throw std::runtime_error("Failed to find a suitable GPU!");
	}
}

bool Device::IsDeviceSuitable(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties2 device_properties;
	VkPhysicalDeviceFeatures2 device_features;
	
	vkGetPhysicalDeviceProperties2(device, &device_properties);
	vkGetPhysicalDeviceFeatures2(device, &device_features);

	// Return true till I work out what is going on.
	return true;
	
	// Code here is for API v1.0
	//return device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
	//	device_features.geometryShader;

	// Code here is for API v1.2
	//return device_properties.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
	//	device_features.features.geometryShader;
}