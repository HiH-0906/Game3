#pragma once
#include <utility>
#include "Collision.h"
class CircleCollision :
    public Collision
{
public:
    CircleCollision(const float& rad, const Vector2Flt offset = {});
    ~CircleCollision() = default;

    COLLISION_TAG CollisionTag(void)override;
    bool isHit(std::shared_ptr<Collision> col)override;

    bool CheckHitWall(const Vector2& scrSize, bool& UpDown)override final;

    const std::pair<Vector2Flt, float> GetCircleData(void);
    void SetRadius(const float& rad);
private:
    float rad_;
};

