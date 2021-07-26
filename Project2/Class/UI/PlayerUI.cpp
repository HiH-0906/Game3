#include <cassert>
#include <DxLib.h>
#include "PlayerUI.h"
#include "../Mng/ImageMng.h"

PlayerUI::PlayerUI(const Vector2& pos, const Vector2& scrSize, const TeamTag& tag) :
	UIBase(pos, scrSize)
{
	lpImageMng.GetID("PlayerIcon", "Image/UI/Icon/chikinIcon.png", { 64,64 }, { 1,1 });
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

void PlayerUI::UpDate(const double& delta)
{
	
}

void PlayerUI::UIDraw(void)
{
	SetUseMaskScreenFlag(true);
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawMask(0, 0, mask_, DX_MASKTRANS_NONE);
	DrawBox(0, 0, scrSize_.x, scrSize_.y, col_, true);
	SetUseMaskScreenFlag(false);
	DrawGraph(20, 25, lpImageMng.GetID("PlayerIcon")[0], true);
}
