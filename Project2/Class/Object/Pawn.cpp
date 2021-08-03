#include <DxLib.h>
#include <cmath>
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
#include "../UI/PlayerUI.h"


Pawn::Pawn(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, int hp, TeamTag tag, std::shared_ptr<PlayerUI> ui, unsigned int reviveCnt, InputType inputType) :
	Object(pos, size, oID,tag),hp_(hp)
{
    animID_=Char_Anim_ID::IDLE;
    animCnt_ = 0;
    animLoopCnt_ = 0;
    moduleNode_ = std::make_unique<state::ModuleNode>();
    LoadCommad loadCommand;

    ui_ = ui;
    isRevive_ = false;
    reviveCnt_ = reviveCnt;

    commandList_ = loadCommand("commandData/PlayerComand.xml");
    for (const auto& data:commandList_)
    {
        TRACE((data.name_ + "\n").c_str());
        for (const auto& com:data.command_)
        {
            if (com.id == CMD_ID::LEFT)
            {
                TRACE("LEFT:");
            }
            if (com.id == CMD_ID::RIGHT)
            {
                TRACE("RIGHT:");
            }
            if (com.id == CMD_ID::UP)
            {
                TRACE("UP:");
            }
            if (com.id == CMD_ID::DOWN)
            {
                TRACE("DOWN:");
            }
            if (com.id == CMD_ID::LEFT_U)
            {
                TRACE("LEFT_U_D:");
            }
            if (com.id == CMD_ID::LEFT_D)
            {
                TRACE("LEFT_D_D:");
            }
            if (com.id == CMD_ID::RIGHT_U)
            {
                TRACE("RIGHT_U_D:");
            }
            if (com.id == CMD_ID::RIGHT_D)
            {
                TRACE("RIGHT_D_D:");
            }
            if (com.id == CMD_ID::BTN_3)
            {
                TRACE("BTN_3:");
            }
            if (com.id == CMD_ID::NEUTRAL)
            {
                TRACE("NEUTRAL:");
            }
            TRACE("%d", com.time);
            TRACE("\n");
        }
    }
}

void Pawn::Draw(const double& delta)
{
    if (isAlive_)
    {
        SetDrawScreen(ownScreen_);
        ClsDrawScreen();
        if (invincibleCnt_ > 0.0 && isAlive_)
        {
            if (static_cast<int>(std::floor(invincibleCnt_ * 10.0)) % 2 == 0)
            {
                DrawGraph(0, 0, lpAnimMng.GetAnimImag(objectID_, animID_, animCnt_, animLoopCnt_), true);
            }
        }
        else
        {
            DrawGraph(0, 0, lpAnimMng.GetAnimImag(objectID_, animID_, animCnt_, animLoopCnt_), true);
        }
        invincibleCnt_ -= delta;
        SetDrawScreen(effectScreen_);
        ClsDrawScreen();
        DrawGraph(0, 0, ownScreen_, true);
        GraphFilter(effectScreen_, DX_GRAPH_FILTER_GAUSS, 8, 100);
        int col = ui_->GetCol();
        GraphFilter(effectScreen_, DX_GRAPH_FILTER_TWO_COLOR, 0, 0x000000, 0, col, 255);
        SetDrawScreen(DX_SCREEN_BACK);
        DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 0.9 * exRate_, angle_, effectScreen_, true, reverseXFlag_);
        DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), exRate_, angle_, ownScreen_, true, reverseXFlag_);
    }
    else
    {
        DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), exRate_, angle_, lpAnimMng.GetAnimImag(objectID_, animID_, animCnt_, animLoopCnt_), true, reverseXFlag_);
    }
    for (const auto& bullet : bulletList_)
    {
        bullet->Draw(delta);
    }
    ui_->UpDate(delta);
    ui_->UIDraw(delta);
    ui_->Draw();
}

void Pawn::AddDamage(int damage)
{
    if (invincibleCnt_ < 0.0)
    {
        invincibleCnt_ = 2.0;
        hp_ -= damage;
        if (hp_ <= 0)
        {
            isAlive_ = false;
        }
    }
}

const unsigned int& Pawn::GetReviveCnt()
{
    return reviveCnt_;
}

void Pawn::SetInvincibleCnt(const double& cnt)
{
    invincibleCnt_ = cnt;
}

InputType Pawn::GetInputType(void)
{
    return controller_->GetInputType();
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
