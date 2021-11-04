#include "calibration_toolbox/undistortion.h"
#include "calibration_toolbox/calibration.h"
#include <iostream>

int main()
{
    std::string originalImagesPath = "/home/avelasco/CalibFiles/mdc3_60/original/";
    std::string outputImagesPath = "/home/avelasco/CalibFiles/mdc3_60/TEST/";
    Calibration::CameraType camera = Calibration::CameraType::MDC3_60;

    //////////////////////////////////////////////////////////////////////////////////

    Calibration calibration;

    calibration.setInputImagesPath(originalImagesPath);
    calibration.setCameraType(camera);

    // calibration.calibrate();
    calibration.getExistingCalibration();

    std::cout << "Camera mat:" << std::endl
              << " " << calibration.getCameraMatrixCvMat() << std::endl
              << std::endl;
    std::cout << "Distortion coeffs:" << std::endl
              << " " << calibration.getDistortionCoefficientsCvMat() << std::endl
              << std::endl;

    Undistortion undistort;
    undistort.setCameraType(camera);
    undistort.setCameraMatrixCvMat(calibration.getCameraMatrixCvMat());
    undistort.setDistortionCoefficientsCvMat(calibration.getDistortionCoefficientsCvMat());
    undistort.setInputImagePath(originalImagesPath + "left-0008.jpg");
    undistort.setOutputImagePath(outputImagesPath + "generate_calib_left-0008-new.jpg");

    undistort.undistort();
}