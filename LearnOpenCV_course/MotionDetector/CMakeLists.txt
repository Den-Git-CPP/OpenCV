cmake_minimum_required (VERSION 3.21.0)
 
project (motionDetector)
find_package(OpenCV REQUIRED)
include_directories((${OpenCV_INCLUDE_DIRS}))
set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

set (SOURCE src/main.cpp src/camera.cpp src/logger.cpp)
 
add_executable (${PROJECT_NAME} ${SOURCE})
target_link_libraries(motionDetector ${OpenCV_LIBS})
target_include_directories(motionDetector PRIVATE include)
