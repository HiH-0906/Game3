#include <DxLib.h>
#include "Pawn.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

Pawn::Pawn(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
	Object(pos, size, speed, cID, inputType)
{
    animID_=Char_Anim_ID::IDLE;
    animCnt_ = 0;
    animLoopCnt_ = 0;
}

void Pawn::Draw(const double& delta)
{
    auto offset = lpAnimMng.GetDrawOffSet(charID_, animID_);
    if (reverseXFlag_)
    {
        offset = -offset;
    }
    DrawRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y + offset.y), exRate_, angle_, lpAnimMng.GetAnimImag(charID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
}


void Pawn::SetAnimation(Char_Anim_ID id)
{
    if (animID_ != id)
    {
        animID_ = id;
        animCnt_ = 0;
        animLoopCnt_ = 0;
    }
}
