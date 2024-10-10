cmake_minimum_required(VERSION 3.15)

project("")
get_filename_component(MY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("CMAKE_CURRENT_SOURCE_DIR ==> " ${MY_NAME})
set(PROJECT_NAME ${MY_NAME} )

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(ColorSpace)
add_subdirectory(ColorTransformations)