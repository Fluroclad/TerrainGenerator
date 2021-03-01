// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include "Window.hpp"

#include "Vulkan/Device.hpp"
#include "Vulkan/Surface.hpp"

class Graphics {
public:
	Graphics(Window* window);
	~Graphics();

	void CreateInstance();

private:
	Window* m_window;
	VkInstance m_instance;
	Device* m_device;
	Surface* m_surface;

	bool CheckValidationLayers();
};