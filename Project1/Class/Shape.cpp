#include <DxLib.h>
#include "Shape.h"

void Shape::Draw(void)
{
	DrawBox(pos_.x - (size_.x / 2), pos_.y - (size_.y / 2), pos_.x + (size_.x / 2), pos_.y + (size_.y / 2), 0xffffff, true);
}

Shape::Shape(const int& posX, const int& posY, const int& sizeX, const int sizeY) :
	pos_(posX,posY), size_(sizeX,sizeY)
{
}

Shape::Shape(const Vector2& pos, const Vector2& size)
{
	pos_ = pos;
	size_ = size;
}
