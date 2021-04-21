#pragma once
#include "../common/Vector2.h"

class Shape
{
public:
	Shape(const int& posX,const int& posY,const int& sizeX,const int sizeY);
	Shape(const Vector2& pos,const Vector2& size);

	void Draw(void);

	Vector2 pos_;
	Vector2 size_;

private:
};

