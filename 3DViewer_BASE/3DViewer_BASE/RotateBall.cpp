#include "RotateBall.h"
#include "SceneManager.h"
#include "Unit.h"

RotateBall::RotateBall(SceneManager* manager, Unit* unit)
{
    mSceneMnager_ = manager;
    unit_ = unit;
}

void RotateBall::Init(void)
{
}

void RotateBall::Update(void)
{
    deltaTime_ += mSceneMnager_->GetDeltaTime() * 2.0f;

    VECTOR uPos = unit_->GetPos();

    float dirX = sinf(uPos.y + deltaTime_);
    float dirZ = cosf(uPos.y + deltaTime_);

    VECTOR movePos = VNorm({ dirX ,0.0f,dirZ });
    movePos = VScale(movePos, 100.0f);
    movePos.y = 50.0f;
    pos_ = VAdd(uPos, movePos);
}

void RotateBall::Draw(void)
{
    DrawSphere3D(pos_, 10.0f, 5, 0xff0000, 0xff0000, true);
}

VECTOR RotateBall::GetPos(void)
{
    return pos_;
}
