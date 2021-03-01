// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <optional>
#include <iostream>

struct QueueFamilyIndices {
	std::optional<uint32_t> GraphicsFamily;

	bool IsComplete();
};


class Device {
public:
	Device(VkInstance instance);

private:
	VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
	
	bool IsDeviceSuitable(VkPhysicalDevice device);
};