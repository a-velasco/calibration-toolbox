#pragma once

#include <opencv2/core/core.hpp>
#include "calibration.h"

class Undistortion final
{
public:
    Undistortion() noexcept {}
    Undistortion(std::vector<float> &cameraMatrix,
                 std::vector<float> &distortionCoefficients) noexcept;

    void setInputImagePath(const std::string &input) { _inputImagePath = input; }
    void setOutputImagePath(const std::string &output) { _outputImagePath = output; }

    std::string &getInputImagePath() { return _inputImagePath; }
    std::string &getOutputImagePath() { return _outputImagePath; }

    void setCameraMatrixCvMat(cv::Mat &K) { _cameraMatrixCvMat = K; }
    void setDistortionCoefficientsCvMat(cv::Mat &d) { _distortionCoefficientsCvMat = d; }

    void setCameraType(Calibration::CameraType type) { _cameraType = type; }
    Calibration::CameraType getCameraType() { return _cameraType; }

    cv::Mat &getMap1() { return _map1; }
    cv::Mat &getMap2() { return _map2; }

    /// Computes undistortion maps, applies undistortion, and writes image to _outputImagePath
    void undistort();

private:
    cv::Mat _cameraMatrixCvMat{};
    cv::Mat _distortionCoefficientsCvMat{};

    Calibration::CameraType _cameraType{Calibration::CameraType::MDC3_60};

    cv::Mat _map1{};
    cv::Mat _map2{};

    std::string _inputImagePath{};
    std::string _outputImagePath{};
};
