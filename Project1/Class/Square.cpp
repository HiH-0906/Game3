#include <DxLib.h>
#include "Square.h"

Square::Square(const int& posX, const int& posY, const int& sizeX, const int& sizeY,const unsigned int& col):Shape(posX,posY,sizeX,sizeY,col)
{
}

Square::Square(const Vector2& pos, const Vector2& size) : Shape(pos, size)
{
}

void Square::Draw(void)
{
	DrawBox(pos_.x, pos_.y, pos_.x + (size_.x), pos_.y + (size_.y), col_, true);
}

void Square::Draw(const float& rate)
{
	auto tmpSize = Vector2{ size_.x * static_cast<int>(rate),size_.y * static_cast<int>(rate) };
	DrawBox(pos_.x, pos_.y, pos_.x + (tmpSize.x), pos_.y + (tmpSize.y), col_, true);
}

void Square::Draw(const float& rate, Vector2 offSet)
{
	Vector2 pos = pos_ + offSet;
	Vector2Flt tmp = static_cast<Vector2Flt>(offSet) / static_cast<Vector2Flt>(size_);
	pos -= static_cast<Vector2>(rate * static_cast<Vector2Flt>(size_) * tmp);
	DrawBox(pos.x, pos.y, pos.x + size_.x * static_cast<int>(rate), pos.y + size_.y * static_cast<int>(rate), col_, true);
}
