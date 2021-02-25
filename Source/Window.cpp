// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#include "Window.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string& title) {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::~Window() {
	glfwDestroyWindow(m_window);
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::Update() {
	glfwPollEvents();
}