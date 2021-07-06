#include <DxLib.h>
#include "Pawn.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/ImageMng.h"
#include "../common/Raycast.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"
#include "state/state.h"

namespace
{
    int cnt = 0;
}

Pawn::Pawn(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
	Object(pos, size, speed, cID, inputType)
{
    animID_=Char_Anim_ID::IDLE;
    animCnt_ = 0;
    animLoopCnt_ = 0;
    moduleNode_ = std::make_unique<state::ModuleNode>();
    lpImageMng.GetID("Bullet", "Image/player/ChickenBullet.png", Vector2{ 32,32 }, Vector2{1,3});
}

void Pawn::Draw(const double& delta)
{
   
    auto offset = lpAnimMng.GetDrawOffSet(charID_, animID_);
    if (reverseXFlag_)
    {
        offset = -offset;
    }
    DrawRotaGraph(static_cast<int>(pos_.x + offset.x), static_cast<int>(pos_.y + offset.y), exRate_, angle_, lpAnimMng.GetAnimImag(charID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
    Vector2 tmp = static_cast<Vector2>(pos_) + Vector2(64, 0);
    int size = 32;
    DrawGraph(tmp.x, tmp.y, lpImageMng.GetID("Bullet")[(cnt/7)%3], true);
    cnt++;
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
