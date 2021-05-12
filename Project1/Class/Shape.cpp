#include <utility>
#include <DxLib.h>
#include "Shape.h"

Shape::Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed, const float& rate, const Vector2Flt& offSet) :
	pos_(pos), size_(size), col_(col), vec_(vec), speed_(speed), offSet_(offSet), rate_(rate)
{
}

void Shape::Update(const float& delta, const Vector2& scrSize)
{
	if (CheckHitWall(scrSize))
	{
		pos_ += vec_ * delta * speed_;
	}
}

void Shape::Draw(const float& rate, Vector2Flt offSet)
{
}

void Shape::RefVec(void)
{
}
