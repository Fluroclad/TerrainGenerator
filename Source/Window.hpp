// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#include <string>


class Window {
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	bool ShouldClose() const;
	void Update();
	
	void SetTitle(const std::string& title);

	GLFWwindow* GetWindow() { return m_window; }

private:
	GLFWwindow* m_window;

	static void HandleWindowResize(GLFWwindow* window, int width, int height);
	static void HandleFrameBufferResize(GLFWwindow* window, int width, int height);
};