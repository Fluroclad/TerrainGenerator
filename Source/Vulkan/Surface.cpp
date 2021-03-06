// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Surface.hpp"
#include "../Window.hpp"
#include "Device.hpp"

Surface::Surface(VkInstance& instance, std::shared_ptr<Window>& window) {
	m_instance = instance;

	if (glfwCreateWindowSurface(m_instance, window->Handle(), nullptr, &m_surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create window surface");
	}
}

VkSurfaceCapabilitiesKHR Surface::GetCapabilities(std::shared_ptr<Device>& device) {
	VkSurfaceCapabilitiesKHR capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->HandlePhysicalDevice(), m_surface, &capabilities);

	return capabilities;
}

std::vector<VkSurfaceFormatKHR> Surface::GetFormats(std::shared_ptr<Device>& device) {
	// See available formats
	uint32_t count;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->HandlePhysicalDevice(), m_surface, &count, nullptr);
	std::vector<VkSurfaceFormatKHR> formats(count);

	// Resize to hold all available formats
	if (count != 0) {
		formats.resize(count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device->HandlePhysicalDevice(), m_surface, &count, formats.data());
	}

	return formats;
}

std::vector<VkPresentModeKHR> Surface::GetPresentModes(std::shared_ptr<Device>& device) {
	// See if present mode is available
	uint32_t count;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->HandlePhysicalDevice(), m_surface, &count, nullptr);
	std::vector<VkPresentModeKHR> modes(count);

	// Resize to hold all available formats
	if (count != 0) {
		modes.resize(count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device->HandlePhysicalDevice(), m_surface, &count, modes.data());
	}

	return modes;
}