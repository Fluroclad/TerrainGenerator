// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#pragma once

#include <GLFW\glfw3.h>
#include <string>


class Window {
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	bool ShouldClose() const;

	void Update();

private:
	GLFWwindow* m_window;

	static void HandleWindowResize(GLFWwindow* window, int width, int height);
	static void HandleFrameBufferResize(GLFWwindow* window, int width, int height);
};