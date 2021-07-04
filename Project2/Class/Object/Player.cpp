#include <algorithm>
#include <DxLib.h>
#include "Player.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/SceneMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"
#include "../Map/MapData.h"
#include "../common/Raycast.h"
#include "../../_debug/_DebugDispOut.h"

namespace {
    int junpCnt = 0;
}

Player::Player(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
    Pawn(pos,size, speed, cID, inputType)
{ 
    Init(speed, inputType);
}

Player::~Player()
{
}

bool Player::Init(const double& speed, unsigned int inputType)
{    
    if (inputType == 0)
    {
        controller_ = std::make_unique<KeyBoard>();
    }
    else if (inputType == 1)
    {
        controller_ = std::make_unique<Pad>();
    }
    else
    {
        // @@enumclassにしたほうがわかりやすいのでは疑惑現状２つしかないので放置
        assert(!"存在しないInputType");
    }

    size_ = lpAnimMng.GetDivImageSize(charID_, animID_);

    raycast_ = std::make_unique<Raycast>();
    defJunpPower_ = -8;
    yaddPower_ = 0;
    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    auto CheckMove = [&](Vector2Flt moveVec, Vector2Flt offset)
    {
        Vector2Flt tmpPos = pos_ - offset;

        for (int i = 0; i < 9; i++)
        {
            Raycast::Ray ray = { tmpPos ,moveVec };
            _dbgDrawLine(ray.point.x, ray.point.y, ray.point.x + ray.vec.x, ray.point.y + ray.vec.y, 0x00ff00);
            _dbgDrawBox(pos_.x - size_.x / 2, pos_.y - size_.y / 2, pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0xff0000, false);
            for (auto colData : mapData.lock()->GetColData())
            {
                _dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xff0000, false);
                if (raycast_->CheckCollision(ray, colData))
                {
                    _dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xffffff, true);
                    return false;
                }
            }
            tmpPos += offset / 4.0f;
        }

        return true;
    };
    auto MoveFunc = [&](INPUT_ID id, const Vector2Flt& speed, const Vector2Flt& offset) {
        if (!controller_->GetNow(id))
        {
            return false;
        }
        Vector2Flt rayoffset = {};
        // @@ただの反転できるかのテストコード
        if (id == INPUT_ID::RIGHT)
        {
            reverseXFlag_ = false;
            rayoffset.y = size_.y / 2.0f;
        }
        else if (id == INPUT_ID::LEFT)
        {
            reverseXFlag_ = true;
            rayoffset.y = size_.y / 2.0f;
        }
        else if (id == INPUT_ID::UP)
        {
            rayoffset.x = size_.x / 2.0f;
        }
        else if (id == INPUT_ID::DOWN)
        {
            rayoffset.x = size_.x / 2.0f;
        }
        else
        {
            // 何もしない
        }
        if (CheckMove(speed + offset, rayoffset))
        {
            pos_ += speed;
        }
        return true;
    };
    controller_->Update();
    bool tmp = false;
    tmp |= MoveFunc(INPUT_ID::LEFT, Vector2Flt{ -static_cast<float>(speed_ * delta),0.0f }, -(Vector2Flt{ size_.x / 2.0f ,0.0f }));
    tmp |= MoveFunc(INPUT_ID::RIGHT, Vector2Flt{ static_cast<float>(speed_ * delta),0.0f }, (Vector2Flt{ size_.x / 2.0f ,0.0f }));
    //tmp |= MoveFunc(INPUT_ID::UP, Vector2Flt{ 0.0f,-static_cast<float>(speed_ * delta) }, -(Vector2Flt{ 0.0f,size_.y / 2.0f }));
    //tmp |= MoveFunc(INPUT_ID::DOWN, Vector2Flt{ 0.0f,static_cast<float>(speed_ * delta) }, (Vector2Flt{ 0.0f,size_.y / 2.0f }));
    // @@走らせるアニメーション確認のためのテストコード
    if (tmp)
    {
        SetAnimation(Char_Anim_ID::RUN);
    }
    else
    {
        SetAnimation(Char_Anim_ID::IDLE);
    }

    if (controller_->GetNow(INPUT_ID::BTN_1))
    {
        yaddPower_ = defJunpPower_;
    }
    Vector2Flt moveVec = {};
    Vector2Flt offset = {};
    if (yaddPower_ < 0)
    {
        moveVec = { 0.0f,yaddPower_ - size_.y / 2.0f };
        offset = { size_.x / 2.0f,0.0f };
    }
    else
    {
        moveVec = { 0.0f,yaddPower_ + size_.y / 2.0f };
        offset = { size_.x / 2.0f,0.0f };
    }
    if (CheckMove(moveVec, offset))
    {
        pos_.y += yaddPower_;
        yaddPower_ += 0.2f;
    }
    else
    {
        yaddPower_ = 0.2f;
    }

    // 画面端処理
    pos_.x = std::min(std::max(pos_.x, size_.x / 2.0f), lpSceneMng.GetScreenSize().x - (size_.x / 2.0f));
    pos_.y = std::min(std::max(pos_.y, size_.y / 2.0f - 10.0f), lpSceneMng.GetScreenSize().y - (size_.y / 2.0f));
}