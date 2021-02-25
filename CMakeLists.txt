# Terrain Generator
# (c) 2020 Daniel Dickson, All Rights Reserved.

cmake_minimum_required(VERSION 3.19.5)
project(TerrainGenerator)

# Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory("Source")