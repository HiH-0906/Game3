#pragma once
#include "../common/Vector2.h"

class Shape
{
public:
	Shape(const int& posX,const int& posY,const int& sizeX,const int sizeY);
	Shape(const Vector2& pos,const Vector2& size);

	virtual void Draw(void);
	virtual void Draw(const float& rate);
	virtual void Draw(const float& rate, const Vector2& offSet);

	Vector2 pos_;
	Vector2 size_;

private:
};

