#include <iostream>
#include "opencv2/opencv.hpp"
#include "ImageAlgorithm/NearestNeighborInterpolation.h"
#include "ImageAlgorithm/BilinearInterpolation.h"
#include "ImageAlgorithm/TripleInterpolation.h"
#include "Assist/TIMER.h"
#include "Eigen/Dense"

using namespace std;
using namespace cv;
using namespace Eigen;

TIMER timer;
int main()
{
	auto src = imread("D:/Qsync/Code/DIP/DigitalImageProcessing/src/Data/DIP3E_CH02_Original_Images/Fig0227(a)(washington_infrared).tif",0);
	Mat tmp1;
	src.copyTo(tmp1);

	cvtColor(tmp1, tmp1, CV_8UC1);
	auto pdata = tmp1.data;

	for (int i = 0; i < tmp1.rows * tmp1.cols; i++)
	{
		uchar tmp = 0xfe;
		pdata[i] = (pdata[i] & tmp);
	}
	
	Mat diff(src.rows,src.cols, CV_8UC1);
	
	for (int i = 0; i < tmp1.rows * tmp1.cols; i++)
	{
		
		diff.data[i] = src.data[i] - tmp1.data[i];
	}
	for (int i = 0; i < tmp1.rows * tmp1.cols; i++)
	{

		diff.data[i] = (diff.data[i]==0?0:255);
	}

	imshow("src", src);
	imshow("tmp1", tmp1);
	imshow("diff", diff);
	waitKey();

	return 0;
}