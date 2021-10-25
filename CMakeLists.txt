cmake_minimum_required(VERSION 3.10.2)
project(undistortion)

# include_directories("external")

file(GLOB SOURCES "*.cpp")

# set(OpenCV_DIR "E:/Programs/programming/opencv/build2")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(undistortion  ${SOURCES})

target_link_libraries(undistortion  ${OpenCV_LIBS})