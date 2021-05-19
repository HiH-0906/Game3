#include <cmath>
#include <utility>
#include <ostream>
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

	bool isLeft = false;
	bool isUP = false;

	if (pos_.x + hitOffSet_.x < pos.x)
	{
		isLeft = true;
	}
	else
	{
		isLeft = false;
	}
	if (pos_.y + hitOffSet_.y < pos.y)
	{
		isUP = true;
	}
	else
	{
		isUP = false;
	}
	return CheckHitScreen(shape,isLeft,isUP);
}

bool Shape::CheckHitScreen(const std::weak_ptr<Shape>& shape, bool isLeft, bool isUP)
{
	auto checkScreen = [](const int& screen, const int& sX, const int& sY, const int& eX, const int& eY, const unsigned int& col)
	{
		if ((eX < 0) || (eY < 0))
		{
			return false;
		}
		int checkCol = col + 0xff000000;
		SetDrawScreen(screen);
		for (int x = sX; x < eX; x++)
		{
			for (int y = sY; y < eY; y++)
			{
				auto aaa = GetPixel(x, y);
				if (checkCol == GetPixel(x, y))
				{
					SetDrawScreen(DX_SCREEN_BACK);
					return true;
				}
			}
		}
		SetDrawScreen(DX_SCREEN_BACK);
		return false;
	};
	bool hit = false;
	bool opHit = false;

	// é©ï™intå^èÓïÒ
	Vector2 pos = static_cast<Vector2>(pos_) + hitOffSet_;
	Vector2 size = static_cast<Vector2>(scrSize_);
	// ëäéËèÓïÒ
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
		
		if (isUP)
		{
			OutputDebugString("ç∂ è„\n");
			offsetY = pos.y + size.y - opPos.y;
			hit = checkScreen(screen_, size.x - offsetX, size.y - offsetY, size.x, size.y, col_);
			opHit = checkScreen(opScr, 0, 0, offsetX, offsetY, opCol);
			if (hit && opHit)
			{
				auto aaa = 0;
			}
		}
		else
		{
			OutputDebugString("ç∂ â∫\n");
			offsetY = opPos.y + opSize.y - pos.y;
			hit = checkScreen(screen_, size.x - offsetX, 0, size.x, offsetY, col_);
			opHit = checkScreen(opScr, 0, opSize.y - offsetY, offsetX, size.y, opCol);
		}
	}
	else
	{
		offsetX = opPos.x + opSize.x - pos.x;
		if (isUP)
		{
			OutputDebugString("âE è„\n");
			offsetY = pos.y + size.y - opPos.y;
			hit = checkScreen(screen_, 0, 0, offsetX, offsetY, col_);
			opHit = checkScreen(opScr, opSize.x + opPos.x - offsetX, opSize.y - offsetY, opSize.x, opSize.y, opCol);
			
		}
		else
		{
			OutputDebugString("âE â∫\n");
			offsetY = opPos.y + opSize.y - pos.y;
			hit = checkScreen(screen_, 0, size.y - offsetY, offsetX, size.y, col_);
			opHit = checkScreen(opScr, opSize.x - offsetX, 0, opSize.x, offsetY, opCol);
			if (hit && opHit)
			{
				auto aaa = 0;
			}
		}
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
