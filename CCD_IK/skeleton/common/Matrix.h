#pragma once
#include "Vector2.h"

struct Matrix2D
{
	float mat[3][3];
};

Matrix2D IdentityMatrix2D(void);

Matrix2D TranslateMatrix2D(const float& x, const float& y);

Matrix2D RotateMatrix2D(const float radian);

Matrix2D MultipleMatrix2D(const Matrix2D& lMatrix, const Matrix2D& rMatrix);

Vector2Flt MultipleVector2(const Matrix2D& matrix, const Vector2Flt& vec);