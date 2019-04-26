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
	auto mat = imread("D:/Qsync/Code/DIP/DigitalImageProcessing/src/Data/DIP3E_CH02_Original_Images/Fig0222(b)(cameraman).tif",0);
	cvtColor(mat, mat, CV_8UC1);
	cout << mat.rows << " " << mat.cols << endl;
	Mat tmp;
	
	timer.Reset();
	tmp = BilinearInterpolation(mat,512,512);
	auto t = timer.GetTime();
	cout << "BilinearInterpolation time: "<<t.count() << endl;

	timer.Reset();
	auto tmp2 = TripleInterpolation(mat, 512, 512);
	auto t2 = timer.GetTime();
	cout << "TripleInterpolation time: "<<t2.count() << endl;

	imwrite("2.jpg", tmp);
	imwrite("3.jpg", tmp2);
	imshow("src", mat);
	imshow("BilinearInterpolation", tmp);
	imshow("TripleInterpolation", tmp2);

	waitKey();

	//Matrix3d A2;
	//A2 << 1, 2, 3,
	//	3, 1, 2,
	//	1, 2, 0;
	//Vector3d B2(14, 11, 5);
	//Vector3d x12 = A2.colPivHouseholderQr().solve(B2); //right Answer    
	//Vector3d x62 = A2.lu().solve(B2);                  // right Answer

	//std::cout << A2 << std::endl;
	//std::cout << "The solution is:\n" << x12 << "\n\n" << x62 << std::endl;


	system("pause");
	return 0;
}