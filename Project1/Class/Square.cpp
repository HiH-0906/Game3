#include <DxLib.h>
#include "Square.h"

Square::Square(const float& posX, const float& posY, const float& sizeX, const float& sizeY, const unsigned int& col) :
	Shape(posX, posY, sizeX, sizeY, col)
{
}

Square::Square(const Vector2Flt& pos, const Vector2Flt& size) : Shape(pos, size)
{
}

void Square::Draw(void)
{
	Vector2 tmpPos = static_cast<Vector2>(pos_);
	Vector2 tmpSize = static_cast<Vector2>(size_);

	DrawBox(tmpPos.x, tmpPos.y, tmpPos.x + (tmpSize.x), tmpPos.y + (tmpSize.y), col_, true);
}

void Square::Draw(const float& rate)
{
	Vector2 tmpPos = static_cast<Vector2>(pos_);
	Vector2 tmpSize = static_cast<Vector2>(size_ * rate);
	
	DrawBox(tmpPos.x, tmpPos.y, tmpPos.x + (tmpSize.x), tmpPos.y + (tmpSize.y), col_, true);
}

void Square::Draw(const float& rate, Vector2Flt offSet)
{
	Vector2Flt pos = pos_ + offSet - size_ * rate * offSet / size_;

	Vector2 tmpPos = static_cast<Vector2>(pos);
	Vector2 tmpSize = static_cast<Vector2>(size_ * rate);

	DrawBox(tmpPos.x, tmpPos.y, tmpPos.x + tmpSize.x, tmpPos.y + tmpSize.y, col_, true);
}
