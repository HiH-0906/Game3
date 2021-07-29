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
#include "../UI/PlayerUI.h"



Player::Player(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, int hp, TeamTag tag, std::shared_ptr<PlayerUI> ui, InputType inputType) :
    Pawn(pos, size, oID, hp, tag, ui, inputType)
{ 
    Init(inputType);
    deadTime_ = 3.0;
}

Player::~Player()
{
}

bool Player::Init(InputType inputType)
{    
    if (inputType == InputType::KEYBOARD)
    {
        controller_ = std::make_unique<KeyBoard>();
    }
    else if (inputType == InputType::PAD)
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

    size_ = { 32,64 };

    raycast_ = std::make_unique<Raycast>();
    defJunpPower_ = -12;
    yaddPower_ = 0;
    bullet_ = nullptr;
    isRevive_ = false;
    InitAttackFunc();
    return true;
}

void Player::Update(const double& delta, std::weak_ptr<MapData> mapData)
{
    delta_ = delta;
    mapData_ = mapData;
    if (!isAlive_)
    {
        deadTime_ -= delta;
        if (deadTime_ <= 0&&!)
        {
            ui_->InstancePlayer();
        }
    }
    if (isAlive_)
    {
        controller_->Update();
    }
    controller_->UpdateRingBuf(delta);
    controller_->DebugRingBuf();

    if (bullet_)
    {
        bullet_->Update(delta, mapData);
        if (!bullet_->Alive())
        {
            bullet_ = nullptr;
        }
    }

    for (auto node = stateNode_->first_node(); node != nullptr; node = node->next_sibling())
    {
        (*moduleNode_)(this, node);
    }
    // âÊñ í[èàóù
    pos_.x = std::min(std::max(pos_.x, size_.x / 2.0f), lpSceneMng.GetScreenSize().x - (size_.x / 2.0f));
    pos_.y = std::min(std::max(pos_.y, size_.y / 2.0f - 10.0f), lpSceneMng.GetScreenSize().y - (size_.y / 2.0f));
    ui_->UpDate(delta);
    ui_->UIDraw(delta);
}

void Player::InitAttackFunc(void)
{
    attackFuncMap_["HadoKen"] = [&]()
    {
        TRACE("HadoKen!!\n");
        if (!bullet_)
        {
            Vector2Flt speed = {};
            if (reverseXFlag_)
            {
                speed = { -5.0f,0.0f };
            }
            else
            {
                speed = { 5.0f,0.0f };
            }
            bullet_ = std::make_shared<Bullet>(pos_, Vector2{ 32,32 }, 10, Object_ID::Bullet, speed, reverseXFlag_, teamTag_);
            Vector2Flt size = static_cast<Vector2Flt>(bullet_->GetSize());
            auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
            col->SetOwner(bullet_);
            lpCollisionMng.RegistrationCol(col);
        }
    };
    attackFuncMap_["SyoryuKen"] = [&]()
    {
        TRACE("SyoryuKen!!\n");
        if (!bullet_)
        {
            Vector2Flt speed = {};
            if (reverseXFlag_)
            {
                speed = { -20.0f,0.0f };
            }
            else
            {
                speed = { 20.0f,0.0f };
            }
            bullet_ = std::make_shared<Bullet>(pos_, Vector2{ 32,32 }, 5, Object_ID::Bullet, speed, reverseXFlag_, teamTag_);
            Vector2Flt size = static_cast<Vector2Flt>(bullet_->GetSize());
            auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
            col->SetOwner(bullet_);
            lpCollisionMng.RegistrationCol(col);
        }
    };
    attackFunc_ = attackFuncMap_["HadoKen"];
}
