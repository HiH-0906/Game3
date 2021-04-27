#pragma once
#include "../common/Vector2.h"

class Shape
{
public:
	Shape(const int& posX,const int& posY,const int& sizeX,const int& sizeY,const unsigned int& col);
	Shape(const Vector2& pos,const Vector2& size);

	virtual void Draw(void) = 0;
	virtual void Draw(const float& rate) = 0;
	virtual void Draw(const float& rate, const Vector2& offSet) = 0;

	Vector2 pos_;
	Vector2 size_;
	int col_;

private:
};

