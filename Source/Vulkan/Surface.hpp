// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include<memory>
#include <vector>
#include <stdexcept>

class Window;
class Device;

class Surface {
public:
	Surface(VkInstance& instance, std::shared_ptr<Window>& window);

	VkSurfaceKHR Handle() const { return m_surface; }

	VkSurfaceCapabilitiesKHR GetCapabilities(std::shared_ptr<Device>& device);
	std::vector<VkSurfaceFormatKHR> GetFormats(std::shared_ptr<Device>& device);
	std::vector<VkPresentModeKHR> GetPresentModes(std::shared_ptr<Device>& device);

private:
	VkSurfaceKHR m_surface;
	VkInstance m_instance;
};