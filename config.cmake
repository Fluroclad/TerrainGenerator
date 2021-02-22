# Terrain Generator
# (c) 2020 Daniel Dickson, All Rights Reserved.

# Detect the Operating System
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(PLATFORM_WINDOWS 1)

	# define preprocessor macro
	add_definitions(-DPLATFORM_WINDOWS) 
else ()
	# message(FATAL_ERROR "Unsupported operating system or environment")
	return()
endif ()