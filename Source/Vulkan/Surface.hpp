// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

class Window;
class Device;

class Surface {
public:
	Surface(VkInstance& instance, Window* window);

	VkSurfaceKHR Handle() const { return m_surface; }

	VkSurfaceCapabilitiesKHR GetCapabilities(Device* device);
	std::vector<VkSurfaceFormatKHR> GetFormats(Device* device);
	std::vector<VkPresentModeKHR> GetPresentModes(Device* device);

private:
	VkSurfaceKHR m_surface;
	VkInstance m_instance;
};