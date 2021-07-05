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
#include "../XML/RapidXml/rapidxml.hpp"
#include "../XML/RapidXml/rapidxml_utils.hpp"

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
        // @@enumclassÇ…ÇµÇΩÇŸÇ§Ç™ÇÌÇ©ÇËÇ‚Ç∑Ç¢ÇÃÇ≈ÇÕã^òfåªèÛÇQÇ¬ÇµÇ©Ç»Ç¢ÇÃÇ≈ï˙íu
        assert(!"ë∂ç›ÇµÇ»Ç¢InputType");
    }

    rapidxml::file<> moduleFileName = "actionData/test.xml";
    stateVec_ = moduleFileName.vecData();
    stateDoc_.parse<0>(stateVec_.data());
    stateNode_ = stateDoc_.first_node("moduleList");

    size_ = lpAnimMng.GetDivImageSize(charID_, animID_);

    raycast_ = std::make_unique<Raycast>();
    defJunpPower_ = -8;
    yaddPower_ = 0;
    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    mapData_ = mapData;
    controller_->Update();

    for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
    {
        moduleNode_(this, node);
    }
    //tmp |= MoveFunc(INPUT_ID::LEFT, Vector2Flt{ -static_cast<float>(speed_ * delta),0.0f }, -(Vector2Flt{ size_.x / 2.0f ,0.0f }));
    //tmp |= MoveFunc(INPUT_ID::RIGHT, Vector2Flt{ static_cast<float>(speed_ * delta),0.0f }, (Vector2Flt{ size_.x / 2.0f ,0.0f }));
    ////tmp |= MoveFunc(INPUT_ID::UP, Vector2Flt{ 0.0f,-static_cast<float>(speed_ * delta) }, -(Vector2Flt{ 0.0f,size_.y / 2.0f }));
    ////tmp |= MoveFunc(INPUT_ID::DOWN, Vector2Flt{ 0.0f,static_cast<float>(speed_ * delta) }, (Vector2Flt{ 0.0f,size_.y / 2.0f }));
    //if (controller_->GetNow(INPUT_ID::BTN_1))
    //{
    //    yaddPower_ = defJunpPower_;
    //}
    //Vector2Flt moveVec = {};
    //Vector2Flt offset = {};
    //if (yaddPower_ < 0)
    //{
    //    moveVec = { 0.0f,yaddPower_ - size_.y / 2.0f };
    //    offset = { size_.x / 2.0f,0.0f };
    //}
    //else
    //{
    //    moveVec = { 0.0f,yaddPower_ + size_.y / 2.0f };
    //    offset = { size_.x / 2.0f,0.0f };
    //}
    //if (CheckMove(moveVec, offset))
    //{
    //    pos_.y += yaddPower_;
    //    yaddPower_ += 0.2f;
    //}
    //else
    //{
    //    yaddPower_ = 0.2f;
    //}

    // âÊñ í[èàóù
    pos_.x = std::min(std::max(pos_.x, size_.x / 2.0f), lpSceneMng.GetScreenSize().x - (size_.x / 2.0f));
    pos_.y = std::min(std::max(pos_.y, size_.y / 2.0f - 10.0f), lpSceneMng.GetScreenSize().y - (size_.y / 2.0f));
}