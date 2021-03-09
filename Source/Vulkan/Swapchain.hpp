// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>

#include <stdexcept>
#include <memory>
#include <vector>

#include "Surface.hpp"
#include "Device.hpp"
#include "../Window.hpp"

class Swapchain {
public:
	Swapchain(std::shared_ptr<Surface>& surface, std::shared_ptr<Device>& device, std::shared_ptr<Window>& window);
	~Swapchain();

private:
	std::shared_ptr<Device>& m_device;
	VkSwapchainKHR m_swapchain;

	uint32_t m_image_count;
	VkSurfaceFormatKHR m_surface_format;
	VkPresentModeKHR m_present_mode;
	VkExtent2D m_extent;

	void ChooseSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats);
	void ChoosePresentMode(std::vector<VkPresentModeKHR> present_modes);
	void ChooseExtent(VkSurfaceCapabilitiesKHR capabilities, std::shared_ptr<Window>& window);
};