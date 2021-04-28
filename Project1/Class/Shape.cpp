#include <DxLib.h>
#include "Shape.h"


Shape::Shape(const float& posX, const float& posY, const float& sizeX, const float& sizeY, const unsigned int& col) :
	pos_(posX, posY), size_(sizeX, sizeY), col_(col)
{
}

Shape::Shape(const Vector2Flt& pos, const Vector2Flt& size)
{
	pos_ = pos;
	size_ = size;
}
