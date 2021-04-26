#include <DxLib.h>
#include "Shape.h"

void Shape::Draw(void)
{
	DrawBox(pos_.x - (size_.x / 2), pos_.y - (size_.y / 2), pos_.x + (size_.x / 2), pos_.y + (size_.y / 2), 0xffffff, true);
}

void Shape::Draw(const float& rate)
{
	auto tmpSize = Vector2{ size_.x * static_cast<int>(rate),size_.y * static_cast<int>(rate) };
	DrawBox(pos_.x - (tmpSize.x / 2), pos_.y - (tmpSize.y / 2), pos_.x + (tmpSize.x / 2), pos_.y + (tmpSize.y / 2), 0xffffff, true);
}

void Shape::Draw(const float& rate, const Vector2& offSet)
{
	const auto tmpPos = Vector2{ pos_.x + offSet.x,pos_.y + offSet.y };
	const auto tmpSize = Vector2{ size_.x * static_cast<int>(rate),size_.y * static_cast<int>(rate) };
	DrawBox(tmpPos.x - (tmpSize.x / 2), tmpPos.y - (tmpSize.y / 2), tmpPos.x + (tmpSize.x / 2), tmpPos.y + (tmpSize.y / 2), 0xffffff, true);
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
