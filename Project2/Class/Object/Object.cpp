#include <DxLib.h>
#include "Object.h"
#include "../Mng/ImageMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

Object::Object(const Vector2& pos, const double& speed, PlayerColor col,unsigned int inputType):
    pos_(pos), playerColor_(col)
{
    id_ = {
    {PlayerColor::BLUE,"B_player_run"},
    {PlayerColor::RED,"R_player_run"},
    {PlayerColor::WHITE,"W_player_run"}
    };
    Init(speed,inputType);
}

bool Object::Init(const double& speed, unsigned int inputType)
{

    lpImageMng.GetID("B_player_run", "Image/player/Blue_witch/B_witch_run.png", Vector2{ 32,48 }, Vector2{ 1,8 });
    lpImageMng.GetID("R_player_run", "Image/player/Red_witch/R_witch_run.png", Vector2{ 48,64 }, Vector2{ 1,8 });
    lpImageMng.GetID("W_player_run", "Image/player/White_witch/W_witch_run.png", Vector2{ 64,64 }, Vector2{ 1,6 });
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
        assert(!"‘¶Ý‚µ‚È‚¢InputType");
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

void Object::Update(const double& delta)
{
    controller_->Update();
    for (auto id : INPUT_ID())
    {
        if (controller_->GetNow(id))
        {
            pos_ += static_cast<Vector2>(speed_[id] * delta);
        }
    }
}

void Object::Draw(const double& delta)
{
    DrawGraph(pos_.x, pos_.y, lpImageMng.GetID(id_[playerColor_])[0],true);
}

