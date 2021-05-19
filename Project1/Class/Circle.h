#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(const Vector2Flt& pos, const Vector2Flt& size, const unsigned int col, const Vector2Flt vec, const float& speed);

    void Update(const float& delta, const Vector2& scrSize, const std::vector<std::shared_ptr<Shape>>& list,std::vector<InstanceData>& instanceData)override final;

    void Draw()override final;
    void Draw(const float& rate)override final;
    void Draw(const float& rate, const Vector2Flt offSet)override final;

    void GetDrawSpace(Vector2& pos, Vector2& size)override final;

    bool CheckHitWall(const Vector2& scrSize, bool& UpDown)override final;

private:
};

