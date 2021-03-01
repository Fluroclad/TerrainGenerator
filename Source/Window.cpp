// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "Window.hpp"

Window::Window(uint32_t width, uint32_t height, const std::string& title) {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowSizeCallback(m_window, &HandleWindowResize);
	glfwSetFramebufferSizeCallback(m_window, &HandleFrameBufferResize);
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

void Window::SetTitle(const std::string& title) {
	glfwSetWindowTitle(m_window, title.c_str());
}

void Window::HandleWindowResize(GLFWwindow* window, int width, int height) {
	
}

void Window::HandleFrameBufferResize(GLFWwindow* window, int width, int height) {

}