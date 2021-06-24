#include <DxLib.h>
#include "Object.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

Object::Object(const Vector2& pos, const double& speed, const char_ID cID, unsigned int inputType) :
    pos_(pos), animID_(Anim_ID::IDLE), animCnt_(0),charID_(cID), animLoopCnt_(0)
{
    exRate_ = 1.0;
    angle_ = 0.0;
    reverseXFlag_ = false;
}



void Object::Update(const double& delta)
{
    
}

void Object::Draw(const double& delta)
{
    auto offset = lpAnimMng.GetDrawOffSet(charID_,animID_);
    DrawRotaGraph(pos_.x + offset.x, pos_.y + offset.y, exRate_, angle_, lpAnimMng.GetAnimImag(charID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
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

