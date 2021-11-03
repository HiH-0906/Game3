#include "Matrix.h"

Matrix2D IdentityMatrix2D(void)
{
	Matrix2D reMat = {};
	reMat.mat[0][0] = 1;
	reMat.mat[1][1] = 1;
	reMat.mat[2][2] = 1;
	return reMat;
}

Matrix2D TranslateMatrix2D(const float& x, const float& y)
{
	Matrix2D reMat = {};
	reMat = IdentityMatrix2D();
	reMat.mat[0][2] = x;
	reMat.mat[1][2] = y;
	return reMat;
}

Matrix2D RotateMatrix2D(const float radian)
{
	Matrix2D reMat = {};
	reMat = IdentityMatrix2D();
	reMat.mat[0][0] = cos(radian);
	reMat.mat[0][1] = -sin(radian);
	reMat.mat[1][0] = sin(radian);
	reMat.mat[1][1] = cos(radian);
	return reMat;
}

Matrix2D MultipleMatrix2D(const Matrix2D& lMatrix, const Matrix2D& rMatrix)
{
	Matrix2D reMat = {};
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				reMat.mat[k][j] += lMatrix.mat[k][i] * rMatrix.mat[i][j];
			}
		}
	}
	return reMat;
}

Vector2Flt MultipleVector2(const Matrix2D& matrix, const Vector2Flt& vec)
{
	Vector2Flt reVec = {};
	reVec.x = matrix.mat[0][0] * vec.x + matrix.mat[0][1] * vec.y + matrix.mat[0][2];
	reVec.y = matrix.mat[1][0] * vec.x + matrix.mat[1][1] * vec.y + matrix.mat[1][2];
	return reVec;
}
