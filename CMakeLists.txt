cmake_minimum_required(VERSION 3.25)
project(OrbWalker)

file(GLOB_RECURSE KIERO_SRC kiero/*)
add_library(Kiero STATIC ${KIERO_SRC})

file(GLOB_RECURSE ORBWALKER_SRC *.ixx *.cpp)
add_library(OrbWalker SHARED ${ORBWALKER_SRC})

set_property(TARGET OrbWalker PROPERTY CXX_STANDARD 23)
target_compile_options(OrbWalker PRIVATE "/experimental:module")
target_link_libraries(OrbWalker PRIVATE Kiero)
