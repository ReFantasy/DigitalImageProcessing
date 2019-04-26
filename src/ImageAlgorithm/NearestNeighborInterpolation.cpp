#include "NearestNeighborInterpolation.h"

Mat NearestNeighborInterpolation(const Mat &input, int new_row, int new_col)
{

	cv::Mat out(new_row, new_col, CV_8UC1);

	int input_rows = input.rows;
	int input_cols = input.cols;
	double scale_x = new_row / (double)input_rows;
	double scale_y = new_col / (double)input_cols;

	auto pInput = input.data;
	auto pOut = out.data;

	for (size_t x = 0; x < new_row; x++)
	{
		for (size_t y = 0; y < new_col; y++)
		{
			int tmpx = x / scale_x;
			int tmpy = y / scale_y;
			if (tmpx > input_rows - 1)
				tmpx = input_rows - 1;
			if (tmpy > input_cols - 1)
				tmpy = input_cols - 1;

			pOut[x*new_col + y] = pInput[tmpx*input_cols + tmpy];
		}
	}

	return out;
}
