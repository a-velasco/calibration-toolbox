#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>
#include <vector>

enum class CameraType
{
    MDC3_60,
    MDC3_120,
    KOWA_6MM
};

void getCalibrationInfo(CameraType type, std::vector<float> &cameraMatrixData, std::vector<float> &distCoeffsData)
{
    if (type == CameraType::MDC3_60)
    {
        cameraMatrixData = {1216.44437f, 0.f, 639.10603f,
                            0.f, 1214.25279f, 484.7274f,
                            0.f, 0.f, 1.f};

        distCoeffsData = {-0.479922f, 0.278691f, -0.000137f, 0.000710f, 0.f};
    }
    else if (type == CameraType::MDC3_120)
    {
        cameraMatrixData = {638.23556f, 0.f, 636.35528f,
                            0.f, 636.55505f, 495.6578f,
                            0.f, 0.f, 1.f};

        distCoeffsData = {-0.272714f, 0.060136f, -0.000840f, 0.000259f, 0.f};
    }
    else if (type == CameraType::KOWA_6MM)
    {
        cameraMatrixData = {1060.45125f, 0.f, 970.25025f,
                            0.f, 1059.68604f, 609.87367f,
                            0.f, 0.f, 1.f};

        distCoeffsData = {-0.132717f, 0.053377f, 0.000166f, -0.000108f, 0.f};
    }
}

int main(int argc, char **argv)
{
    // Configuration
    std::string folderPath = "/home/avelasco/CalibFiles/calibrationMDC3_120/";
    std::string imagePath = "left-0046.jpg";
    CameraType type = CameraType::MDC3_120;

    cv::Mat inputImage;
    inputImage = cv::imread(folderPath + imagePath);
    if (inputImage.empty())
    {
        std::cout << "Image import failed" << std::endl;
        return 1;
    }
    cv::Mat distortedImage(inputImage); //save copy to variable

    std::vector<float> cameraMatrixData, distCoeffsData;
    getCalibrationInfo(type, cameraMatrixData, distCoeffsData);

    cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32F, &cameraMatrixData[0]);
    cv::Mat distCoeffs = cv::Mat(1, 5, CV_32F, &distCoeffsData[0]);

    cv::Mat outputImage, map1, map2, new_camera_matrix;
    cv::Size imageSize(cv::Size(inputImage.cols, inputImage.rows));

    // Method 1 to undistort the image (Does not work propertly for MDC3 120 for some reason)
    // Refining the camera matrix using parameters obtained by calibration
    // new_camera_matrix = cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0);
    // cv::undistort(inputImage, outputImage, new_camera_matrix, distCoeffs, new_camera_matrix);

    // Method 2 to undistort the image
    cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0), imageSize, CV_16SC2, map1, map2);
    cv::remap(inputImage, outputImage, map1, map2, cv::INTER_LINEAR);

    // Method 3 (fisheye)
    // cv::Mat fisheyeDistCoeffs = {-0.272714f, 0.060136f, -0.000840f, 0.000259f};
    // cv::fisheye::undistortImage(inputImage, outputImage, cameraMatrix, fisheyeDistCoeffs);

    //Displaying the undistorted image
    cv::imshow("undistorted image", outputImage);
    cv::imshow("original image", distortedImage);

    cv::imwrite(folderPath + imagePath + "-undistorted.jpg", outputImage);

    cv::waitKey(0);
}