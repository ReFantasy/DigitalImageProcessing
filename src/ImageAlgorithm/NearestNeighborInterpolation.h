#ifndef __NearestNeighborInterpolation_H__
#define __NearestNeighborInterpolation_H__
#include "opencv2/opencv.hpp"
using namespace cv;

// 双线性内插
Mat NearestNeighborInterpolation(const Mat &input, int row, int col);

#endif//__NearestNeighborInterpolation_H__
