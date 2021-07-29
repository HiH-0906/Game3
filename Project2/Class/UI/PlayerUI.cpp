#include <cassert>
#include <DxLib.h>
#include "PlayerUI.h"
#include "../Mng/ImageMng.h"
#include "../Object/Player.h"


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
	case TeamTag::BLUE:
		col_ = 0x0000ff;
		break;
	case TeamTag::RED:
		col_ = 0xff0000;
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
	auto obj = std::make_shared<Player>(Vector2Flt{ 500.0f,100.0f }, Vector2{ 0,0 },
		Object_ID::Pawn, 20, owner_.lock()->GetTeamTag(), 
		shared_from_this(), owner_.lock()->GetInputType());
	objList_.emplace_back(obj);
	SetOwner(obj);
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
}
