cmake_minimum_required(VERSION 2.7)
project(rt)

set(CMAKE_CXX_FLAGS "-ggdb --std=c++11")

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

set(SHAPES shapes/sphere.cpp shapes/plane.cpp)
set(LIGHTS lights/point.cpp)

add_executable(rt main.cpp math.cpp color.cpp geometry.cpp world.cpp
	render.cpp shape.cpp ${SHAPES} camera.cpp material.cpp light.cpp
	${LIGHTS})
target_link_libraries(rt ${SDL2_LIBRARIES})
