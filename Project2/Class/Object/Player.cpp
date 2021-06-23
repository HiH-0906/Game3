#include <DxLib.h>
#include "Player.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"



Player::Player(const Vector2& pos, const double& speed, const char_ID cID, unsigned int inputType) :
    Object(pos, speed, cID, inputType)
{ 
    Init(speed, inputType);
}

Player::~Player()
{
}

bool Player::Init(const double& speed, unsigned int inputType)
{
    // @@åªç›ÇÕÇ±Ç±Ç≈ì«Ç›çûÇÒÇ≈Ç¢ÇÈÇ™ÉLÉÉÉâÇ∆Ç©Ç™ëùÇ¶ÇÈÇÊÇ§Ç»ÇÁGameSceneÇÃInitÇ∆Ç©Ç≈Ç‚ÇÈÇÃÇ™Ç¢Ç¢Ç©Ç‡
    lpAnimMng.LoadAnimTmx("animData/BluePlayerAnim.tmx", char_ID::B_Player);
    lpAnimMng.LoadAnimTmx("animData/WhitePlayerAnim.tmx", char_ID::W_Player);
    lpAnimMng.LoadAnimTmx("animData/RedPlayerAnim.tmx", char_ID::R_Player);
    
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
        SetAnimation(Anim_ID::RUN);
    }
    else
    {
        SetAnimation(Anim_ID::IDLE);
    }
}
