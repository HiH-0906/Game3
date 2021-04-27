#include <DxLib.h>
#include "Shape.h"


Shape::Shape(const int& posX, const int& posY, const int& sizeX, const int& sizeY,const unsigned int& col) :
	pos_(posX,posY), size_(sizeX,sizeY), col_(col)
{
}

Shape::Shape(const Vector2& pos, const Vector2& size)
{
	pos_ = pos;
	size_ = size;
}
