// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Swapchain.hpp"
//#include "Device.hpp"

Swapchain::Swapchain(std::shared_ptr<Surface>& surface, std::shared_ptr<Device>& device, std::shared_ptr<Window>& window) : m_device(device) {
	VkSurfaceCapabilitiesKHR capabilities = surface->GetCapabilities(device);
	std::vector<VkSurfaceFormatKHR> formats = surface->GetFormats(device);
	std::vector<VkPresentModeKHR> present_modes = surface->GetPresentModes(device);
	
	if (formats.size() == 0 || present_modes.size() == 0) {
		throw std::runtime_error("No available formats or present modes!");
	}

	ChooseSurfaceFormat(formats);
	ChoosePresentMode(present_modes);
	ChooseExtent(capabilities, window);

	m_image_count = capabilities.minImageCount + 1;

	// Do not exceed maximage count
	if (capabilities.maxImageCount > 0 && m_image_count > capabilities.maxImageCount) {
		m_image_count = capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	create_info.surface = surface->Handle();
	create_info.minImageCount = m_image_count;
	create_info.imageFormat = m_surface_format.format;
	create_info.imageColorSpace = m_surface_format.colorSpace;
	create_info.imageExtent = m_extent;
	create_info.imageArrayLayers = 1; // Always 1
	create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	// Check if graphics and present queues are the same device
	QueueFamilyIndices indices = FindQueueFamilies(device->HandlePhysicalDevice(), surface->Handle());

	uint32_t queue_family_indices[] = { indices.graphics_family.value(), indices.present_family.value() };

	if (indices.graphics_family != indices.present_family) {
		create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		create_info.queueFamilyIndexCount = 2;
		create_info.pQueueFamilyIndices = queue_family_indices;
	} else {
		create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		create_info.queueFamilyIndexCount = 0;
		create_info.pQueueFamilyIndices = nullptr;
	}

	create_info.preTransform = capabilities.currentTransform; // No transformations
	create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // Ignore alpha channel
	create_info.presentMode = m_present_mode;
	create_info.clipped = VK_TRUE;
	create_info.oldSwapchain = VK_NULL_HANDLE;

	// Create swapchain.
	if (vkCreateSwapchainKHR(device->HandleDevice(), &create_info, nullptr, &m_swapchain) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create swapchain!");
	}
}

Swapchain::~Swapchain() {
	vkDestroySwapchainKHR(m_device->HandleDevice(), m_swapchain, nullptr);
}

void Swapchain::ChooseSurfaceFormat(std::vector<VkSurfaceFormatKHR> available_formats) {
	// Set swapchain format
	for (const auto& available_format : available_formats) {
		if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			m_surface_format = available_format;
		}
	}
}

void Swapchain::ChoosePresentMode(std::vector<VkPresentModeKHR> available_present_modes) {
	// Set present mode if not suitable one, set a default mode
	for (const auto& available_present_mode : available_present_modes) {
		if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
			m_present_mode = available_present_mode;
		} else {
			m_present_mode = VK_PRESENT_MODE_FIFO_KHR;
		}
	}
}

void Swapchain::ChooseExtent(VkSurfaceCapabilitiesKHR capabilities, std::shared_ptr<Window>& window) {
	if (capabilities.currentExtent.width != UINT32_MAX) {
		m_extent = capabilities.currentExtent;
	} else {
		int width;
		int height;

		glfwGetFramebufferSize(window->Handle(), &width, &height);

		VkExtent2D actual_extent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actual_extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actual_extent.width));
		actual_extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actual_extent.height));
	
		m_extent = actual_extent;
	}
}