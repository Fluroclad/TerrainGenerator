// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Device.hpp"

// Extensions
const std::vector<const char*> device_extensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
	QueueFamilyIndices indices;

	uint32_t queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

	std::vector<VkQueueFamilyProperties> Queue_families(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, Queue_families.data());
	
	// Search for queue support family and present
	int i = 0;
	for (const auto& queue_family : Queue_families) {
		if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphics_family = i;
		}

		VkBool32 present_support = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

		if (present_support) {
			indices.present_family = i;
		}

		if (indices.IsComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

bool QueueFamilyIndices::IsComplete() {
	return graphics_family.has_value() && present_family.has_value();
}

Device::Device(VkInstance& instance, Surface* surface) {
	m_instance = instance;
	m_surface = surface;

	SelectPhysicalDevice();
	CreateDevice();
}

void Device::SelectPhysicalDevice() {
	uint32_t device_count = 0;

	vkEnumeratePhysicalDevices(m_instance, &device_count, nullptr);

	if (device_count == 0) {
		throw std::runtime_error("Failed to find a GPU with Vulkan Support!");
	}

	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(m_instance, &device_count, devices.data());

	for (const auto& device : devices) {
		if (IsDeviceSuitable(device)) {
			m_physical_device = device;
			break;
		}
	}

	if (m_physical_device == VK_NULL_HANDLE) {
		throw std::runtime_error("Failed to find a suitable GPU!");
	}
}

void Device::CreateDevice() {
	QueueFamilyIndices indices = FindQueueFamilies(m_physical_device, m_surface->GetSurface());
	
	std::vector< VkDeviceQueueCreateInfo> queue_create_infos{};
	std::set<uint32_t> unique_queue_families = { indices.graphics_family.value(), indices.present_family.value() };
	float queue_priorty = 1.0f;

	for (uint32_t queue_family : unique_queue_families) {
		VkDeviceQueueCreateInfo queue_create_info{};
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = queue_family;
		queue_create_info.queueCount = 1;
		queue_create_info.pQueuePriorities = &queue_priorty;
		queue_create_infos.push_back(queue_create_info);
	}

	// Preperation for activating device features in the future
	VkPhysicalDeviceFeatures device_features{};
	
	VkDeviceCreateInfo device_info{};
	device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_info.pQueueCreateInfos = queue_create_infos.data();
	device_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
	device_info.pEnabledFeatures = &device_features;
	device_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
	device_info.ppEnabledExtensionNames = device_extensions.data();

	if (vkCreateDevice(m_physical_device, &device_info, nullptr, &m_device) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create device!");
	}

	vkGetDeviceQueue(m_device, indices.graphics_family.value(), 0, &m_graphics_queue);
	vkGetDeviceQueue(m_device, indices.present_family.value(), 0, &m_graphics_queue);
}

bool Device::IsDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = FindQueueFamilies(device, m_surface->GetSurface());
	bool extensions_supported = CheckDeviceExtensionSupport(device);

	bool swapchain_supported = false;
	if (extensions_supported) {
		SwapchainSupport(device);
		swapchain_supported = !m_surface_formats.empty() && !m_present_modes.empty();
	}

	return indices.IsComplete() && extensions_supported && swapchain_supported;
}

bool Device::CheckDeviceExtensionSupport(VkPhysicalDevice device) {
	uint32_t extension_count;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

	std::vector<VkExtensionProperties> available_extensions(extension_count);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

	std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());

	for (const auto& extension : available_extensions) {
		required_extensions.erase(extension.extensionName);
	}

	// Return true if empty
	return required_extensions.empty();
}

void Device::SwapchainSupport(VkPhysicalDevice device) {
	// Surface capabilities
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface->GetSurface(), &m_surface_capabilities);

	uint32_t format_count; 
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface->GetSurface(), &format_count, nullptr);

	// Resize to hold all available formats
	if (format_count != 0) {
		m_surface_formats.resize(format_count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface->GetSurface(), &format_count, m_surface_formats.data());
	}

	// See if present mode is available
	uint32_t present_mode_count;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface->GetSurface(), &present_mode_count, nullptr);
	
	if (present_mode_count != 0) {
		m_present_modes.resize(present_mode_count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface->GetSurface(), &present_mode_count, m_present_modes.data());
	}
}