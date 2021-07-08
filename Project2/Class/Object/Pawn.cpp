#include <DxLib.h>
#include "Pawn.h"
#include "Bullet.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/ImageMng.h"
#include "../common/Raycast.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"
#include "state/state.h"


Pawn::Pawn(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, unsigned int inputType) :
	Object(pos, size, oID)
{
    animID_=Char_Anim_ID::IDLE;
    animCnt_ = 0;
    animLoopCnt_ = 0;
    nowBufCnt_ = 0;
    moduleNode_ = std::make_unique<state::ModuleNode>();
}

void Pawn::Draw(const double& delta)
{
    DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), exRate_, angle_, lpAnimMng.GetAnimImag(objectID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
    if (bullet_)
    {
        bullet_->Draw(delta);
    }
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

void Pawn::UpdateInputBuf(void)
{
    for (auto id:INPUT_ID())
    {
        inputBuf_[nowBufCnt_ % BUF_NUM_MAX][id] = controller_->GetNow(id);
    }
    nowBufCnt_++;
}
