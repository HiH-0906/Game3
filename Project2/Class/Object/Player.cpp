#include <DxLib.h>
#include "Player.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"
#include "../Map/MapData.h"



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
        // @@enumclassÇ…ÇµÇΩÇŸÇ§Ç™ÇÌÇ©ÇËÇ‚Ç∑Ç¢ÇÃÇ≈ÇÕã^òf
        assert(!"ë∂ç›ÇµÇ»Ç¢InputType");
    }

    speed_.try_emplace(INPUT_ID::LEFT, Vector2Dbl{ -speed,0.0 });
    speed_.try_emplace(INPUT_ID::RIGHT, Vector2Dbl{ speed,0.0 });
    speed_.try_emplace(INPUT_ID::UP, Vector2Dbl{ 0.0,-speed });
    speed_.try_emplace(INPUT_ID::DOWN, Vector2Dbl{ 0.0,speed });
    speed_.try_emplace(INPUT_ID::BTN_1, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::BTN_2, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::BTN_3, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::MAX, Vector2Dbl{ 0.0,0.0 });

    SetCollisionPos();

    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    auto CheckMoveDir = [&](const Vector2& pos)
    {
        for (const auto& col:collisionPos_[dir_])
        {
            auto tmp = pos + col;
            if ((mapData.lock())->CheckMapChip(tmp))
            {
                return true;
            }
        }
        return false;
    };
    controller_->Update();
    bool tmp = false;
    for (auto id : INPUT_ID())
    {
        if (controller_->GetNow(id))
        {
            if (ChengeDIR_[id] != DIR::MAX)
            {
                dir_ = ChengeDIR_[id];
            }
            tmp = true;
            auto tmpPos= pos_ + static_cast<Vector2>(speed_[id] * delta);
            if (CheckMoveDir(tmpPos))
            {
                pos_ = tmpPos;
            }
            if (id==INPUT_ID::RIGHT)
            {
                reverseXFlag_ = false;
            }
            else if (id == INPUT_ID::LEFT)
            {
                reverseXFlag_ = true;
            }
            else
            {
                // âΩÇ‡ÇµÇ»Ç¢
            }
        }
    }
    if (tmp)
    {
        SetAnimation(Anim_ID::RUN);
    }
    else
    {
        SetAnimation(Anim_ID::IDLE);
    }
}

void Player::SetCollisionPos(void)
{
    for (const auto aID : Anim_ID())
    {
        Vector2 imageSize = { lpAnimMng.GetDivImageSize(charID_, aID).x / 2 ,lpAnimMng.GetDivImageSize(charID_, aID).y / 2 };
        collisionPos_[DIR::UP].emplace_back(Vector2(-imageSize.x,-imageSize.y));
        collisionPos_[DIR::UP].emplace_back(Vector2(imageSize.x,-imageSize.y));
        collisionPos_[DIR::DOWN].emplace_back(Vector2(-imageSize.x,imageSize.y));
        collisionPos_[DIR::DOWN].emplace_back(Vector2(imageSize.x,imageSize.y));
        collisionPos_[DIR::LEFT].emplace_back(Vector2(-imageSize.x, -imageSize.y));
        collisionPos_[DIR::LEFT].emplace_back(Vector2(-imageSize.x, imageSize.y));
        collisionPos_[DIR::RIGHT].emplace_back(Vector2(imageSize.x, -imageSize.y));
        collisionPos_[DIR::RIGHT].emplace_back(Vector2(imageSize.x, imageSize.y));
        collisionPos_[DIR::MAX].emplace_back(Vector2());
    }
}
