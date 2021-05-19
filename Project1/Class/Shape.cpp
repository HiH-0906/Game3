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

void Shape::Update(const float& delta, const Vector2& scrSize, const std::vector<std::shared_ptr<Shape>>& list, std::vector<InstanceData>& instanceData)
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

void Shape::UpDate(const int& x, const int& y)
{
	pos_ = { static_cast<float>(x),static_cast<float>(y) };
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

bool Shape::CheckHit(const std::weak_ptr<Shape>& shape)
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

bool Shape::CheckHitDrawSpace(const std::weak_ptr<Shape>& shape)
{
	Vector2 pos = {};
	Vector2 size = {};
	Vector2 hitPos = static_cast<Vector2>(pos_) + hitOffSet_;
	shape.lock()->GetDrawSpace(pos, size);
	return ((hitPos.x + scrSize_.x > pos.x) && (hitPos.x < pos.x + size.x) && (hitPos.y + scrSize_.y > pos.y) && (hitPos.y < pos.y + size.y));
}

bool Shape::CheckHitCol(const std::weak_ptr<Shape>& shape)
{
	Vector2 pos = {};
	Vector2 size = {};
	Vector2 hitPos = static_cast<Vector2>(pos_) + hitOffSet_;
	shape.lock()->GetDrawSpace(pos, size);
	return true;

	int offSetX = 0;
	int offSetY = 0;
	bool isLeft = false;

	if (pos_.x < pos.x)
	{
		offSetX = static_cast<int>(pos_.x + size_.x) - pos.x;
		isLeft = true;
	}
	else
	{
		offSetX = pos.x + size.x - static_cast<int>(pos_.x);
		isLeft = false;
	}
	if (pos_.y < pos.y)
	{
		offSetY = static_cast<int>(pos_.y + size_.y) - pos.y;
		isLeft = true;
	}
	else
	{
		offSetY = pos.y + size.y - static_cast<int>(pos_.y);
		isLeft = false;
	}
}

bool Shape::CheckHitScreen(const std::weak_ptr<Shape>& shape, bool isLeft)
{
	auto checkScreen = [](const int& screen, const int& sX, const int& sY, const int& eX, const int& eY, const unsigned int& col)
	{
		bool reflag = false;
		SetDrawScreen(screen);
		for (int x = sX; x < eX; x++)
		{
			for (int y = sY; y < eY; y++)
			{
				if (col == GetPixel(x, y))
				{
					reflag = true;
				}
			}
		}
		SetDrawScreen(DX_SCREEN_BACK);
		return reflag;
	};
	bool hit = false;
	bool opHit = false;

	// Ž©•ªintŒ^î•ñ
	Vector2 pos = static_cast<Vector2>(pos_);
	Vector2 size = static_cast<Vector2>(size_);
	// ‘ŠŽèî•ñ
	Vector2 opPos = {};
	Vector2 opSize = {};
	const int& opScr = shape.lock()->GetDrawScreen();
	unsigned int opCol = shape.lock()->GetCol();

	shape.lock()->GetDrawSpace(opPos, opSize);

	int offsetX = 0;
	int offsetY = 0;
	if (isLeft)
	{
		offsetX = pos.x + size.x - opPos.x;
		offsetY = pos.y + size.y - opPos.y;
		hit = checkScreen(screen_, size.x - offsetX, size.y - offsetY, size.x, size.y, col_);
		opHit = checkScreen(opScr, 0, 0, offsetX, offsetY, opCol);
	}
	else
	{
		offsetX = opPos.x + opSize.x - pos.x;
		offsetY = opPos.y + opSize.y - pos.y;
		hit = checkScreen(screen_, 0, 0, offsetX, offsetY, col_);
		opHit = checkScreen(opScr, opSize.x + opPos.x - offsetX, opSize.y + opPos.y - offsetY, opSize.x, opSize.y, opCol);
	}
	return hit && opHit;
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

const unsigned int& Shape::GetCol(void) const
{
	return col_;
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
