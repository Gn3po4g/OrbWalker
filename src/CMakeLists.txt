project(main)

aux_source_directory(. SRCS)

add_library(${PROJECT_NAME} SHARED dllmain.cpp ${SRCS})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_link_libraries(${PROJECT_NAME} PRIVATE kiero libmem)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "D:/Riot Games/League of Legends/Game/Hid.dll")