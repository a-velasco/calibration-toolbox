#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

void getCalibrationData2(std::vector<std::vector<cv::Point3f>> &objpoints, //
                         std::vector<std::vector<cv::Point2f>> &imgpoints, //
                         cv::Size graySize,                                //
                         std::vector<std::string> &sources)
{
    // Defining the dimensions of checkerboard
    int CHECKERBOARD[2]{6, 9};

    // Defining the world coordinates for 3D points
    std::vector<cv::Point3f> objp;
    for (int i{0}; i < CHECKERBOARD[1]; i++)
    {
        for (int j{0}; j < CHECKERBOARD[0]; j++)
            objp.push_back(cv::Point3f(j, i, 0));
    }

    // Extracting path of individual image stored in a given directory
    std::vector<cv::String> images;
    // Path of the folder containing checkerboard images
    std::string path = "/home/avelasco/CalibFiles/calibrationMDC3_120/*.jpg";

    cv::glob(path, images);

    cv::Mat frame, gray;
    // vector to store the pixel coordinates of detected checker board corners
    std::vector<cv::Point2f> corner_pts;
    bool success;

    // Looping over all the images in the directory
    for (int i{0}; i < images.size(); i++)
    {
        sources.push_back(images[i]);

        frame = cv::imread(images[i]);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        if (graySize.area() == 0)
        {
            graySize = gray.size();
        }
        else if (gray.size() != graySize)
        {
            std::cout << "Invalid image size: " << images[i] << " - expect " << graySize << ", but " << gray.size() << std::endl;
            continue;
        }

        // Finding checker board corners
        // If desired number of corners are found in the image then success = true
        success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);

        /*
        * If desired number of corner are detected,
        * we refine the pixel coordinates and display
        * them on the images of checker board
        */

        if (success)
        {
            cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.001);

            // refining pixel coordinates for given 2d points.
            cv::cornerSubPix(gray, corner_pts, cv::Size(11, 11), cv::Size(-1, -1), criteria);

            // Displaying the detected corner points on the checker board
            cv::drawChessboardCorners(frame, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);

            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);
        }

        cv::imshow("Image", frame);
        cv::waitKey(0);
    }

    cv::destroyAllWindows();
}

void getCalibrationData(std::vector<std::vector<cv::Point3f>> &objpoints, //
                        std::vector<std::vector<cv::Point2f>> &imgpoints, //
                        cv::Size graySize,                                //
                        std::vector<std::string> &sources)
{
    int W = 9;
    int H = 6;
    std::vector<std::string> fileNames = {"/home/avelasco/CalibFiles/calibrationMDC3_120/left-0000.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0001.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0002.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0003.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0004.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0005.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0006.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0007.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0008.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0009.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0010.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0011.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0012.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0013.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0014.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0015.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0016.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0017.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0018.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0019.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0020.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0021.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0022.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0023.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0024.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0025.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0026.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0027.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0028.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0029.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0030.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0031.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0032.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0033.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0034.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0035.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0036.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0037.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0038.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0039.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0040.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0041.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0042.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0043.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0044.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0045.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0046.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0047.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0048.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0049.jpg",
                                          "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0050.jpg"};
    const cv::Size checkerBoard(W, H);
    std::vector<cv::Point3f> objp;

    for (int v = 0; v < checkerBoard.height; ++v)
    {
        for (int u = 0; u < checkerBoard.width; ++u)
        {
            objp.push_back(cv::Point3f(float(u), float(v), 0));
        }
    }
    for (int i = 0; i < fileNames.size(); ++i)
    {
        std::string fileName = fileNames[i];
        if (fileName.begin()[0] == '-')
            continue;
        std::cout << "Processing " << fileName << "..." << std::endl;
        cv::Mat source = cv::imread(fileName);
        if (source.empty())
        {
            std::cout << "Failed to imread(" << fileName << ")." << std::endl;
            continue;
        }
        cv::Mat gray;
        cv::cvtColor(source, gray, cv::COLOR_RGB2GRAY);
        if (graySize.area() == 0)
        {
            graySize = gray.size();
        }
        else if (gray.size() != graySize)
        {
            std::cout << "Invalid image size: " << fileName << " - expect " << graySize << ", but " << gray.size() << std::endl;
            continue;
        }
        sources.push_back(fileName);
        std::vector<cv::Point2f> corners;
        int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
        if (!cv::findChessboardCorners(source, checkerBoard, corners, flags))
        {
            std::cout << "Failed to findChessboardCorners(" << fileName << ")." << std::endl;
            continue;
        }
        objpoints.push_back(objp);
        cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1);
        cv::cornerSubPix(source, corners, cv::Size(3, 3), cv::Size(-1, -1), criteria);
        imgpoints.push_back(corners);
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::vector<cv::Point3f>> objpoints;
    std::vector<std::vector<cv::Point2f>> imgpoints;
    cv::Size graySize;
    std::vector<std::string> sources;

    std::cout << "Finding chessboard corners ..." << std::endl;
    getCalibrationData2(objpoints, imgpoints, graySize, sources);

    if (objpoints.empty() || imgpoints.empty())
    {
        std::cout << "No corners found" << std::endl;
        return 1;
    }

    std::cout
        << "Processing cv::fisheye::calibrate() ..." << std::endl;
    cv::Mat K, D;
    std::vector<cv::Mat> rvecs, tvecs;
    int flags = cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC | cv::fisheye::CALIB_FIX_SKEW;
    cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 1e-6);
    cv::fisheye::calibrate(objpoints, imgpoints, graySize, K, D, rvecs, tvecs, flags, criteria);

    std::cout
        << "K=" << K << std::endl
        << "D=" << D << std::endl;

    cv::Mat map1, map2;
    cv::fisheye::initUndistortRectifyMap(K, D, cv::Mat::eye(3, 3, CV_32F), K, graySize, CV_16SC2, map1, map2);

    for (auto fileName : sources)
    {
        cv::Mat source = cv::imread(fileName);
        cv::Mat undistort;
        cv::remap(source, undistort, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

        cv::Mat result;
        cv::hconcat(source, undistort, result);
        cv::resize(result, result, cv::Size(), 0.25, 0.25);
        cv::imshow("result", result);
        cv::waitKey();
    }

    return 0;
}