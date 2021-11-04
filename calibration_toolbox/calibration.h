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

    cv::Mat &getCameraMatrixCvMat() { return _cameraMatrixCvMat; }
    cv::Mat &getDistortionCoefficientsCvMat() { return _distortionCoefficientsCvMat; }

    void setChessboardW(int w) { _chessboardW = w; }
    void setChessboardH(int h) { _chessboardH = h; }

    /// Gets cameraMatrix and distortionCoefficients for _cameraType based on an existing OpenCV calibration.
    void getExistingCalibration();

    /// Detects corners and finds camera matrix + distortion coeffs for set of chessboard images in _inputImagesPath.
    void calibrate();

private:
    cv::Mat _cameraMatrixCvMat{};
    cv::Mat _distortionCoefficientsCvMat{};

    CameraType _cameraType{CameraType::MDC3_60};

    std::string _inputImagesPath{}; /// Path to set of chessboard images

    int _chessboardW{5};
    int _chessboardH{8};
};
