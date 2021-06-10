#include <cmath>
#include <utility>
#include <ostream>
#include <cassert>
#include <DxLib.h>
#include "Shape.h"
#include "collision/Collision.h"

Shape::Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	pos_(pos), size_(size), col_(col), vec_(vec), speed_(speed), defCol_(col), defvec_(vec)
{
	interval_ = 0;
	tag_ = ShapeTag::NON;

	isDead_ = false;
}

void Shape::SetCollisionOwner(std::shared_ptr<Shape> owner)
{
	for (const auto& col : colls_)
	{
		col->SetOwner(owner);
	}
}

void Shape::HitUpdate(const float& delta,const std::vector<std::shared_ptr<Shape>>& list)
{
	for (const auto& hitShape : list)
	{
		if (this == &(*hitShape))
		{
			continue;
		}
		if (CheckHit(hitShape))
		{
			HitAction(hitShape);
		}
	}
}

void Shape::Update(const float& delta, const Vector2& scrSize)
{
	pos_ += vec_ * delta * speed_;
	bool upDown = false;
	if (!CheckHitWall(scrSize, upDown))
	{
		RefVec(upDown);
	}
}

void Shape::Update(const int& x, const int& y)
{
	pos_ = { static_cast<float>(x),static_cast<float>(y) };
}

void Shape::Draw(const float& rate, Vector2Flt offSet)
{
}

bool Shape::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	bool reFlag = true;
	for (const auto& col : colls_)
	{
		if (!col->CheckHitWall(scrSize, UpDown))
		{
			reFlag=false;
			break;
		}
	}
	return reFlag;
}


bool Shape::CheckHit(const std::weak_ptr<Shape>& shape)
{
	bool isHit = false;
	for (const auto& col : colls_)
	{
		for (const auto& hcol : shape.lock()->colls_)
		{
			isHit |= col->isHit(hcol);
		}
	}
	return isHit;
}


void Shape::SetIsDead(void)
{
	isDead_ = !isDead_;
}

bool Shape::GetIsDead(void)
{
	return isDead_;
}

const Vector2Flt Shape::GetVec(void)
{
	return vec_;
}

void Shape::SetCol(const unsigned int& col)
{
	col_ = col;
}

void Shape::SetVec(const Vector2Flt& vec)
{
	vec_ = vec;
}

void Shape::SetSpeed(const float& speed)
{
	speed_ = speed;
}

const float& Shape::GetIntervel(void) const
{
	return interval_;
}

void Shape::SetInterval(const float& inter)
{
	interval_ = inter;
}

const unsigned int& Shape::GetCol(void) const
{
	return col_;
}

Vector2Flt& Shape::GetPos(void)
{
	return pos_;
}

const Vector2Flt& Shape::GetSize(void)
{
	return size_;
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

void Shape::ReSetVec(void)
{
	vec_ = defvec_;
}

const ShapeTag& Shape::GetTag() const
{
	return tag_;
}
