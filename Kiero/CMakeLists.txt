cmake_minimum_required(VERSION 3.25)
project(Kiero)

file(GLOB_RECURSE SRC *)

add_library(Kiero STATIC ${SRC})