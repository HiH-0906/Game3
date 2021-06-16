#pragma once
#include <array>
#include "Shape.h"
class Star :
    public Shape
{
public:
    Star(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int& col, const Vector2Flt& vec, const float& speed);

    void Draw(void)override final;
    void Draw(const float& rate)override final;
    void Draw(const float& rate, Vector2Flt offSet)override final;

    void HitAction(std::shared_ptr<Shape> shape)override;
private:
    std::array<std::array<Vector2Flt, 3>, 5> vertexs_;
};

