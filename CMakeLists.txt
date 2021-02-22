# Terrain Generator
# (c) 2020 Daniel Dickson, All Rights Reserved.

cmake_minimum_required(VERSION 3.19.5)
project(TerrainGenerator)

# Config for build script
include(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory("Source")