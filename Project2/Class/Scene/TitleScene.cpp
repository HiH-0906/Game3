#include <DxLib.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "Transition/CrossOver.h"
#include "Transition/FadeInOut.h"
#include "Transition/Slide.h"
#include "../Mng/ImageMng.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	lpImageMng.GetID("kishi", "Image/kishi.png");
	return true;
}

const SceneID TitleScene::GetSceneID(void) const
{
	return SceneID::Title;
}

std::unique_ptr<BaseScene> TitleScene::Update(const double& delta, std::unique_ptr<BaseScene> ownScene)
{
	if (CheckHitKey(KEY_INPUT_1))
	{
		return std::make_unique<Slide>(std::move(ownScene), std::make_unique<GameScene>());
	}
	return std::move(ownScene);
}

void TitleScene::DrawOwnScreen(const double& delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("kishi")[0], true);
}
