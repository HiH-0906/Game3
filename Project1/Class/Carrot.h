#pragma once
#include <array>
#include "Shape.h"
class Carrot :
    public Shape
{
public:
	Carrot(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed);

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;
	void HitAction(std::shared_ptr<Shape> shape)override;
private:
	Vector2 CirclePos_;
	Vector2 CircleSize_;
	std::array<Vector2Flt, 3> leafVertex_;
	std::array<Vector2Flt, 3> fruitVertex_;
	float rad_;
	Vector2Flt circleoffSet_;
};

