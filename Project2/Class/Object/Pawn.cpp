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
#include "../../commandData/LoadCommand.h"
#include "../../_debug/_DebugConOut.h"


Pawn::Pawn(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, unsigned int inputType) :
	Object(pos, size, oID)
{
    animID_=Char_Anim_ID::IDLE;
    animCnt_ = 0;
    animLoopCnt_ = 0;
    moduleNode_ = std::make_unique<state::ModuleNode>();
    LoadCommad loadCommand;
    commandList_ = loadCommand("commandData/PlayerComand.xml");
    for (const auto& data:commandList_)
    {
        TRACE((data.name_ + "\n").c_str());
        for (const auto& com:data.command_)
        {
            if (com.first==CMD_ID::LEFT)
            {
                TRACE("LEFT:");
            }
            if (com.first == CMD_ID::RIGHT)
            {
                TRACE("RIGHT:");
            }
            if (com.first == CMD_ID::UP)
            {
                TRACE("UP:");
            }
            if (com.first == CMD_ID::DOWN)
            {
                TRACE("DOWN:");
            }
            if (com.first == CMD_ID::LEFT_U_D)
            {
                TRACE("LEFT_U_D:");
            }
            if (com.first == CMD_ID::LEFT_D_D)
            {
                TRACE("LEFT_D_D:");
            }
            if (com.first == CMD_ID::RIGHT_U_D)
            {
                TRACE("RIGHT_U_D:");
            }
            if (com.first == CMD_ID::RIGHT_D_D)
            {
                TRACE("RIGHT_D_D:");
            }
            if (com.first == CMD_ID::BTN_3)
            {
                TRACE("BTN_3:");
            }
            TRACE("%d", com.second);
            TRACE("\n");
        }
    }
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
