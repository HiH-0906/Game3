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
#include "state/state.h"

namespace {
    int junpCnt = 0;
}

Player::Player(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, unsigned int inputType) :
    Pawn(pos,size, oID, inputType)
{ 
    Init(inputType);
}

Player::~Player()
{
}

bool Player::Init(unsigned int inputType)
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

    rapidxml::file<> moduleFileName = "actionData/test.xml";
    stateVec_ = moduleFileName.vecData();
    stateDoc_.parse<0>(stateVec_.data());
    stateNode_ = stateDoc_.first_node("moduleList");

    size_ = {32,64}/*lpAnimMng.GetDivImageSize(objectID_, animID_)*/;

    raycast_ = std::make_unique<Raycast>();
    defJunpPower_ = -8;
    yaddPower_ = 0;
    bullet_ = nullptr;

    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    mapData_ = mapData;
    controller_->Update();

    for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
    {
        (*moduleNode_)(this, node);
    }
    if (bullet_)
    {
        bullet_->Update(delta, mapData);
        if (!bullet_->Alive())
        {
            bullet_.release();
            bullet_ = nullptr;
        }
    }
    // 画面端処理
    pos_.x = std::min(std::max(pos_.x, size_.x / 2.0f), lpSceneMng.GetScreenSize().x - (size_.x / 2.0f));
    pos_.y = std::min(std::max(pos_.y, size_.y / 2.0f - 10.0f), lpSceneMng.GetScreenSize().y - (size_.y / 2.0f));
    UpdateInputBuf();
}