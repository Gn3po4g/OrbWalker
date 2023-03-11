cmake_minimum_required(VERSION 3.24)
project(OrbWalker)

set(CMAKE_CXX_STANDARD 23)

include_directories(kiero libmem)
link_directories(libmem)

add_subdirectory(kiero)
add_subdirectory(src)