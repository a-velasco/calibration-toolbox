#include "calibration.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

void Calibration::getExistingCalibration()
{
    if (_cameraType == CameraType::MDC3_60)
    {
        _cameraMatrix = {1216.44437f, 0.f, 639.10603f,
                         0.f, 1214.25279f, 484.7274f,
                         0.f, 0.f, 1.f};

        _distortionCoefficients = {-0.479922f, 0.278691f, -0.000137f, 0.000710f, 0.f};
    }
    else if (_cameraType == CameraType::MDC3_120) // obtained with cv::fisheye::calibrate()
    {
        _cameraMatrix = {631.1520782571031f, 0.0f, 649.8469891056759f,
                         0.f, 630.2008683008255f, 494.5608552948983f,
                         0.f, 0.f, 1.f};

        _distortionCoefficients = {-0.000852221592701229f, -0.002021302848618454f, 0.009273264304481579f, -0.00558289649465117f};
    }
    else if (_cameraType == CameraType::KOWA_6MM) // acA1920-40uc Kowa 6mm 1_8
    {
        _cameraMatrix = {1060.45125f, 0.f, 970.25025f,
                         0.f, 1059.68604f, 609.87367f,
                         0.f, 0.f, 1.f};

        _distortionCoefficients = {-0.132717f, 0.053377f, 0.000166f, -0.000108f, 0.f};
    }
    else
    {
        std::cout << "WARNING: Wrong or unsupported camera type" << std::endl;
    }
}
