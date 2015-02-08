cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("SDLGraphs")
# Version number.
set(SDL_GRAPHS_VERSION_MAJOR 1)
set(SDL_GRAPHS_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_library(sdlgraphs src/sdlgraphs.cpp)
target_link_libraries(sdlgraphs ${SDL2_LIBRARY})

add_executable(sdlgraphs-test src/sample.cpp)
target_link_libraries(sdlgraphs-test ${SDL2_LIBRARY} sdlgraphs)
