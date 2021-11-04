#include "undistortion.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

Undistortion::Undistortion(std::vector<float> &cameraMatrix,
                           std::vector<float> &distortionCoefficients) noexcept : _cameraMatrix(cameraMatrix), _distortionCoefficients(distortionCoefficients)
{
}

void Undistortion::undistort()
{
    if (_inputImagePath.empty())
    {
        std::cerr << "No input image path specified. Exiting." << std::endl;
        return;
    }
    if (_outputImagePath.empty())
    {
        std::cerr << "No output image path specified. Exiting." << std::endl;
        return;
    }

    if (_cameraMatrixCvMat.empty())
    {
        std::cerr << "Camera matrix is empty. Exiting." << std::endl;
        return;
    }
    if (_distortionCoefficientsCvMat.empty())
    {
        std::cerr << "Distortion coefficients are empty. Exiting." << std::endl;
        return;
    }

    cv::Mat inputImage;
    inputImage = cv::imread(_inputImagePath);

    if (inputImage.empty())
    {
        std::cout << "cv::imread failed to import " << _inputImagePath << std::endl;
        return;
    }

    cv::Size imageSize(cv::Size(inputImage.cols, inputImage.rows));

    if (_cameraType != Calibration::CameraType::MDC3_120)
    {
        // Equivalent to cv::undistort() - just more control over parameters.
        cv::Mat newCameraMatrix = cv::getOptimalNewCameraMatrix(_cameraMatrixCvMat, _distortionCoefficientsCvMat, imageSize, 1, imageSize, 0);

        cv::Mat map1, map2;
        cv::initUndistortRectifyMap(_cameraMatrixCvMat, _distortionCoefficientsCvMat, cv::Mat(), newCameraMatrix, imageSize, CV_16SC2, map1, map2);

        cv::Mat outputImage;
        cv::remap(inputImage, outputImage, map1, map2, cv::INTER_LINEAR);

        std::cout << "Writing undistorted image to " << _outputImagePath << std::endl;
        cv::imwrite(_outputImagePath, outputImage);
    }
    else
    {
        int balance = 1; // Do not crop image, draw black on extra pixels.
        cv::Mat newCameraMatrix;
        cv::fisheye::estimateNewCameraMatrixForUndistortRectify(_cameraMatrixCvMat,
                                                                _distortionCoefficientsCvMat,
                                                                imageSize,
                                                                cv::Mat::eye(3, 3, CV_32F),
                                                                newCameraMatrix, 
                                                                balance);

        cv::Mat map1, map2;
        cv::fisheye::initUndistortRectifyMap(_cameraMatrixCvMat, _distortionCoefficientsCvMat,
                                             cv::Mat::eye(3, 3, CV_32F), newCameraMatrix, imageSize, CV_16SC2, map1, map2);

        cv::Mat outputImage;
        cv::remap(inputImage, outputImage, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

        std::cout << "Writing undistorted image to " << _outputImagePath << std::endl;
        cv::imwrite(_outputImagePath, outputImage);
    }
}
