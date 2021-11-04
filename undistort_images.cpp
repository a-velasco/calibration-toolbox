#include "calibration_toolbox/undistortion.h"
#include "calibration_toolbox/calibration.h"
#include "utils/input_parser.hpp"

#include <iostream>

namespace
{
    void printUsage(char *exe)
    {
        std::cerr << "Usage: " << exe << "\n"
                  << "--inputDir   : directory containing .jpg images to undistort\n"
                  << "--outputDir  : directory to write undistorted images\n"
                  << "--cameraType : 'mdc3_60', 'pylon', or 'mdc3_120'\n";
    }

    const std::string checkPath(std::string path)
    {
        return path.back() == '/' ? path : path + '/';
    }

    bool parseCameraType(const std::string &cameraTypeArg, Calibration::CameraType &cameraType)
    {
        if (cameraTypeArg == "mdc3_60")
        {
            cameraType = Calibration::CameraType::MDC3_60;
            return true;
        }
        else if (cameraTypeArg == "mdc3_120")
        {
            cameraType = Calibration::CameraType::MDC3_120;
            return true;
        }
        else if (cameraTypeArg == "pylon")
        {
            cameraType = Calibration::CameraType::KOWA_6MM;
            return true;
        }
        else
        {
            return false;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        printUsage(argv[0]);
        return 1;
    }

    // Handle cli inputs
    InputParser input(argc, argv);
    auto inputPath = checkPath(input.getArgument("--inputDir"));
    auto outputPath = checkPath(input.getArgument("--outputDir"));
    std::string cameraTypeArg = input.getArgument("--cameraType");

    Calibration::CameraType cameraType;
    auto result = parseCameraType(cameraTypeArg, cameraType);
    if (!result)
    {
        std::cout << "Incorrect camera type: " + cameraTypeArg << std::endl;
        printUsage(argv[0]);
    }

    // Prepare classes
    Undistortion undistortion;
    undistortion.setCameraType(cameraType);

    Calibration calibration;
    calibration.setCameraType(cameraType);
    calibration.getExistingCalibration();

    undistortion.setCameraMatrixCvMat(calibration.getCameraMatrixCvMat());
    undistortion.setDistortionCoefficientsCvMat(calibration.getDistortionCoefficientsCvMat());

    std::vector<std::string> inputImages;
    cv::glob(inputPath + "*.jpg", inputImages, false);

    std::string outputImage = "";

    for (const auto &inputImage : inputImages)
    {
        // Parse out image name to construct outputImage path
        std::string imgName = inputImage.substr(inputImage.find_last_of("/") + 1);
        outputImage = outputPath + imgName;

        undistortion.setInputImagePath(inputImage);
        undistortion.setOutputImagePath(outputImage);
        undistortion.undistort();
    }

    return 0;
}