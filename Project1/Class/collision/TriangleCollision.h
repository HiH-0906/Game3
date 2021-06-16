#pragma once
#include <array>
#include "Collision.h"
class TriangleCollision :
    public Collision
{
public:
    TriangleCollision(const std::array<Vector2Flt, 3>& vertex, const Vector2Flt offset = {});
    ~TriangleCollision() = default;

    COLLISION_TAG CollisionTag(void)override;
    bool isHit(std::shared_ptr<Collision> col)override;

    const std::vector<Vector2Flt> GetVertex(void);

    bool CheckHitWall(const Vector2& scrSize,bool& UpDown)override final;
private:
    std::array<Vector2Flt, 3> vertex_;
    bool CheckSeparationLine(const std::vector<Vector2Flt>& myvertex, const std::vector<Vector2Flt>& svertex);
};

