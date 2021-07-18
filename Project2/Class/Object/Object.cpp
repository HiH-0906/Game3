#include <DxLib.h>
#include "Object.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/ImageMng.h"

Object::Object(const Vector2Flt& pos, const Vector2& size, const Object_ID oID) :
    pos_(pos), size_(size), objectID_(oID)
{
    exRate_ = 1.0;
    angle_ = 0.0;
    delta_ = 0.0;
    reverseXFlag_ = false;
    isAlive_ = true;
    animCnt_ = 0;
    animFlam_ = 1;
    animMax_ = 1;
}


void Object::Draw(const double& delta)
{
    DrawRotaGraph(pos_.x, pos_.y, exRate_, angle_, lpImageMng.GetID(imageKey_)[(animCnt_ / animFlam_) % animMax_], true, reverseXFlag_);
    animCnt_++;
}

bool Object::Alive(void)
{
    return isAlive_;
}

const Vector2Flt Object::GetPos(void) const
{
    return pos_;
}

