#include "undistortion.h"

namespace
{
    const std::string ORIGINAL = "original/";
    const std::string METHOD_1 = "undistorted_method1/"; // cv::undistort - NOT USED
    const std::string METHOD_2 = "undistorted_method2/"; // cv::initUndistortRectifyMap
}

int main()
{
    Undistortion undistortion;
    undistortion.setCameraType(Undistortion::CameraType::MDC3_60);

    std::string cameraFolderPath = "/home/avelasco/CalibFiles/mdc3_60/";
    std::vector<std::string> inputImages;
    cv::glob(cameraFolderPath + ORIGINAL + "*.jpg", inputImages, false);

    for (const auto &inputImage : inputImages)
    {
        size_t pos = inputImage.find(ORIGINAL);
        std::string outputImage = inputImage;
        outputImage.replace(pos, ORIGINAL.length(), "TEST/");

        undistortion.setInputImagePath(inputImage);
        undistortion.setOutputImagePath(outputImage);

        undistortion.undistortOpenCv();
    }
}