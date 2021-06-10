#include <DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "Transition/CrossOver.h"
#include "Transition/FadeInOut.h"
#include "../Map/MapData.h"
#include "../Mng/ImageMng.h"

GameScene::GameScene()
{
	Init();
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
	lpImageMng.GetID("ryushen", "Image/ryushen.png");
	mapData_ = std::make_unique<MapData>("mapData/map.tmx");
	
	const auto& info = mapData_->GetMapInfo(MAP_LAYER::BLOCK);

	lpImageMng.GetID("map", info.imageStr, info.chipSize, info.imageSize / info.chipSize);

	return true;
}

std::unique_ptr<BaseScene> GameScene::Update(const double& delta, std::unique_ptr<BaseScene> ownScene)
{
	if (CheckHitKey(KEY_INPUT_2))
	{
		return std::make_unique<FadeInOut>(std::move(ownScene), std::make_unique<TitleScene>());
	}
	return std::move(ownScene);
}

void GameScene::DrawOwnScreen(const double& delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//DrawGraph(0, 0, lpImageMng.GetID("ryushen")[0], true);

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
}
