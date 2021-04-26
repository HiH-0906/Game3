#include <DxLib.h>
#include "Square.h"

Square::Square(const int& posX, const int& posY, const int& sizeX, const int sizeY):Shape(posX,posY,sizeX,sizeY)
{
}

Square::Square(const Vector2& pos, const Vector2& size) : Shape(pos, size)
{
}

void Square::Draw(void)
{
	DrawBox(pos_.x - (size_.x / 2), pos_.y - (size_.y / 2), pos_.x + (size_.x / 2), pos_.y + (size_.y / 2), 0xff0000, true);
}

void Square::Draw(const float& rate)
{
	auto tmpSize = Vector2{ size_.x * static_cast<int>(rate),size_.y * static_cast<int>(rate) };
	DrawBox(pos_.x - (tmpSize.x / 2), pos_.y - (tmpSize.y / 2), pos_.x + (tmpSize.x / 2), pos_.y + (tmpSize.y / 2), 0xff0000, true);
}

void Square::Draw(const float& rate, const Vector2& offSet)
{

}
