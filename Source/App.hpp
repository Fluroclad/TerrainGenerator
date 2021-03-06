// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#pragma once

#include <memory>

#include "Window.hpp"
#include "Graphics.hpp"

class App {
public:
	App(uint32_t width, uint32_t height, const std::string& title);
	~App();

	void Run();

	void SetTitle(const std::string& title);

	Window& GetWindow() { return *m_window; }

private:
	std::shared_ptr<Window> m_window;
	std::unique_ptr<Graphics> m_graphics;
};