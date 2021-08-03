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
#include "../collision/Collision.h"
#include "../collision/SquaerCollision.h"
#include "../UI/PlayerUI.h"

namespace
{
	constexpr unsigned int ReviveCnt = 3;
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
	lpImageMng.GetID("UITest", "image/UI/EggUI�����C���[�W.png", { 224,128 }, { 1,1 });


	auto p1UI = std::make_shared<PlayerUI>(Vector2{ 16 ,600 }, Vector2{ 224,128 }, TeamTag::YELLOW,objList_);
	auto p1 = std::make_shared<Player>(Vector2Flt{ 300.0f,68.0f }, Vector2{ 32,64 },
		Object_ID::Pawn, 20, TeamTag::YELLOW, p1UI, ReviveCnt,
		InputType::KEYBOARD);
	p1UI->SetOwner(p1);
	objList_.emplace_back(p1);
	auto p2UI = std::make_shared<PlayerUI>(Vector2{ 316 ,600 }, Vector2{ 224,128 }, TeamTag::SKYBLUE, objList_);
	auto p2 = std::make_shared<Player>(Vector2Flt{ 700.0f,68.0f }, Vector2{ 32,64 },
		Object_ID::Pawn, 20, TeamTag::SKYBLUE, p2UI, ReviveCnt,
		InputType::PAD);
	p2->SetReverse(true);
	p2UI->SetOwner(p2);
	objList_.emplace_back(p2);


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
