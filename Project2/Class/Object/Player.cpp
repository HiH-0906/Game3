#include <DxLib.h>
#include "Player.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"
#include "../Map/MapData.h"
#include "../common/Raycast.h"
#include "../../_debug/_DebugDispOut.h"



Player::Player(const Vector2& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
    Object(pos,size, speed, cID, inputType)
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

    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    auto CheckMove = [&](Vector2 moveVec)
    {
        Raycast::Ray ray = { pos_ ,moveVec };
        _dbgDrawLine(ray.point.x, ray.point.y, ray.point.x + ray.vec.x, ray.point.y + ray.vec.y, 0x00ff00);
        _dbgDrawBox(pos_.x - size_.x / 2, pos_.y - size_.y / 2, pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0xff0000, false);
        for (auto colData : mapData.lock()->GetColData())
        {
            if (raycast_->CheckCollision(ray,colData))
            {
                _dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xffffff, true);
                return false;
            }
        }
        return true;
    };
    auto MoveFunc = [&](INPUT_ID id, const Vector2& speed, const Vector2& offset) {
        if (!controller_->GetNow(id))
        {
            return false;
        }
        // @@ただの反転できるかのテストコード
        if (id == INPUT_ID::RIGHT)
        {
            reverseXFlag_ = false;
        }
        else if (id == INPUT_ID::LEFT)
        {
            reverseXFlag_ = true;
        }
        else
        {
            // 何もしない
        }
        if (CheckMove(speed + offset))
        {
            pos_ += speed;
        }
        return true;
    };
    for (auto colData : mapData.lock()->GetColData())
    {
        _dbgDrawBox(colData.first.x, colData.first.y, colData.first.x + colData.second.x, colData.first.y + colData.second.y, 0xff0000, false);
    };
    controller_->Update();
    bool tmp = false;
    tmp |= MoveFunc(INPUT_ID::LEFT, Vector2{ -static_cast<int>(speed_ * delta),0 }, -(Vector2{ size_.x / 2 ,0 }));
    tmp |= MoveFunc(INPUT_ID::RIGHT, Vector2{ static_cast<int>(speed_ * delta),0 }, (Vector2{ size_.x / 2 ,0 }));
    tmp |= MoveFunc(INPUT_ID::UP, Vector2{ 0,-static_cast<int>(speed_ * delta) }, -(Vector2{ 0,size_.y / 2 }));
    tmp |= MoveFunc(INPUT_ID::DOWN, Vector2{ 0,static_cast<int>(speed_ * delta) }, (Vector2{ 0,size_.y / 2 }));
    // @@走らせるアニメーション確認のためのテストコード
    if (tmp)
    {
        SetAnimation(Anim_ID::RUN);
    }
    else
    {
        SetAnimation(Anim_ID::IDLE);
    }
}