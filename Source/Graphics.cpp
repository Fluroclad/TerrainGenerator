// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Graphics.hpp"
#include <iostream>

const std::vector<const char*> validation_layers = {
	"VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif

Graphics::Graphics(Window* window) {
	m_window = window;
	CreateInstance();
	m_surface = new Surface(m_instance, m_window);
	m_device = new Device(m_instance, m_surface);
}

Graphics::~Graphics() {

}

void Graphics::CreateInstance() {

	if (enable_validation_layers && !CheckValidationLayers()) {
		throw std::runtime_error("Validation layers requested, but are not available!");
	}

	VkApplicationInfo app_info{};

	app_info.pApplicationName = "Terrain Generation";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "Voxel Engine";

	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_MAKE_VERSION(1, 2, 0);

	uint32_t glfw_extension_count = 0;
	const char** glfw_extensions;
	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	VkInstanceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.enabledExtensionCount = glfw_extension_count;
	create_info.ppEnabledExtensionNames = glfw_extensions;

	if (enable_validation_layers) {
		create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
		create_info.ppEnabledLayerNames = validation_layers.data();
	} else {
		create_info.enabledLayerCount = 0;
		create_info.pNext = nullptr;
	}
	

	create_info.enabledLayerCount = 0;

	if (vkCreateInstance(&create_info, nullptr, &m_instance) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create vulkan instance!");
	}
}

bool Graphics::CheckValidationLayers() {
	uint32_t layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
	
	std::vector<VkLayerProperties> available_layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

	for (const char* layer_name : validation_layers) {
		bool layer_found = false;

		for (const auto& layer_properties : available_layers) {
			if (strcmp(layer_name, layer_properties.layerName) == 0) {
				layer_found = true;
				break;
			}
		}

		if (!layer_found) {
			return false;
		}
	}

	return true;
}