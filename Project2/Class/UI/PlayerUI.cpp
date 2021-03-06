#include <cassert>
#include <DxLib.h>
#include "PlayerUI.h"
#include "../Mng/ImageMng.h"
#include "../Mng/CollisionMng.h"
#include "../Object/Player.h"
#include "../collision/SquaerCollision.h"


PlayerUI::PlayerUI(const Vector2& pos, const Vector2& scrSize, const TeamTag& tag, std::list<std::shared_ptr<Object>>& list) :
	UIBase(pos, scrSize),objList_(list)
{
	lpImageMng.GetID("PlayerIcon", "Image/UI/Icon/chikinIcon.png", { 64,64 }, { 1,1 });
	lpImageMng.GetID("Egg", "Image/UI/Egg.png", { 32,32 }, { 1,1 });
	col_ = 0xffffff;
	mask_ = LoadMask("Image/UI/UIBGMask.png");
	switch (tag)
	{
	case TeamTag::NON:
		col_ = 0xffffff;
		break;
	case TeamTag::SKYBLUE:
		col_ = 0x00ffff;
		break;
	case TeamTag::YELLOW:
		col_ = 0xffff00;
		break;
	case TeamTag::MAP:
		col_ = 0xffffff;
		assert(!"マップがPlayerUIをインスタンスしている");
		break;
	default:
		col_ = 0xffffff;
		assert(!"PlayerUIをインスタンス時エラー");
		break;
	}
}

void PlayerUI::SetRevive(const double& time)
{
}

void PlayerUI::SetOwner(std::weak_ptr<Pawn> owner)
{
	owner_ = owner;
}

void PlayerUI::UpDate(const double& delta)
{
	
}

void PlayerUI::InstancePlayer(void)
{
	auto obj = std::make_shared<Player>(Vector2Flt{ 500.0f,100.0f }, Vector2{ 32,64 },
		Object_ID::Pawn, 20, owner_.lock()->GetTeamTag(),
		shared_from_this(), owner_.lock()->GetReviveCnt() - 1, owner_.lock()->GetInputType());
	obj->SetInvincibleCnt(3.0);
	objList_.emplace_back(obj);
	Vector2Flt size = static_cast<Vector2Flt>(obj->GetSize());
	auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
	col->SetOwner(obj);
	lpCollisionMng.RegistrationCol(col);
	SetOwner(obj);
}

const int& PlayerUI::GetCol(void) const
{
	return col_;
}

void PlayerUI::UIDraw(const double& delta)
{
	SetUseMaskScreenFlag(true);
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawMask(0, 0, mask_, DX_MASKTRANS_NONE);
	DrawBox(0, 0, scrSize_.x, scrSize_.y, col_, true);
	SetUseMaskScreenFlag(false);
	DrawGraph(20, 25, lpImageMng.GetID("PlayerIcon")[0], true);
	for (unsigned int i = 0; i < owner_.lock()->GetReviveCnt(); i++)
	{
		DrawGraph(90 + i * 32, 50, lpImageMng.GetID("Egg")[0], true);
	}
	SetDrawScreen(DX_SCREEN_BACK);
}
