# Terrain Generator
# (c) 2021 Daniel Dickson, All Rights Reserved.


## Find Vulkan Library
find_package(Vulkan)

if (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
else()
	message(STATUS ${Vulkan_LIBRARY})
endif()

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(APP_SRCS
		
		main.cpp

		App.cpp
		Window.cpp
		Graphics.cpp

		Vulkan/Device.cpp
		Vulkan/Surface.cpp
		Vulkan/Swapchain.cpp
)

set(APP_INC
	
		App.hpp
		Window.hpp
		Graphics.hpp

		Vulkan/Device.hpp
		Vulkan/Surface.hpp
		Vulkan/Swapchain.hpp
)

add_executable(TerrainGenerator ${APP_SRCS})
target_link_libraries(TerrainGenerator ${CONAN_LIBS} ${Vulkan_LIBRARY})

set_target_properties(TerrainGenerator PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)