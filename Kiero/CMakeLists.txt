project(kiero)

file(GLOB_RECURSE MINHOOK *.cpp *.c)

add_library(${PROJECT_NAME} STATIC kiero.cpp ${MINHOOK})