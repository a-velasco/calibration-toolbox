// #include <opencv2/opencv.hpp>
// #include <opencv2/calib3d/calib3d.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <stdio.h>
// #include <iostream>

// namespace
// {
//     constexpr int W = 8;
//     constexpr int H = 5;

//     constexpr int imgW = 1280;
//     constexpr int imgH = 960;
// }

// void getCalibrationDataOld(std::vector<std::vector<cv::Point3f>> &objpoints, //
//                            std::vector<std::vector<cv::Point2f>> &imgpoints, //
//                            cv::Size graySize,                                //
//                            std::vector<std::string> &sources)
// {
//     std::vector<std::string> fileNames = {"/home/avelasco/CalibFiles/calibrationMDC3_120/left-0000.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0001.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0002.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0003.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0004.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0005.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0006.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0007.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0008.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0009.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0010.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0011.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0012.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0013.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0014.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0015.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0016.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0017.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0018.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0019.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0020.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0021.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0022.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0023.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0024.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0025.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0026.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0027.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0028.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0029.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0030.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0031.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0032.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0033.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0034.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0035.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0036.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0037.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0038.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0039.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0040.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0041.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0042.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0043.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0044.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0045.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0046.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0047.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0048.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0049.jpg",
//                                           "/home/avelasco/CalibFiles/calibrationMDC3_120/left-0050.jpg"};
//     const cv::Size checkerBoard(W, H);
//     std::vector<cv::Point3f> objp;

//     for (int v = 0; v < checkerBoard.height; ++v)
//     {
//         for (int u = 0; u < checkerBoard.width; ++u)
//         {
//             objp.push_back(cv::Point3f(float(u), float(v), 0));
//         }
//     }
//     for (int i = 0; i < fileNames.size(); ++i)
//     {
//         std::string fileName = fileNames[i];
//         if (fileName.begin()[0] == '-')
//             continue;
//         std::cout << "Processing " << fileName << "..." << std::endl;
//         cv::Mat source = cv::imread(fileName);
//         if (source.empty())
//         {
//             std::cout << "Failed to imread(" << fileName << ")." << std::endl;
//             continue;
//         }
//         cv::Mat gray;
//         cv::cvtColor(source, gray, cv::COLOR_RGB2GRAY);
//         if (graySize.area() == 0)
//         {
//             graySize = gray.size();
//         }
//         else if (gray.size() != graySize)
//         {
//             std::cout << "Invalid image size: " << fileName << " - expect " << graySize << ", but " << gray.size() << std::endl;
//             continue;
//         }
//         sources.push_back(fileName);
//         std::vector<cv::Point2f> corners;
//         int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
//         if (!cv::findChessboardCorners(source, checkerBoard, corners, flags))
//         {
//             std::cout << "Failed to findChessboardCorners(" << fileName << ")." << std::endl;
//             continue;
//         }
//         objpoints.push_back(objp);
//         cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1);
//         cv::cornerSubPix(source, corners, cv::Size(3, 3), cv::Size(-1, -1), criteria);
//         imgpoints.push_back(corners);
//     }
// }

// std::vector<std::vector<cv::Point2f>> getCalibrationData(std::vector<std::vector<cv::Point3f>> &objpoints,
//                                                          std::vector<std::string> &fileNames)
// {
//     cv::glob("/home/avelasco/CalibFiles/calibrationMDC3_120/*.jpg", fileNames, false);

//     std::vector<std::vector<cv::Point2f>> imgpoints; //(fileNames.size());

//     cv::Size patternSize(W - 1, H - 1);

//     // Defining the world coordinates for 3D points
//     int checkerBoard[2] = {W, H};
//     std::vector<cv::Point3f> objp;
//     for (int i = 1; i < checkerBoard[1]; i++)
//     {
//         for (int j = 1; j < checkerBoard[0]; j++)
//         {
//             objp.push_back(cv::Point3f(j, i, 0));
//         }
//     }

//     std::vector<cv::Point2f> imgPoint;
//     // Detect feature points
//     std::size_t i = 0;
//     for (auto const &f : fileNames)
//     {
//         std::cout << std::string(f) << std::endl;

//         // 2. Read in the image an call cv::findChessboardCorners()
//         cv::Mat img = cv::imread(fileNames[i]);
//         cv::Mat gray;

//         cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

//         std::vector<cv::Point2f> corners;
//         int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK;
//         bool patternFound = cv::findChessboardCorners(gray, patternSize, corners, flags);

//         objpoints.push_back(objp);
//         if (patternFound)
//         {
//             cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1);
//             cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
//         }
//         imgpoints.push_back(corners);

//         // bool patternFound = cv::findChessboardCorners(gray, patternSize, imgpoints[i], cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);
//         // objpoints.push_back(objp);

//         // 2. Use cv::cornerSubPix() to refine the found corner detections
//         // if (patternFound)
//         // {
//         //     cv::cornerSubPix(gray, imgpoints[i], cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
//         // }

//         // Display
//         cv::drawChessboardCorners(img, patternSize, imgpoints[i], patternFound);
//         cv::imshow("chessboard detection", img);
//         cv::waitKey(0);

//         i++;
//     }

//     return imgpoints;
// }

// int main(int argc, char *argv[])
// {
//     std::vector<std::vector<cv::Point3f>> objpoints;
//     cv::Size imgSize(imgW, imgH);

//     std::vector<std::string> fileNames;

//     std::cout << "cv::findChessboardCorners..." << std::endl;
//     auto imgpoints = getCalibrationData(objpoints, fileNames);

//     if (objpoints.empty() || imgpoints.empty())
//     {
//         std::cout << "No corners found" << std::endl;
//         return 1;
//     }

//     std::cout << "cv::fisheye::calibrate()..." << std::endl;
//     cv::Mat K, D;
//     std::vector<cv::Mat> rvecs, tvecs;
//     int flags = cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC | cv::fisheye::CALIB_FIX_SKEW;
//     cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 1e-6);

//     cv::InputArrayOfArrays temp(imgpoints);
//     cv::fisheye::calibrate(objpoints, temp, imgSize, K, D, rvecs, tvecs, flags, criteria);

//     std::cout
//         << "K=" << K << std::endl
//         << "D=" << D << std::endl;

//     cv::Mat map1, map2;
//     cv::fisheye::initUndistortRectifyMap(K, D, cv::Mat::eye(3, 3, CV_32F), K, imgSize, CV_16SC2, map1, map2);

//     for (auto fileName : fileNames)
//     {
//         cv::Mat source = cv::imread(fileName);
//         cv::Mat undistort;
//         cv::remap(source, undistort, map1, map2, cv::INTER_LINEAR, cv::BORDER_CONSTANT);

//         cv::Mat result;
//         cv::hconcat(source, undistort, result);
//         cv::resize(result, result, cv::Size(), 0.25, 0.25);
//         cv::imshow("result", result);
//         cv::waitKey();
//     }

//     return 0;
// }