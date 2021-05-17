#include <utility>
#include <cmath>
#include <DxLib.h>
#include "Square.h"

Square::Square(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	Shape(pos, size, col, vec, speed)
{
	tag_ = ShapeTag::Circle;
	// ぴったりサイズだと端がきれいに映らないので余裕を持たせて+10
	scrSize_ = Vector2{ static_cast<int>(std::ceil(size_.x)) + 10, static_cast<int>(std::ceil(size_.y)) + 10 };
	screen_ = MakeScreen(scrSize_.x, scrSize_.y ,true);
}

void Square::Update(const float& delta, const Vector2& scrSize, std::vector<std::shared_ptr<Shape>>list,std::vector<InstanceData>& instanceData)
{
	Shape::Update(delta, scrSize,list,instanceData);
}


void Square::Draw(void)
{
	PreparaScreen();
	Vector2 tmpSize = static_cast<Vector2>(size_);

	DrawBox(0, 0, tmpSize.x, tmpSize.y, col_, true);
	
	SetDrawScreen(DX_SCREEN_BACK);
	ScrDraw(Vector2{ 0,0 });
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

bool Square::CheckHitWall(const Vector2& scrSize, bool& UpDown)
{
	if (pos_.x < 0 )
	{
		pos_.x = 0;
		UpDown = false;
	}
	else if (pos_.x + size_.x > scrSize.x)
	{
		pos_.x = scrSize.x - size_.x;
		UpDown = false;
	}
	else if (pos_.y < 0)
	{
		pos_.y = 0;
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
