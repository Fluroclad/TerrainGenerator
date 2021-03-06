// Terrain Generator
// (c) 2021 Daniel Dickson, All Rights Reserved.

#include "App.hpp"


int main() {
	std::unique_ptr<App> game = std::make_unique<App>(1280, 760, "Terrain Generator");
	
	game->Run();

	return 0;
}
