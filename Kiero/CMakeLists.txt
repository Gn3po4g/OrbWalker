file(GLOB_RECURSE minhook minhook/*.c)

add_library(kiero STATIC kiero.cpp ${minhook})
