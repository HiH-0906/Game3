#include <utility>
#include <DxLib.h>
#include "Square.h"

Square::Square(const Vector2Flt&& pos, const Vector2Flt&& size, const unsigned int& col, const Vector2Flt& vec, const float& speed, const float& rate, const Vector2Flt& offSet) : Shape(pos, size, col, vec, speed, rate, offSet)
{
}

void Square::Update(const float& delta, const Vector2& scrSize)
{
	Shape::Update(delta, scrSize);
}


void Square::Draw(void)
{
	Vector2Flt pos = pos_ + offSet_ - size_ * rate_ * offSet_ / size_;

	Vector2 tmpPos = static_cast<Vector2>(pos);
	Vector2 tmpSize = static_cast<Vector2>(size_ * rate_);

	DrawBox(tmpPos.x, tmpPos.y, tmpPos.x + tmpSize.x, tmpPos.y + tmpSize.y, col_, true);
	/*Vector2 tmpPos = static_cast<Vector2>(pos_);
	Vector2 tmpSize = static_cast<Vector2>(size_);

	DrawBox(tmpPos.x, tmpPos.y, tmpPos.x + (tmpSize.x), tmpPos.y + (tmpSize.y), col_, true);*/
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

bool Square::CheckHitWall(const Vector2& scrSize)
{
	
	return !(pos_.x<0 || pos_.y<0 || pos_.x + size_.x>scrSize.x || pos_.y + size_.y>scrSize.y);
}
