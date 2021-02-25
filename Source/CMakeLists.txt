# Terrain Generator
# (c) 2020 Daniel Dickson, All Rights Reserved.

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(APP_SRCS
		
		main.cpp

		App.cpp
		Window.cpp
)

set(APP_INC
	
		App.hpp
		Window.hpp
)

add_executable(TerrainGenerator ${APP_SRCS})

target_link_libraries(TerrainGenerator ${CONAN_LIBS})