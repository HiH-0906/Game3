#pragma once
#include "../common/Vector2.h"

class Shape
{
public:
	Shape(const float& posX, const float& posY, const float& sizeX, const float& sizeY, const unsigned int& col);
	Shape(const Vector2Flt& pos,const Vector2Flt& size, const unsigned int& col);

	virtual void Draw(void) = 0;
	virtual void Draw(const float& rate) = 0;
	virtual void Draw(const float& rate, Vector2Flt offSet) = 0;

	Vector2Flt pos_;
	Vector2Flt size_;
	int col_;

private:
};

