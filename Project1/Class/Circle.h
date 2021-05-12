#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(const Vector2Flt&& pos, const Vector2Flt&& size, const unsigned int col, const float& rate = 1.0f, const Vector2Flt& offSet = {});

    void Update(const float& delta)override final;

    void Draw()override final;
    void Draw(const float& rate)override final;
    void Draw(const float& rate, const Vector2Flt offSet)override final;

private:
};

