#include <DxLib.h>
#include "Object.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/ImageMng.h"
#include "../../_debug/_DebugConOut.h"

Object::Object(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, TeamTag tag) :
    pos_(pos), size_(size), objectID_(oID),teamTag_(tag)
{
    exRate_ = 1.0;
    angle_ = 0.0;
    delta_ = 0.0;
    reverseXFlag_ = false;
    isAlive_ = true;
    isDead_ = false;
    animCnt_ = 0;
    animFlam_ = 1;
    animMax_ = 1;
    invincibleCnt_ = 0.0;
    ownScreen_ = MakeScreen(64, 64, true);
    effectScreen_ = MakeScreen(64, 64, true);
}

void Object::Draw(const double& delta)
{
    if (invincibleCnt_ > 0.0)
    {
        if (static_cast<int>(std::floor(invincibleCnt_ * 10.0)) % 2 == 0)
        {
            DrawRotaGraph(pos_.x, pos_.y, exRate_, angle_, lpImageMng.GetID(imageKey_)[(animCnt_ / animFlam_) % animMax_], true, reverseXFlag_);
        }
    }
    else
    {
        DrawRotaGraph(pos_.x, pos_.y, exRate_, angle_, lpImageMng.GetID(imageKey_)[(animCnt_ / animFlam_) % animMax_], true, reverseXFlag_);
    }
    invincibleCnt_ -= delta;
    animCnt_++;
}

void Object::AddDamage(int damage)
{
}

void Object::HitCollision(std::shared_ptr<Object> otehr)
{
}

bool Object::CheckIsDead(void)
{
    return isDead_;
}

Vector2 Object::GetSize(void)
{
    return size_;
}

void Object::SetReverse(bool flag)
{
    reverseXFlag_ = flag;
}

TeamTag Object::GetTeamTag(void)
{
    return teamTag_;
}

bool Object::Alive(void)
{
    return isAlive_;
}

const Object_ID& Object::ObjectID(void) const
{
    return objectID_;
}



