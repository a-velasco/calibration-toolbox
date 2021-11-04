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

void writeCalibrationFile(const std::string &path, cv::Mat &cameraMatrix, cv::Mat &distortionCoefficients, cv::Mat &map1, cv::Mat &map2)
{
    cv::FileStorage file(path, cv::FileStorage::WRITE);
    file << "camera_matrix" << cameraMatrix;
    file << "distortion_coefficients" << distortionCoefficients;
    file << "map1" << map1;
    file << "map2" << map2;
    file.release();
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
    std::string inputImagesPath = checkPath(input.getArgument("--inputDir"));
    std::string outputPath = checkPath(input.getArgument("--outputDir"));
    std::string cameraTypeArg = input.getArgument("--cameraType");
    std::string chessW = input.getArgument("--chessboardW");
    std::string chessH = input.getArgument("--chessboardH");

    Calibration::CameraType cameraType;
    auto result = parseCameraType(cameraTypeArg, cameraType);
    if (!result)
    {
        std::cout << "Incorrect camera type: " + cameraTypeArg << std::endl;
        printUsage(argv[0]);
    }

    // Prepare classes
    Calibration calibration;
    calibration.setInputImagesPath(inputImagesPath);
    calibration.setCameraType(cameraType);
    calibration.setChessboardW(std::stoi(chessW));
    calibration.setChessboardH(std::stoi(chessH));

    calibration.calibrate();
    // calibration.getExistingCalibration();

    // Compute undistortion on an image
    std::vector<cv::String> images;
    std::string path = inputImagesPath + "*.jpg";
    cv::glob(path, images);

    Undistortion undistortion;
    undistortion.setCameraType(cameraType);
    undistortion.setCameraMatrixCvMat(calibration.getCameraMatrixCvMat());
    undistortion.setDistortionCoefficientsCvMat(calibration.getDistortionCoefficientsCvMat());
    undistortion.setInputImagePath(images[0]);
    undistortion.setOutputImagePath(outputPath + "undistorted.jpg");
    undistortion.undistort();

    std::string outputYamlFile = outputPath + "calibration.yaml";
    writeCalibrationFile(outputYamlFile,
                         calibration.getCameraMatrixCvMat(),
                         calibration.getDistortionCoefficientsCvMat(),
                         undistortion.getMap1(),
                         undistortion.getMap2());
    return 0;
}