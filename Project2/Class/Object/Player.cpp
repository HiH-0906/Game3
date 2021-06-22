#include <DxLib.h>
#include "Player.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

namespace
{
    std::map<PlayerColor, std::string> imageKey_ = {
            {PlayerColor::BLUE,"B_player_run"},
            {PlayerColor::RED,"R_player_run"},
            {PlayerColor::WHITE,"W_player_run"}
    };
}


Player::Player(const Vector2& pos, const double& speed, PlayerColor col, unsigned int inputType) :
    Object(pos, speed, inputType), playerColor_(col)
{ 
    key_ = imageKey_[col];
    charID_ = char_ID::Player;
    Init(speed, inputType);
}

Player::~Player()
{
}

bool Player::Init(const double& speed, unsigned int inputType)
{
    // @@@ ほんとにここで読み込みをするのか問題 ダブって登録されない仕組みにはなってはいる
    lpImageMng.GetID(imageKey_[PlayerColor::BLUE], "Image/player/Blue_witch/B_witch_run.png", Vector2{ 32,48 }, Vector2{ 1,8 });
    lpImageMng.GetID(imageKey_[PlayerColor::RED], "Image/player/Red_witch/R_witch_run.png", Vector2{ 48,64 }, Vector2{ 1,8 });
    lpImageMng.GetID(imageKey_[PlayerColor::WHITE], "Image/player/White_witch/W_witch_run.png", Vector2{ 64,64 }, Vector2{ 1,6 });

    lpAnimMng.LoadAnimTmx("animData/playerAnim.tmx", char_ID::Player);
    
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
        assert(!"存在しないInputType");
    }

    speed_.try_emplace(INPUT_ID::LEFT, Vector2Dbl{ -speed,0.0 });
    speed_.try_emplace(INPUT_ID::RIGHT, Vector2Dbl{ speed,0.0 });
    speed_.try_emplace(INPUT_ID::UP, Vector2Dbl{ 0.0,-speed });
    speed_.try_emplace(INPUT_ID::DOWN, Vector2Dbl{ 0.0,speed });
    speed_.try_emplace(INPUT_ID::BTN_1, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::BTN_2, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::BTN_3, Vector2Dbl{ 0.0,0.0 });
    speed_.try_emplace(INPUT_ID::MAX, Vector2Dbl{ 0.0,0.0 });

    return true;
}

void Player::Update(const double& delta)
{
    controller_->Update();
    bool tmp = false;
    for (auto id : INPUT_ID())
    {
        if (controller_->GetNow(id))
        {
            tmp = true;
            pos_ += static_cast<Vector2>(speed_[id] * delta);
        }
    }
    if (tmp)
    {
        SetAnimID(Anim_ID::RUN);
    }
    else
    {
        SetAnimID(Anim_ID::IDLE);
    }
    animCnt_++;
}
