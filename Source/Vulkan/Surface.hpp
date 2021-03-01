// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>

class Window;

class Surface {
public:
	Surface(VkInstance& instance, Window* window);
	
	VkSurfaceKHR GetSurface() { return m_surface; }

private:
	VkSurfaceKHR m_surface;
	VkInstance m_instance;
};