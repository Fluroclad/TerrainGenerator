// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Surface.hpp"
#include "../Window.hpp"

Surface::Surface(VkInstance& instance, Window* m_window) {
	m_instance = instance;

	if (glfwCreateWindowSurface(m_instance, m_window->GetWindow(), nullptr, &m_surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create window surface");
	}
}