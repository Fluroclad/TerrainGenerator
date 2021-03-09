// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include "Window.hpp"

#include "Vulkan/Device.hpp"
#include "Vulkan/Surface.hpp"
#include "Vulkan/Swapchain.hpp"

class Graphics {
public:
	Graphics(std::shared_ptr<Window>& window);
	~Graphics();

	void CreateInstance();

private:
	std::shared_ptr<Window>& m_window;
	VkInstance m_instance;
	std::shared_ptr<Device> m_device;
	std::shared_ptr<Surface> m_surface;
	std::shared_ptr<Swapchain> m_swapchain;

	VkSurfaceCapabilitiesKHR m_surface_capabilities;
	std::vector<VkSurfaceFormatKHR> m_surface_formats;
	std::vector<VkPresentModeKHR> m_present_modes;

	bool CheckValidationLayers();
};