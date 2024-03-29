import cv2

import numpy as np
import sys

# Obtained from running calibrate.py on mdc3_120 chessboard images.
DIM=(1280, 960)
K=np.array([[631.1520782571031, 0.0, 649.8469891056759], [0.0, 630.2008683008255, 494.5608552948983], [0.0, 0.0, 1.0]])
D=np.array([[-0.000852221592701229], [-0.002021302848618454], [0.009273264304481579], [-0.00558289649465117]])

def undistort(img_path, balance=0.0, dim2=None, dim3=None):
    print('undistorting ' + img_path)
    img = cv2.imread(img_path)
    dim1 = img.shape[:2][::-1]  #dim1 is the dimension of input image to un-distort
    assert dim1[0]/dim1[1] == DIM[0]/DIM[1], "Image to undistort needs to have same aspect ratio as the ones used in calibration"
    if not dim2:
        dim2 = dim1
    if not dim3:
        dim3 = dim1
    scaled_K = K * dim1[0] / DIM[0]  # The values of K is to scale with image dimension.
    scaled_K[2][2] = 1.0  # Except that K[2][2] is always 1.0
    # This is how scaled_K, dim2 and balance are used to determine the final K used to un-distort image. OpenCV document failed to make this clear!
    new_K = cv2.fisheye.estimateNewCameraMatrixForUndistortRectify(scaled_K, D, dim2, np.eye(3), balance=1)
    map1, map2 = cv2.fisheye.initUndistortRectifyMap(scaled_K, D, np.eye(3), new_K, dim3, cv2.CV_16SC2)
    undistorted_img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)

    # cv2.imshow("undistorted", undistorted_img)
    new_path = img_path.replace("original", "undistorted")
    print('saving ' + new_path)
    cv2.imwrite(new_path, undistorted_img)

    # cv2.waitKey(0)
    # cv2.destroyAllWindows()
if __name__ == '__main__':
    for p in sys.argv[1:]:
        undistort(p)


# def undistort(img_path):
#     img = cv2.imread(img_path)
#     h,w = img.shape[:2]
#     map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), K, DIM, cv2.CV_16SC2)
#     undistorted_img = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)
#     cv2.imshow("undistorted", undistorted_img)
#     cv2.waitKey(0)
#     cv2.destroyAllWindows()
# if __name__ == '__main__':
#     for p in sys.argv[1:]:
#         undistort(p)