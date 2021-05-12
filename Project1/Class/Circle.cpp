#include <DxLib.h>
#include "Circle.h"

Circle::Circle(const Vector2Flt&& pos, const Vector2Flt&& size, const unsigned int col, const float& rate, const Vector2Flt& offSet) :Shape(pos, size, col, rate, offSet)
{
}

void Circle::Update(const float& delta)
{
}

void Circle::Draw()
{
	Vector2Flt pos = pos_ + offSet_ - size_ * rate_ * offSet_ / size_;

	Vector2 tmpPos = static_cast<Vector2>(pos);
	Vector2 tmpSize = static_cast<Vector2>(size_ * rate_);

	DrawOval(tmpPos.x, tmpPos.y, tmpSize.x, tmpSize.y, col_, true);
	/*Vector2 pos = static_cast<Vector2>(pos_);
	Vector2 size = static_cast<Vector2>(size_);
	DrawOval(pos.x, pos.y, size.x, size.y, col_,true);*/
}

void Circle::Draw(const float& rate)
{
	Vector2 pos = static_cast<Vector2>(pos_);
	Vector2 size = static_cast<Vector2>(size_ * rate);
	DrawOval(pos.x, pos.y, size.x, size.y, col_,true);
}

void Circle::Draw(const float& rate, const Vector2Flt offSet)
{
	Vector2Flt pos = pos_ + offSet - size_ * rate * offSet / size_;

	Vector2 tmpPos = static_cast<Vector2>(pos);
	Vector2 tmpSize = static_cast<Vector2>(size_ * rate);

	DrawOval(tmpPos.x, tmpPos.y, tmpSize.x, tmpSize.y, col_, true);
}
