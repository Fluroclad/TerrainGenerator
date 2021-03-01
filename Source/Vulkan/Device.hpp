// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <optional>
#include <iostream>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphics_family;

	bool IsComplete();
};


class Device {
public:
	Device(VkInstance& instance);

private:
	VkPhysicalDevice m_physical_device = VK_NULL_HANDLE;
	VkDevice m_device;
	VkInstance m_instance;
	VkQueue m_graphics_queue;
	
	void SelectPhysicalDevice();
	void CreateDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
};