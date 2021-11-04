#pragma once

#include <opencv2/core/core.hpp>

class Calibration final
{
public:
    Calibration() noexcept {}

    enum class CameraType
    {
        MDC3_60, // default
        MDC3_120,
        KOWA_6MM
    };

    void setInputImagesPath(const std::string &inputPath) { _inputImagesPath = inputPath; }

    void setCameraType(CameraType type) { _cameraType = type; }
    CameraType getCameraType() { return _cameraType; }

    std::vector<float> &getCameraMatrix() { return _cameraMatrix; }
    std::vector<float> &getDistortionCoefficients() { return _distortionCoefficients; }

    /// Gets cameraMatrix and distortionCoefficients for _cameraType based on previously done
    /// OpenCV calibration.
    void getExistingCalibration();

    // TODO: Implement cv::calibrate and cv::fisheye::calibrate for given set of chessboard images.
    // void calibrate();

private:
    std::vector<float> _cameraMatrix{};
    std::vector<float> _distortionCoefficients{};

    CameraType _cameraType{CameraType::MDC3_60};

    std::string _inputImagesPath{}; /// Path to set of chessboard images
};
