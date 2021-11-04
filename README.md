# Camera Calibration & Undistortion Toolbox
This repository is for scripts and executables that we can use to calibrate and undistort images from different cameras. Until our long-term needs are further clarified, it is not yet a unified process, so please refer to this README for specific instructions.

## Build and install
First, you'll need OpenCV. (TODO in future: Add to repo as a static lib.)
https://linuxize.com/post/how-to-install-opencv-on-ubuntu-20-04/

Then, in the repository directory,
```sh
mkdir build && cd build
cmake ..
cmake --build .
```

## To generate a calibration profile
Given a directory with chessboard images, this program will calculate and save calibration and undistortion parameters to a .yaml file.
```sh
./generate_calibration --inputDir ~/your/input/imgs --outputDir ~/your/output/txt --cameraType type --chessboardW width --chessboardH height
```
Where `type` can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 

The output .yaml file will include: camera matrix, distortion coefficients, undistortion map1, undistortion map2

Example:
```sh
./generate_calibration --inputDir /home/avelasco/CalibFiles/mdc3_60/original --outputDir /home/avelasco/CalibFiles/mdc3_60/ --cameraType mdc3_60 --chessboardW 5 --chessboardH 8
```

## To undistort a list of images
`undistort_images` uses a set of pre-computed calibrations and applies an undistortion to the images in the given directory.
```sh
./undistort_images --inputDir home/calibration/distorted_images/ --outputDir home/calibration/undistorted_images/  --cameraType type
```
Where `type` can be:
- mdc3_120
- mdc3_60
- kowa3_5mm
- TODO? ~~Smount~~ 
- TODO? ~~6mm_1_8~~ 

Example:
```sh
.undistort_images --inputDir /home/avelasco/CalibFiles/mdc3_60/original/ --outputDir /home/avelasco/CalibFiles/mdc3_60/undistorted/ --cameraType mdc3_60
```