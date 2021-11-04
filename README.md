# Camera Undistortion Toolbox
This repository is for scripts and executables that we can use to calibrate and undistort images from different cameras. Until our long-term needs are further clarified, it is not yet a unified process, so please refer to this README.


## To generate a calibration profile
Given a directory with chessboard images, this program will calculate and save calibration and undistortion parameters to a .txt file.
Build the repository with CMake and run:
```sh
.generate_calibration --inputDir ~/your/input/imgs --outputDir ~/your/output/txt --cameraType type --chessboardW width --chessboardH height
```
Where `type`can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 

Example:
```sh
.generate_calibration --inputDir home/calibration/images/ --outputDir home/calibration/files/ --cameraType mdc3_120 --chessboardW 5 --chessboardH 8
```

## To undistort a list of images
Build the repository with CMake and run:
```sh
.undistort_images --inputDir home/calibration/distorted_images/ --outputDir home/calibration/undistorted_images/  --cameraType mdc3_120
```
Where `type`can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 

Example:
```sh
.undistort_images --inputDir home/calibration/images/ --outputDir home/calibration/files/ --cameraType mdc3_120 --chessboardW 5 --chessboardH 8
```