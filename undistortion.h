#pragma once

#include <opencv2/core/core.hpp>

class Undistortion final
{
public:
    Undistortion();

    enum class CameraType
    {
        MDC3_60, // default
        MDC3_120,
        KOWA_6MM
    };

    void setInputImagePath(const std::string &inputPath) { inputImagePath = inputPath; }

    void setOutputImagePath(const std::string &outputPath) { outputImagePath = outputPath; }

    void setCameraType(CameraType type);

    void undistortOpenCv();
    void undistort();

private:
    std::vector<float> cameraMatrix{};
    std::vector<float> distortionCoefficients{};

    CameraType cameraType{CameraType::MDC3_60};

    std::string inputImagePath{};
    std::string outputImagePath{};
};
