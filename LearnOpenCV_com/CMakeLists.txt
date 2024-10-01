cmake_minimum_required(VERSION 3.25)
project("")
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("==========================================================")
message("CMAKE_CURRENT_SOURCE_DIR =>PROJECT_NAME=> " ${PROJECT_NAME})
message("==========================================================")

project(${PROJECT_NAME})

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
     )

foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})

foreach(target ${TARGETS})

include_directories(
    ${OpenCV_INCLUDE_DIRS}    
    )

target_link_libraries(${target} ${OpenCV_LIBS})

set_target_properties(${target}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    )
endforeach(target ${TARGETS})


#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
#    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    target_compile_options(${target} PRIVATE
#        -g
#        -Wall
#        -Wextra
#        -Werror
#        -pedantic
#    )
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    target_compile_options(${target} PRIVATE
#        /EHsc
#        /W4
#        /WX
#    )
#endif()
#
#


