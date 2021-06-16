#pragma once
#include <array>
#include "Shape.h"


class Triangle :
    public Shape
{
public:
	Triangle(const Vector2Flt& pos,const std::array<Vector2Flt,3>& vertex, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed);

	void Draw(void)override final;
	void Draw(const float& rate)override final;
	void Draw(const float& rate, Vector2Flt offSet)override final;

	void HitAction(std::shared_ptr<Shape> shape)override;

	const std::array<Vector2Flt, 3> GetVertex(void);
private:
	std::array<Vector2Flt, 3> vertex_;
};

