#include <cmath>
#include <utility>
#include <DxLib.h>
#include "Shape.h"

Shape::Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	pos_(pos), size_(size), col_(col), vec_(vec), speed_(speed)
{
	tag_ = ShapeTag::NON;
	screen_ = -1;
	scrSize_ = {};
	hitOffSet_ = {};

	isDead_ = false;
}

void Shape::Update(const float& delta, const Vector2& scrSize, std::vector<std::shared_ptr<Shape>>list, std::vector<InstanceData>& instanceData)
{
	bool upDown = false;
	if (!CheckHitWall(scrSize, upDown))
	{
		RefVec(upDown);
	}
	pos_ += vec_ * delta * speed_;

	bool hit = false;
	for (const auto& hitShape : list)
	{
		if (this == &(*hitShape))
		{
			continue;
		}
		hit |= CheckHit(hitShape);
	}
	if (hit)
	{
		col_ = 0xffffff;
	}
	else
	{
		col_ = 0xff0000;
	}
}

void Shape::ScrDraw(const Vector2 offSet)
{
	DrawGraph(static_cast<int>(pos_.x) + offSet.x, static_cast<int>(pos_.y) + offSet.y, screen_, true);
}

void Shape::Draw(const float& rate, Vector2Flt offSet)
{
}


void Shape::GetDrawSpace(Vector2& pos, Vector2& size)
{
	pos = static_cast<Vector2>(pos_) + hitOffSet_;
	size = static_cast<Vector2>(scrSize_);
}

const int& Shape::GetDrawScreen(void)
{
	return screen_;
}

bool Shape::CheckHit(const std::weak_ptr<Shape> shape)
{
	if (CheckHitDrawSpace(shape))
	{
		if (CheckHitCol(shape))
		{
			return true;
		}
	}
	return false;
}

bool Shape::CheckHitDrawSpace(const std::weak_ptr<Shape> shape)
{
	Vector2 pos = {};
	Vector2 size = {};
	Vector2 hitPos = static_cast<Vector2>(pos_) + hitOffSet_;
	shape.lock()->GetDrawSpace(pos, size);
	return ((hitPos.x + scrSize_.x > pos.x) && (hitPos.x < pos.x + size.x) && (hitPos.y + scrSize_.y > pos.y) && (hitPos.y < pos.y + size.y));
}

bool Shape::CheckHitCol(const std::weak_ptr<Shape> shape)
{
	Vector2 pos = {};
	Vector2 size = {};
	Vector2 hitPos = static_cast<Vector2>(pos_) + hitOffSet_;
	shape.lock()->GetDrawSpace(pos, size);
	return true;
	int startX = 0;
	if (pos_.x <= pos.x)
	{
		startX = 0;
	}
	else
	{
		startX = 0;
	}
}

void Shape::SetIsDead(void)
{
	isDead_ = !isDead_;
}

bool Shape::GetIsDead(void)
{
	return isDead_;
}

void Shape::SetCol(const unsigned int& col)
{
	col_ = col;
}

void Shape::RefVec(bool UpDown)
{
	if (UpDown)
	{
		vec_.y *= -1;
	}
	else
	{
		vec_.x *= -1;
	}
}

void Shape::PreparaScreen(void)
{
	unsigned int reScr = GetDrawScreen();
	SetDrawScreen(screen_);
	ClsDrawScreen();
}
