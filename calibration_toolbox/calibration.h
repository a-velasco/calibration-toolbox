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

    cv::Mat &getCameraMatrixCvMat() { return _cameraMatrixCvMat; }
    cv::Mat &getDistortionCoefficientsCvMat() { return _distortionCoefficientsCvMat; }

    /// Gets cameraMatrix and distortionCoefficients for _cameraType based on an existing OpenCV calibration.
    void getExistingCalibration();

    /// Detects corners and finds camera matrix + distortion coeffs for set of chessboard images in _inputImagesPath.
    void calibrate();

private:
    std::vector<float> _cameraMatrix{};
    std::vector<float> _distortionCoefficients{};

    cv::Mat _cameraMatrixCvMat{};
    cv::Mat _distortionCoefficientsCvMat{};

    CameraType _cameraType{CameraType::MDC3_60};

    std::string _inputImagesPath{}; /// Path to set of chessboard images

    const int _chessboardW{5};
    const int _chessboardH{8};
};
