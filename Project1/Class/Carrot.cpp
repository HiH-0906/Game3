#include <utility>
#include <cmath>
#include <DxLib.h>
#include "Carrot.h"
#include "Circle.h"
#include "Triangle.h"
#include "collision/CircleCollision.h"
#include "collision/TriangleCollision.h"

Carrot::Carrot(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed):
	Shape(pos, size, col, vec, speed)
{
	tag_ = ShapeTag::Carrot;
	rad_ = size.x / 2.0f;
	circleoffSet_ = { size.x / 2.0f,size.y / 3.0f };

	leafVertex_[0] = { size.x / 4.0f,0.0f };
	leafVertex_[1] = { size.x - size.x / 4.0f,0.0f };
	leafVertex_[2] = { size.x / 2.0f,size.y / 3.0f };

	fruitVertex_[0] = { 0.0f,size.y / 3.0f };
	fruitVertex_[1] = { size.x,size.y / 3.0f };
	fruitVertex_[2] = {size.x/2.0f,size.y};

	colls_.emplace_back(std::make_shared<TriangleCollision>(fruitVertex_));
	colls_.emplace_back(std::make_shared<TriangleCollision>(leafVertex_));
}


void Carrot::Draw(void)
{
	auto ConvertVector2 = [](std::array<Vector2Flt, 3>& poss)->std::array<Vector2, 3> {
		std::array<Vector2, 3> reposs;
		reposs[0] = static_cast<Vector2>(poss[0]);
		reposs[1] = static_cast<Vector2>(poss[1]);
		reposs[2] = static_cast<Vector2>(poss[2]);
		return reposs;
	};
	std::array<Vector2, 3> leafvertex = ConvertVector2(leafVertex_);

	Vector2 pos = static_cast<Vector2>(pos_);
	DrawTriangle(pos.x + leafvertex[0].x, pos.y + leafvertex[0].y, pos.x + leafvertex[1].x, pos.y + leafvertex[1].y, pos.x + leafvertex[2].x, pos.y + leafvertex[2].y, 0x73b839, true);


	Vector2 cpos = static_cast<Vector2>(pos_ + circleoffSet_);
	DrawCircle(cpos.x, cpos.y, static_cast<int>(rad_), 0xec6800, true);

	std::array<Vector2, 3> fruitVertex = ConvertVector2(fruitVertex_);

	DrawTriangle(pos.x + fruitVertex[0].x, pos.y + fruitVertex[0].y, pos.x + fruitVertex[1].x, pos.y + fruitVertex[1].y, pos.x + fruitVertex[2].x, pos.y + fruitVertex[2].y, 0xec6800, true);

}

void Carrot::Draw(const float& rate)
{
}

void Carrot::Draw(const float& rate, Vector2Flt offSet)
{
}

void Carrot::HitAction(std::shared_ptr<Shape> shape)
{
	shape->SetSpeed(150.0f);
}
