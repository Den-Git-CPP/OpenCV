cmake_minimum_required(VERSION 3.15)

project("")
get_filename_component(MY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("CMAKE_CURRENT_SOURCE_DIR ==> " ${MY_NAME})
set(PROJECT_NAME ${MY_NAME} )

project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(Color)
add_subdirectory(Control)
add_subdirectory(Image_Analysis)
add_subdirectory(Images_Video)
add_subdirectory(Filters_and_convolution)

