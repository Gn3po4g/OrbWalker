cmake_minimum_required(VERSION 3.24)
project(OrbWalker)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(kiero)

file(GLOB_RECURSE srcs src/*.cpp)
add_library(${PROJECT_NAME} SHARED dllmain.cpp ${srcs})
target_precompile_headers(${PROJECT_NAME} PRIVATE "pch.h")
target_include_directories(${PROJECT_NAME} PRIVATE libmem)
target_include_directories(${PROJECT_NAME} PRIVATE kiero)
target_link_directories(${PROJECT_NAME} PRIVATE libmem)
target_link_libraries(${PROJECT_NAME} kiero)
target_link_libraries(${PROJECT_NAME} libmem)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "D:/Riot Games/League of Legends/Game/Hid.dll")