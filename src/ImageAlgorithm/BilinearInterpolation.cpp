#include "BilinearInterpolation.h"

cv::Mat BilinearInterpolation(const Mat &input, int new_row, int new_col)
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

			// 边界点
			if (tmpx == 0 || tmpx == input_rows - 1 || tmpy == 0 || tmpy == input_cols - 1)
			{
				pOut[x*new_col + y] = pInput[tmpx*input_cols + tmpy];
			}
			// 计算上下左右四个点的值，求四元二次方程组 AX = B
			else
			{
				Matrix4d A;
				A << (tmpx - 1), tmpy, (tmpx - 1)*tmpy, 1,
					(tmpx + 1), tmpy, (tmpx + 1)*tmpy, 1,
					tmpx, tmpy - 1, tmpx*(tmpy - 1), 1,
					tmpx, tmpy + 1, tmpx*(tmpy + 1), 1;

				
				double v_up = pInput[(tmpx-1)*input_cols + tmpy];
				double v_bottom = pInput[(tmpx+1)*input_cols + tmpy];
				double v_left = pInput[tmpx*input_cols + tmpy-1];
				double v_right = pInput[tmpx*input_cols + tmpy+1];
				Vector4d B(v_up, v_bottom, v_left, v_right);

				Vector4d X = A.colPivHouseholderQr().solve(B);

				pOut[x*new_col + y] = tmpx*X[0]+tmpy*X[1]+tmpx*tmpy*X[2]+X[3];
			}
			
		}
	}

	return out;
}
