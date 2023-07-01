cmake_minimum_required(VERSION 3.25)
project(OrbWalker)

add_subdirectory(kiero)

add_library(
        OrbWalker SHARED dllmain.cpp
        function.cpp function.ixx
        object.cpp object.ixx
        offset.cpp offset.ixx
        orbwalker.cpp orbwalker.ixx
)

set_property(TARGET OrbWalker PROPERTY CXX_STANDARD 23)
target_compile_options(OrbWalker PUBLIC "/experimental:module")
target_link_libraries(OrbWalker PUBLIC Kiero)
