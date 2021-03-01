// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "App.hpp"

App::App(uint32_t width, uint32_t height, const std::string& title) {

	if (!glfwInit())
	{
		// Initialization failed
	}

	m_window = new Window(width, height, title);

	m_graphics = new Graphics(m_window);
}

App::~App() {
	glfwTerminate();
}

void App::Run() {
	while (!m_window->ShouldClose()) {
		m_window->Update();
	}
}

void App::SetTitle(const std::string& title) {
	m_window->SetTitle(title);
}