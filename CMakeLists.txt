cmake_minimum_required(VERSION 3.10.2)
project(calibration_toolbox)

# include_directories("external")

find_package(OpenCV REQUIRED)

set(SOURCES 
    calibration_toolbox/calibration.cpp
    calibration_toolbox/calibration.h

    calibration_toolbox/undistortion.cpp
    calibration_toolbox/undistortion.h)

add_executable(undistort_images  ${SOURCES} undistort_images.cpp)
add_executable(generate_calibration  ${SOURCES} generate_calibration.cpp)

target_include_directories(undistort_images PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(generate_calibration PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(undistort_images  ${OpenCV_LIBS})
target_link_libraries(generate_calibration  ${OpenCV_LIBS})