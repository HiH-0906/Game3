#include <DxLib.h>
#include <string>
#include <memory>
#include <list>
#include <algorithm>
#include "GameScene.h"
#include "TitleScene.h"
#include "Transition/CrossOver.h"
#include "Transition/FadeInOut.h"
#include "../Map/MapData.h"
#include "../Mng/ImageMng.h"
#include "../Mng/AnimationMng.h"
#include "../Mng/CollisionMng.h"
#include "../Object/Player.h"
#include "../Object/Egg.h"
#include "../collision/Collision.h"
#include "../collision/SquaerCollision.h"
#include "../UI/PlayerUI.h"

namespace
{
	constexpr int PlayerRiviveNum = 4;
}

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
	DeleteMaskScreen();
}

const SceneID GameScene::GetSceneID(void) const
{
	return SceneID::Game;
}

bool GameScene::Init(void)
{
	AnimInit();
	CreateMaskScreen();
	mapData_ = std::make_unique<MapData>("mapData/map.tmx");

	const auto& info = mapData_->GetMapInfo(MAP_LAYER::BLOCK);

	lpImageMng.GetID("map", info.imageStr, info.chipSize, info.imageSize / info.chipSize);
	lpImageMng.GetID("UITest", "image/UI/EggUIäÆê¨ÉCÉÅÅ[ÉW.png", { 224,128 }, { 1,1 });

	std::list<std::weak_ptr<Egg>> list;

	auto p1UI = std::make_shared<PlayerUI>(Vector2{ 16 ,600 }, Vector2{ 224,128 }, TeamTag::RED);

	objList_.emplace_back(
		std::make_shared<Player>(Vector2Flt{ 500.0f,100.0f }, Vector2{0,0},
		Object_ID::Pawn,20,TeamTag::RED, p1UI,
			InputType::KEYBOARD)
	);
	for (int i = 0; i < PlayerRiviveNum; i++)
	{
		auto egg = std::make_shared<Egg>(Vector2Flt{ 112.0f + i * 32.0f,660.0f }, Vector2{ 32,32 }, Object_ID::Egg, TeamTag::RED, InputType::KEYBOARD, p1UI, objList_);
		objList_.emplace_back(egg);
		list.emplace_back(egg);
	}
	p1UI->SetList(list);
	list.clear();

	auto p2UI = std::make_shared<PlayerUI>(Vector2{ 316 ,600 }, Vector2{ 224,128 }, TeamTag::BLUE);

	objList_.emplace_back(
		std::make_shared<Player>(Vector2Flt{ 500.0f,100.0f }, Vector2{ 0,0 }, 
		Object_ID::Pawn, 20, TeamTag::BLUE, 
			p2UI,InputType::PAD)
	);
	for (int i = 0; i < PlayerRiviveNum; i++)
	{
		auto egg = std::make_shared<Egg>(Vector2Flt{ 412.0f + i * 32.0f,660.0f }, Vector2{32,32}, Object_ID::Egg, TeamTag::BLUE, InputType::PAD, p2UI, objList_);
		objList_.emplace_back(egg);
		list.emplace_back(egg);
	}
	p2UI->SetList(list);
	list.clear();


	for (const auto& obj : objList_)
	{
		Vector2Flt size = static_cast<Vector2Flt>(obj->GetSize());
		auto col = std::make_shared<SquaerCollision>(size, size / 2.0f);
		col->SetOwner(obj);
		lpCollisionMng.RegistrationCol(col);
	}

	return true;
}

void GameScene::AnimInit(void)
{
	lpAnimMng.LoadAnimTmx("animData/PlayerAnim.tmx", Object_ID::Pawn);
}

std::unique_ptr<BaseScene> GameScene::Update(const double& delta, std::unique_ptr<BaseScene> ownScene)
{
	auto itr = std::remove_if(objList_.begin(), objList_.end(), [](std::shared_ptr<Object> obj) {return obj->CheckIsDead(); });
	objList_.erase(itr, objList_.end());
	if (CheckHitKey(KEY_INPUT_2))
	{
		return std::make_unique<FadeInOut>(std::move(ownScene), std::make_unique<TitleScene>());
	}
	for (const auto& obj : objList_)
	{
		obj->Update(delta,mapData_);
	}
	lpCollisionMng.Update();
	return std::move(ownScene);
}

void GameScene::DrawOwnScreen(const double& delta)
{
	SetUseMaskScreenFlag(false);
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	//DrawGraph(16, 600, lpImageMng.GetID("UITest")[0],true);

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
