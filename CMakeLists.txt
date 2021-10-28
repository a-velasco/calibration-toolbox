cmake_minimum_required(VERSION 3.10.2)
project(undistortion)

# include_directories("external")

file(GLOB SOURCES "*.cpp" "*.h")

find_package(OpenCV REQUIRED)

add_executable(undistortion  ${SOURCES})
target_include_directories(undistortion PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(undistortion  ${OpenCV_LIBS})