#include "TripleInterpolation.h"

cv::Mat TripleInterpolation(const Mat &input, int new_row, int new_col)
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
			int tmpx = round(x / scale_x);
			int tmpy = round(y / scale_y);
			if (tmpx > input_rows - 1)
				tmpx = input_rows - 1;
			if (tmpy > input_cols - 1)
				tmpy = input_cols - 1;

			// 边界点
			if (tmpx == 0 || tmpx == input_rows - 1 || tmpy == 0 || tmpy == input_cols - 1 ||
				tmpx == 1 || tmpx == input_rows - 2 || tmpy == 1 || tmpy == input_cols - 2
				)
			{
				pOut[x*new_col + y] = pInput[tmpx*input_cols + tmpy];
			}
			// 计算周围16个点值，求16元二次方程组 AX = B
			else
			{
				////////////////////////////////// V1 ////////////////////////////////////////
				/*Matrix<double,16,16> A;
				Matrix<double, 16, 1> B;
				int mrow = 0;
				for (int r = tmpx - 2; r <= tmpx + 2; r += 2)
				{
					for (int c = tmpy - 2; c <= tmpy + 2; c += 2)
					{
						if ((r == tmpx) && (c == tmpy))
							continue;
						
						for (int i = 0; i <= 3; i++)
						{
							for (int j = 0; j <= 3; j++)
							{
								A(mrow,i*4+j) = pow(r, i)*pow(c,j);
							}
						}
						B[mrow] = pInput[r*input_cols + c];
						mrow++;
						
					}
				}
				for (int r = tmpx - 1; r <= tmpx + 1; r ++)
				{
					for (int c = tmpy - 1; c <= tmpy + 1; c ++)
					{
						if((r==tmpx) && (c==tmpy))
							continue;
						
						for (int i = 0; i <= 3; i++)
						{
							for (int j = 0; j <= 3; j++)
							{
								A(mrow,i * 4 + j ) = pow(r, i)*pow(c, j);
							}
						}
						B[mrow] = pInput[r*input_cols + c];
						mrow++;
					}
				}
				Matrix<double, 16, 1> X = A.colPivHouseholderQr().solve(B);
				double v = 0;
				for (int i = 0; i <= 3; i++)
				{
					for (int j = 0; j <= 3; j++)
					{
						v += (pow(tmpx, i)*pow(tmpy, j)*X[i * 4 + j]);
					}
				}
				pOut[x*new_col + y] = v;*/

				////////////////////////////////////  V2  //////////////////////////////////////
				Matrix<double,16,16> A;
				Matrix<double, 16, 1> B;
				int mrow = 0;
				for (int r = tmpx - 1; r <= tmpx + 2; r ++)
				{
					for (int c = tmpy - 1; c <= tmpy + 2; c ++)
					{
						for (int i = 0; i <= 3; i++)
						{
							for (int j = 0; j <= 3; j++)
							{
								A(mrow,i*4+j) = pow(r, i)*pow(c,j);
							}
						}
						B[mrow] = pInput[r*input_cols + c];
						mrow++;
						
					}
				}
				Matrix<double, 16, 1> X = A.colPivHouseholderQr().solve(B);
				double v = 0;
				for (int i = 0; i <= 3; i++)
				{
					for (int j = 0; j <= 3; j++)
					{
						v += (pow(tmpx, i)*pow(tmpy, j)*X[i * 4 + j]);	
					}
				}
				pOut[x*new_col + y] = v;
			}

		}
	}

	return out;
}
