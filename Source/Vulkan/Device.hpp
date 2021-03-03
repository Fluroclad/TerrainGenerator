// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <optional>
#include <iostream>
#include <set>

#include "Surface.hpp"

struct QueueFamilyIndices {
	std::optional<uint32_t> graphics_family;
	std::optional<uint32_t> present_family;

	bool IsComplete();
};


class Device {
public:
	Device(VkInstance& instance, Surface* m_surface);

	VkDevice HandleDevice() const { return m_device; }
	VkPhysicalDevice HandlePhysicalDevice() const { return m_physical_device; }

private:
	VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
	VkDevice m_device;
	VkInstance m_instance;
	VkQueue m_graphics_queue;
	VkQueue m_present_queue;
	Surface* m_surface;

	VkSurfaceCapabilitiesKHR m_surface_capabilities;
	std::vector<VkSurfaceFormatKHR> m_surface_formats;
	std::vector<VkPresentModeKHR> m_present_modes;

	void SelectPhysicalDevice();
	void CreateDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
};