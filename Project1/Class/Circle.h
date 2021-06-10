#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(const Vector2Flt& pos, const float& radius, const unsigned int col, const Vector2Flt vec, const float& speed);

    void Draw()override final;
    void Draw(const float& rate)override final;
    void Draw(const float& rate, const Vector2Flt offSet)override final;

    const float& GetRadius(void)const;

    void HitAction(std::shared_ptr<Shape> shape)override;

private:
};

