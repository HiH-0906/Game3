#include <DxLib.h>
#include <string>
#include "GameScene.h"
#include "TitleScene.h"
#include "Transition/CrossOver.h"
#include "Transition/FadeInOut.h"
#include "../Map/MapData.h"
#include "../Mng/ImageMng.h"
#include "../Object/Player.h"
#include "../Animation/AnimationLoder.h"

GameScene::GameScene()
{
	Init();
	AnimationLoder tmp;
	tmp.LoadAnimTmx("animData/playerAnim.tmx", character_ID::Player);
}

GameScene::~GameScene()
{
}

const SceneID GameScene::GetSceneID(void) const
{
	return SceneID::Game;
}

bool GameScene::Init(void)
{
	mapData_ = std::make_unique<MapData>("mapData/map.tmx");
	
	const auto& info = mapData_->GetMapInfo(MAP_LAYER::BLOCK);

	lpImageMng.GetID("map", info.imageStr, info.chipSize, info.imageSize / info.chipSize);

	objList_.emplace_back(std::make_unique<Player>(Vector2{ 500,300 },120.0,PlayerColor::BLUE));
	objList_.emplace_back(std::make_unique<Player>(Vector2{ 800,300 }, 120.0, PlayerColor::WHITE, 1));

	return true;
}

std::unique_ptr<BaseScene> GameScene::Update(const double& delta, std::unique_ptr<BaseScene> ownScene)
{
	if (CheckHitKey(KEY_INPUT_2))
	{
		return std::make_unique<FadeInOut>(std::move(ownScene), std::make_unique<TitleScene>());
	}
	for (const auto& obj : objList_)
	{
		obj->Update(delta);
	}
	return std::move(ownScene);
}

void GameScene::DrawOwnScreen(const double& delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	for (const auto layer:MAP_LAYER())
	{
		const auto& info = mapData_->GetMapInfo(layer);
		for (int y = 0; y < info.mapSize.y; y++)
		{
			for (int x = 0; x < info.mapSize.x; x++)
			{
				int id = mapData_->GetMapChipData(layer,x, y);
				if (id < 0)
				{
					continue;
				}
				DrawGraph(info.chipSize.x * x, info.chipSize.y * y, lpImageMng.GetID("map")[id], true);
			}
		}
	}
	for (const auto& obj : objList_)
	{
		obj->Draw(delta);
	}
}
