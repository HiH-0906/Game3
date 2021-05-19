#include <cmath>
#include <DxLib.h>
#include "Circle.h"

Circle::Circle(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int col, const Vector2Flt vec, const float& speed) :
	Shape(pos, size, col, vec, speed)
{
	tag_ = ShapeTag::Circle;
	// ぴったりサイズだと端がきれいに映らないので余裕を持たせて+10
	scrSize_ = Vector2{ static_cast<int>(std::ceil(size_.x)) * 2 + 10, static_cast<int>(std::ceil(size_.y)) * 2 + 10 };
	screen_ = MakeScreen(scrSize_.x, scrSize_.y, true);
	hitOffSet_ = Vector2{ -scrSize_.x / 2,-scrSize_.y / 2 };
}

void Circle::Update(const float& delta, const Vector2& scrSize, const std::vector<std::shared_ptr<Shape>>& list, std::vector<InstanceData>& instanceData)
{
	Shape::Update(delta,scrSize,list,instanceData);
}

void Circle::Draw()
{
	PreparaScreen();
	Vector2 size = static_cast<Vector2>(size_);
	DrawOval(scrSize_.x / 2, scrSize_.y / 2, size.x, size.y, col_,true);
	SetDrawScreen(DX_SCREEN_BACK);
	ScrDraw(hitOffSet_);
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

void Circle::GetDrawSpace(Vector2& pos, Vector2& size)
{
	pos = static_cast<Vector2>(pos_) + hitOffSet_;
	size = static_cast<Vector2>(size_ * 2.0f);
}


bool Circle::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	if (pos_.x - size_.x < 0)
	{
		pos_.x = size_.x;
		UpDown = false;
	}
	else if (pos_.x + size_.x > scrSize.x)
	{
		pos_.x = scrSize.x - size_.x;
		UpDown = false;
	}
	else if (pos_.y - size_.y < 0)
	{
		pos_.y = size_.y;
		UpDown = true;
	}
	else if (pos_.y + size_.y > scrSize.y)
	{
		pos_.y = scrSize.y - size_.y;
		UpDown = true;
	}
	else
	{
		return true;
	}
	return false;
}
