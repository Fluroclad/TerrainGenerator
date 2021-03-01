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

private:
	VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
	VkDevice m_device;
	VkInstance m_instance;
	VkQueue m_graphics_queue;
	VkQueue m_present_queue;
	Surface* m_surface;

	void SelectPhysicalDevice();
	void CreateDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
};