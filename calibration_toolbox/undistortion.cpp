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

    if (_cameraMatrix.empty())
    {
        std::cerr << "Camera matrix is empty. Exiting." << std::endl;
        return;
    }
    if (_distortionCoefficients.empty())
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
    cv::Mat cameraMatrixMat = cv::Mat(3, 3, CV_32F, &_cameraMatrix[0]);
    cv::Mat distCoeffsMat = cv::Mat(1, 5, CV_32F, &_distortionCoefficients[0]);

    cv::Size imageSize(cv::Size(inputImage.cols, inputImage.rows));

    if (_cameraType != Calibration::CameraType::MDC3_120)
    {
        // Equivalent to cv::undistort() - just more control over parameters.
        cv::Mat newCameraMatrix = cv::getOptimalNewCameraMatrix(cameraMatrixMat, distCoeffsMat, imageSize, 1, imageSize, 0);

        cv::Mat map1, map2;
        cv::initUndistortRectifyMap(cameraMatrixMat, distCoeffsMat, cv::Mat(), newCameraMatrix, imageSize, CV_16SC2, map1, map2);

        cv::Mat outputImage;
        cv::remap(inputImage, outputImage, map1, map2, cv::INTER_LINEAR);

        std::cout << "Writing undistorted image to " << _outputImagePath << std::endl;
        cv::imwrite(_outputImagePath, outputImage);
    }
    else
    {
        cv::Mat K, D;
        std::vector<cv::Mat> rvecs, tvecs;
        int flags = cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC | cv::fisheye::CALIB_FIX_SKEW;
        cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 1e-6);

        cv::InputArrayOfArrays temp(imgpoints);
        cv::fisheye::calibrate(objpoints, temp, imgSize, K, D, rvecs, tvecs, flags, criteria);

        cv::Mat map1, map2;
        cv::fisheye::initUndistortRectifyMap(K, D, cv::Mat::eye(3, 3, CV_32F), K, imgSize, CV_16SC2, map1, map2);


        cv::Mat source = cv::imread(fileName);
        cv::Mat undistort;
        cv::remap(source, undistort, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

        cv::Mat result;
        cv::hconcat(source, undistort, result);
        cv::resize(result, result, cv::Size(), 0.25, 0.25);
        cv::imshow("result", result);
        cv::waitKey();

    }
}

void Undistortion::undistortFisheye(const std::string &inputImagePath)
{
}