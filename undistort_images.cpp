#include "calibration_toolbox/undistortion.h"
#include "calibration_toolbox/calibration.h"

#include <iostream>

class InputParser
{
public:
    InputParser(int &argc, char **argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }

    const std::string &getArgument(const std::string &option) const
    {
        std::vector<std::string>::const_iterator it;
        it = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (it != this->tokens.end() && ++it != this->tokens.end())
        {
            return *it;
        }
        static const std::string emptyString("");
        return emptyString;
    }

private:
    std::vector<std::string> tokens;
};

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

int main(int argc, char **argv)
{
    InputParser input(argc, argv);

    auto cameraTypeArg = input.getArgument("--cameraType");

    Undistortion undistortion;
    if (cameraTypeArg == "mdc3_60")
    {
        undistortion.setCameraType(Calibration::CameraType::MDC3_60);
    }
    else if (cameraTypeArg == "mdc3_120")
    {
        undistortion.setCameraType(Calibration::CameraType::MDC3_120);
    }
    else if (cameraTypeArg == "pylon")
    {
        undistortion.setCameraType(Calibration::CameraType::KOWA_6MM);
    }
    else
    {
        std::cout << "Incorrect camera type: " + cameraTypeArg << std::endl;
        printUsage(argv[0]);
        return 1;
    }

    Calibration calibration;
    calibration.setCameraType(undistortion.getCameraType());
    calibration.getExistingCalibration();

    undistortion.setCameraMatrix(calibration.getCameraMatrix());
    undistortion.setDistortionCoefficients(calibration.getDistortionCoefficients());

    auto inputPath = checkPath(input.getArgument("--inputDir"));
    auto outputPath = checkPath(input.getArgument("--outputDir"));

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