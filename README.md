# Camera Undistortion Toolbox
This repository is for scripts and executables that we can use to calibrate and undistort images from different cameras. Until our long-term needs are further clarified, it is not yet a unified process, so please refer to this README.


## To generate a calibration profile
Given a directory with chessboard images, this program will calculate and save calibration and undistortion parameters to a .txt file.
Build the repository with CMake and run:
```sh
.generate_calibration --cameraType type --chessboardW width --chessboardH height --inputDir ~/your/input/imgs --outputDir ~/your/output/txt
```
Where `type`can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 

## To undistort a directory of images
Build the repository with CMake and run:
```sh
.undistort_images --cameraType type --inputDir ~/your/input/imgs --outputDir ~/your/output/imgs
```
Where `type`can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 