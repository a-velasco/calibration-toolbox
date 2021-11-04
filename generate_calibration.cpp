#include "calibration_toolbox/undistortion.h"
#include "calibration_toolbox/calibration.h"
#include "utils/input_parser.hpp"

#include <iostream>

namespace
{
    void printUsage(char *exe)
    {
        std::cerr << "Usage: " << exe << "\n"
                  << "--inputDir    :  Directory containing chessboard .jpg images\n"
                  << "--outputDir   : .txt output file directory\n"
                  << "--cameraType  : 'mdc3_60', 'pylon', or 'mdc3_120'\n"
                  << "--chessboardW : Number of corners along width\n"
                  << "--chessboardH : Number of corners along height\n";
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
    // Handle cli inputs
    InputParser input(argc, argv);
    std::string originalImagesPath = input.getArgument("--inputDir");
    std::string outputImagesPath = input.getArgument("--outputDir");
    std::string cameraTypeArg = input.getArgument("--cameraType");

    Calibration::CameraType cameraType;
    auto result = parseCameraType(cameraTypeArg, cameraType);
    if (!result)
    {
        std::cout << "Incorrect camera type: " + cameraTypeArg << std::endl;
        printUsage(argv[0]);
    }

    // Prepare classes
    Calibration calibration;
    calibration.setInputImagesPath(originalImagesPath);
    calibration.setCameraType(cameraType);

    calibration.calibrate();
    // calibration.getExistingCalibration();

    std::cout << "Camera mat:" << std::endl
              << " " << calibration.getCameraMatrixCvMat() << std::endl
              << std::endl;
    std::cout << "Distortion coeffs:" << std::endl
              << " " << calibration.getDistortionCoefficientsCvMat() << std::endl
              << std::endl;

    // DEBUG: Optionally use calibration to undistort an image
    // Undistortion undistort;
    // undistort.setCameraType(cameraType);
    // undistort.setCameraMatrixCvMat(calibration.getCameraMatrixCvMat());
    // undistort.setDistortionCoefficientsCvMat(calibration.getDistortionCoefficientsCvMat());
    // undistort.setInputImagePath(originalImagesPath + "left-0008.jpg");
    // undistort.setOutputImagePath(outputImagesPath + "generate_calib_left-0008.jpg");
    // undistort.undistort();

    return 0;
}