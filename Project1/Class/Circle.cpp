#include <cmath>
#include <DxLib.h>
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "collision/CircleCollision.h"

Circle::Circle(const Vector2Flt& pos, const float& radius, const unsigned int col, const Vector2Flt vec, const float& speed) :
	Shape(pos, Vector2Flt{ radius ,radius }, col, vec, speed)
{
	tag_ = ShapeTag::Circle;
	colls_.emplace_back(std::make_shared<CircleCollision>(radius));
}


void Circle::Draw()
{
	Vector2 pos = static_cast<Vector2>(pos_);
	Vector2 size = static_cast<Vector2>(size_);
	DrawOval(pos.x, pos.y, size.x, size.y, col_, true);
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

const float& Circle::GetRadius(void) const
{
	return size_.x;
}

void Circle::HitAction(std::shared_ptr<Shape> shape)
{
	if (shape->GetTag() == ShapeTag::Squeare)
	{
		auto sq = std::dynamic_pointer_cast<Square>(shape);
		sq->SetSize((sq->GetSize() / 1000.0f) * 1001.0f);
	}
	if (shape->GetTag() == ShapeTag::Triangle)
	{
		auto tr = std::dynamic_pointer_cast<Triangle>(shape);
		tr->SetVec((tr->GetVec() / 100.0f) * 99.0f);
	}
}
