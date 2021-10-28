#include "undistortion.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

Undistortion::Undistortion() {}

void Undistortion::setCameraType(CameraType type)
{
    if (type == CameraType::MDC3_60)
    {
        cameraMatrix = {1216.44437f, 0.f, 639.10603f,
                        0.f, 1214.25279f, 484.7274f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.479922f, 0.278691f, -0.000137f, 0.000710f, 0.f};
    }
    else if (type == CameraType::MDC3_120)
    {
        cameraMatrix = {638.23556f, 0.f, 636.35528f,
                        0.f, 636.55505f, 495.6578f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.272714f, 0.060136f, -0.000840f, 0.000259f, 0.f};
    }
    else if (type == CameraType::KOWA_6MM) // acA1920-40uc Kowa 6mm 1_8
    {
        cameraMatrix = {1060.45125f, 0.f, 970.25025f,
                        0.f, 1059.68604f, 609.87367f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.132717f, 0.053377f, 0.000166f, -0.000108f, 0.f};
    }
    else
    {
        std::cout << "WARNING: Wrong camera type" << std::endl;
    }

    cameraType = type;
}

void Undistortion::undistortOpenCv()
{
    cv::Mat inputImage;
    inputImage = cv::imread(inputImagePath);
    if (inputImage.empty())
    {
        std::cout << "cv::imread failed to import " << inputImagePath << std::endl;
        return;
    }
    cv::Mat cameraMatrixMat = cv::Mat(3, 3, CV_32F, &cameraMatrix[0]);
    cv::Mat distCoeffsMat = cv::Mat(1, 5, CV_32F, &distortionCoefficients[0]);

    cv::Mat outputImage, map1, map2, new_camera_matrix;
    cv::Size imageSize(cv::Size(inputImage.cols, inputImage.rows));

    // Method 1 to undistort the image.
    // new_camera_matrix = cv::getOptimalNewCameraMatrix(cameraMatrixMat, distCoeffsMat, imageSize, 1, imageSize, 0);
    // cv::undistort(inputImage, outputImage, new_camera_matrix, distCoeffsMat, new_camera_matrix);

    // Method 2 to undistort the image (looks like it works better - but why?)
    cv::initUndistortRectifyMap(cameraMatrixMat, distCoeffsMat, cv::Mat(), cv::getOptimalNewCameraMatrix(cameraMatrixMat, distCoeffsMat, imageSize, 1, imageSize, 0), imageSize, CV_16SC2, map1, map2);
    cv::remap(inputImage, outputImage, map1, map2, cv::INTER_LINEAR);

    std::cout << "Writing undistorted image to " << outputImagePath << std::endl;
    cv::imwrite(outputImagePath, outputImage);
}