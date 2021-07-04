#include <DxLib.h>
#include "Object.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

Object::Object(const Vector2Flt& pos,const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
    pos_(pos),size_(size), animID_(Anim_ID::IDLE), animCnt_(0),charID_(cID), animLoopCnt_(0),speed_(speed)
{
    dir_ = DIR::LEFT;
    exRate_ = 1.0;
    angle_ = 0.0;
    reverseXFlag_ = false;
}


void Object::Draw(const double& delta)
{
    auto offset = lpAnimMng.GetDrawOffSet(charID_,animID_);
    if (reverseXFlag_)
    {
        offset = -offset;
    }
    DrawRotaGraph(pos_.x + offset.x, pos_.y + offset.y, exRate_, angle_, lpAnimMng.GetAnimImag(charID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
}

const Vector2Flt Object::GetPos(void) const
{
    return pos_;
}


void Object::SetAnimation(Anim_ID id)
{
    if (animID_ != id)
    {
        animID_ = id;
        animCnt_ = 0;
        animLoopCnt_ = 0;
    }
}

