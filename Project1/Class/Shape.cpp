#include <utility>
#include <DxLib.h>
#include "Shape.h"

Shape::Shape(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const float& rate, const Vector2Flt& offSet) :
	pos_(pos), size_(size), col_(col), offSet_(offSet), rate_(rate)
{
}

void Shape::Update(const float& delta)
{
}

void Shape::Draw(const float& rate, Vector2Flt offSet)
{
}
