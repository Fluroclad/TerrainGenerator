// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include "Window.hpp"

#include "vulkan/Device.hpp"

class Graphics {
public:
	Graphics();
	~Graphics();

	void CreateInstance();

private:
	Window* m_window;
	VkInstance m_instance;
	Device* m_device;

	bool CheckValidationLayers();
};