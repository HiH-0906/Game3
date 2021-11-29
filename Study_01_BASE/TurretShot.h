#pragma once
#include "ShotBase.h"
class TurretShot :
    public ShotBase
{
public:
    static constexpr float COLLISION_RADIUS = 5.0f;
    TurretShot(SceneManager* manager, Transform* transform);

private:
};

