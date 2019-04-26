#include <iostream>
#include "opencv2/opencv.hpp"
#include "Assist/Assist.h"
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
	auto mat = imread("C:/Users/30974/Desktop/SrcImage/DIP3E_Original_Images_CH02/Fig0220(a)(chronometer 3692x2812  2pt25 inch 1250 dpi).tif",0);
	mat = ConverToCV8UC1(mat);
	cout << mat.rows << " " << mat.cols << endl;
	Mat tmp;
	
	timer.Reset();
	tmp = BilinearInterpolation(mat,7200,5600);
	auto t = timer.GetTime();
	cout << "BilinearInterpolation time: "<<t.count() << endl;

	timer.Reset();
	auto tmp2 = TripleInterpolation(mat, 7200, 5600);
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