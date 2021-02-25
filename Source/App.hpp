// Terrain Generator
// (c) 2020 Daniel Dickson, All Rights Reserved.

#pragma once

#include "Window.hpp"


class App {
public:
	App(uint32_t width, uint32_t height, const std::string& title);
	~App();

private:
	Window* m_pWindow;
};