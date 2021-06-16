#include <utility>
#include <cmath>
#include <cassert>
#include <DxLib.h>
#include "Triangle.h"
#include "Circle.h"
#include "Square.h"
#include "collision/TriangleCollision.h"

Triangle::Triangle(const Vector2Flt& pos, const std::array<Vector2Flt, 3>& vertex, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed) :
	Shape(pos, size, col, vec, speed), vertex_(vertex)
{
	tag_ = ShapeTag::Triangle;

	Vector2 tmpSize = static_cast<Vector2>(size_);

	colls_.emplace_back(std::make_shared<TriangleCollision>(vertex_));
}

void Triangle::Draw(void)
{
	auto ConvertVector2 = [](std::array<Vector2Flt,3>& poss)->std::array<Vector2,3> {
		std::array<Vector2,3> reposs;
		reposs[0] = static_cast<Vector2>(poss[0]);
		reposs[1] = static_cast<Vector2>(poss[1]);
		reposs[2] = static_cast<Vector2>(poss[2]);
		return reposs;
	};
	std::array<Vector2, 3> vertex = ConvertVector2(vertex_);

	Vector2 pos = static_cast<Vector2>(pos_);

	DrawTriangle(pos.x + vertex[0].x, pos.y + vertex[0].y, pos.x + vertex[1].x, pos.y + vertex[1].y, pos.x + vertex[2].x, pos.y + vertex[2].y, col_, true);
}

void Triangle::Draw(const float& rate)
{
}

void Triangle::Draw(const float& rate, Vector2Flt offSet)
{
}

void Triangle::HitAction(std::shared_ptr<Shape> shape)
{
	if (shape->GetTag() == ShapeTag::Squeare)
	{
		auto sq = std::dynamic_pointer_cast<Square>(shape);
		sq->SetSize((sq->GetSize() / 1000.0f) * 999.0f);
	}
	if (shape->GetTag() == ShapeTag::Circle)
	{
		auto ci = std::dynamic_pointer_cast<Circle>(shape);
		ci->SetVec((ci->GetVec() / 100.0f) * 101.0f);
	}
}

const std::array<Vector2Flt, 3> Triangle::GetVertex(void)
{
	std::array<Vector2Flt, 3> vertex;

	Vector2Flt pos = static_cast<Vector2Flt>(pos_);

	vertex[0] = vertex_[0] + pos;
	vertex[1] = vertex_[1] + pos;
	vertex[2] = vertex_[2] + pos;

	return vertex;
}
