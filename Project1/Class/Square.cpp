#include <utility>
#include <cmath>
#include <DxLib.h>
#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include "collision/SquaerCollision.h"

Square::Square(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	Shape(pos, size, col, vec, speed)
{
	tmp = 0;
	tag_ = ShapeTag::Squeare;
	colls_.emplace_back(std::make_shared<SquaerCollision>(size_));
}


void Square::Draw(void)
{
	Vector2 pos = static_cast<Vector2>(pos_);
	Vector2 size = static_cast<Vector2>(size_);

	DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, col_, true);
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

void Square::HitAction(std::shared_ptr<Shape> shape)
{
	if (shape->GetTag() == ShapeTag::Triangle)
	{
		auto tr = std::dynamic_pointer_cast<Triangle>(shape);
		tr->SetVec(tr->GetVec() * 1.01f);
	}
	if (shape->GetTag() == ShapeTag::Circle)
	{
		auto ci = std::dynamic_pointer_cast<Circle>(shape);
		ci->SetVec(ci->GetVec() * 0.99f);
	}
}

const Vector2Flt& Square::GetSize(void) const
{
	return size_;
}

void Square::SetSize(const Vector2Flt& size)
{
	size_ = size;
	std::dynamic_pointer_cast<SquaerCollision>(colls_[0])->SetSize(size_);
	int x, y;
	GetDrawScreenSize(&x, &y);
	if (size_.x <= 10 || size_.y <= 10 || size_.x >= x || size_.y >= y)
	{
		isDead_ = true;
	}
}
