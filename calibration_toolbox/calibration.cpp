#include "calibration.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

void Calibration::getExistingCalibration()
{
    std::vector<float> cameraMatrix;
    std::vector<float> distortionCoefficients;
    if (_cameraType == CameraType::MDC3_60)
    {
        cameraMatrix = {1216.44437f, 0.f, 639.10603f,
                        0.f, 1214.25279f, 484.7274f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.479922f, 0.278691f, -0.000137f, 0.000710f, 0.f};
        _distortionCoefficientsCvMat = cv::Mat(1, 5, CV_32F, &distortionCoefficients[0]);
    }
    else if (_cameraType == CameraType::MDC3_120) // obtained with cv::fisheye::calibrate()
    {
        cameraMatrix = {631.1520782571031f, 0.0f, 649.8469891056759f,
                        0.f, 630.2008683008255f, 494.5608552948983f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.000852221592701229f, -0.002021302848618454f, 0.009273264304481579f, -0.00558289649465117f};
        _distortionCoefficientsCvMat = cv::Mat(1, 4, CV_32F, &distortionCoefficients[0]);
    }
    else if (_cameraType == CameraType::KOWA_6MM) // acA1920-40uc Kowa 6mm 1_8
    {
        cameraMatrix = {1060.45125f, 0.f, 970.25025f,
                        0.f, 1059.68604f, 609.87367f,
                        0.f, 0.f, 1.f};

        distortionCoefficients = {-0.132717f, 0.053377f, 0.000166f, -0.000108f, 0.f};
        _distortionCoefficientsCvMat = cv::Mat(1, 5, CV_32F, &distortionCoefficients[0]);
    }
    else
    {
        std::cout << "WARNING: Wrong or unsupported camera type" << std::endl;
        return;
    }

    _cameraMatrixCvMat = cv::Mat(3, 3, CV_32F, &cameraMatrix[0]);
}

void Calibration::calibrate()
{
    if (_inputImagesPath.empty())
    {
        std::cerr << "Empty inputImagesPath. Exiting." << std::endl;
        return;
    }

    int CHESSBOARD[2]{_chessboardW, _chessboardH};

    std::vector<std::vector<cv::Point3f>> objPoints;
    std::vector<std::vector<cv::Point2f>> imgPoints;
    std::vector<std::string> sources;
    cv::Size graySize;

    // Defining the world coordinates for 3D points
    std::vector<cv::Point3f> objp;
    for (int i{0}; i < CHESSBOARD[1]; i++)
    {
        for (int j{0}; j < CHESSBOARD[0]; j++)
            objp.push_back(cv::Point3f(j, i, 0));
    }

    std::vector<cv::String> images;
    std::string path = _inputImagesPath + "*.jpg";

    cv::glob(path, images);
    if (images.empty())
    {
        std::cerr << "No images found in " << _inputImagesPath << std::endl;
        return;
    }

    cv::Mat frame, gray;
    std::vector<cv::Point2f> corner_pts;
    bool success;
    for (int i{0}; i < images.size(); i++)
    {
        sources.push_back(images[i]);

        frame = cv::imread(images[i]);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        if (graySize.area() == 0)
        {
            graySize = gray.size();
        }
        else if (gray.size() != graySize)
        {
            std::cout << "Invalid image size: " << images[i] << " - expect " << graySize << ", but " << gray.size() << std::endl;
            continue;
        }

        success = cv::findChessboardCorners(gray, cv::Size(CHESSBOARD[0], CHESSBOARD[1]), corner_pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
        if (success)
        {
            cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1);

            // Refining pixel coordinates for given 2d points.
            cv::cornerSubPix(gray, corner_pts, cv::Size(11, 11), cv::Size(-1, -1), criteria);

            // Displaying the detected corner points on the checker board
            cv::drawChessboardCorners(frame, cv::Size(CHESSBOARD[0], CHESSBOARD[1]), corner_pts, success);

            objPoints.push_back(objp);
            imgPoints.push_back(corner_pts);
        }

        std::cout << "(" << i + 1 << "/" << images.size() << ") " << images[i] << " - Chessboard found: " << success << std::endl;

        // DEBUG: Uncomment to save chessboard images with drawn detection
        // std::string outputFilename = "/home/avelasco/CalibFiles/mdc3_60/TEST/img" + std::to_string(i) + ".jpg";
        // std::cout << "Writing " << outputFilename << std::endl;
        // cv::imwrite(outputFilename, frame);
    }

    if (_cameraType == CameraType::MDC3_120)
    {
        std::vector<cv::Mat> rvecs, tvecs;
        int flags = cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC | cv::fisheye::CALIB_CHECK_COND | cv::fisheye::CALIB_FIX_SKEW;
        std::cout << "Calibrating fisheye..." << std::endl;
        cv::fisheye::calibrate(objPoints, imgPoints, graySize, _cameraMatrixCvMat, _distortionCoefficientsCvMat, rvecs, tvecs, flags);
    }
    else
    {
        std::vector<cv::Mat> rvecs, tvecs;
        std::cout << "Calibrating..." << std::endl;
        int flags = cv::CALIB_CB_FAST_CHECK | cv::CALIB_FIX_FOCAL_LENGTH | cv::CALIB_FIX_INTRINSIC;
        cv::calibrateCamera(objPoints, imgPoints, graySize, _cameraMatrixCvMat, _distortionCoefficientsCvMat, rvecs, tvecs, flags);
    }
}