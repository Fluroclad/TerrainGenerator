# Terrain Generator
# (c) 2020 Daniel Dickson, All Rights Reserved.

set(GAME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(game_srcs
		
		main.cpp
)

add_executable(TerrainGenerator ${game_srcs})

target_link_libraries(TerrainGenerator ${CONAN_LIBS})