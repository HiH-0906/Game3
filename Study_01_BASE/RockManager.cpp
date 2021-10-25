#include "RockManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Rock.h"
#include "RandomEngine.h"
#include "Player.h"

namespace
{
	constexpr float MAP_DIV_SIZE = 20000.0f;
}

RockManager::RockManager(SceneManager* sceneManager, Player* player)
{
	mSceneManager = sceneManager;
	mPlayer = player;
	mResourceManager = sceneManager->GetResource();
}

void RockManager::Init(void)
{
	mResourceManager->Load(ResourceManager::SRC::ROCK01);
	mResourceManager->Load(ResourceManager::SRC::ROCK02);
}

void RockManager::Update(void)
{
	RandomRockInstance();
}

void RockManager::Draw(void)
{
	for (const auto& rocks : mMapRocks)
	{
		for (const auto rock : rocks.second)
		{
			rock->Draw();
		}
	}
}

void RockManager::Release(void)
{
	for (auto& rocks : mMapRocks)
	{
		for (const auto rock : rocks.second)
		{
			rock->Release();
			delete rock;
		}
		rocks.second.clear();
	}
	mMapRocks.clear();
}

void RockManager::RandomRockInstance(void)
{
	VECTOR mapPos = mPlayer->GetTransForm().pos;
	IntVector3 cMapPos = { static_cast<int>(mapPos.x / MAP_DIV_SIZE) ,static_cast<int>(mapPos.y / MAP_DIV_SIZE) ,static_cast<int>(mapPos.z / MAP_DIV_SIZE )};
	if (mMapRocks.count(cMapPos) != 0)
	{
		return;
	}
	std::vector<Rock*> rocks;
	for (int i = 0; i < 3000; i++)
	{
		rocks.emplace_back(CreateRock(cMapPos));
	}

	mMapRocks.emplace(cMapPos, rocks);

}

Rock* RockManager::CreateRock(IntVector3 mPos)
{
	int random = RandomEngine::RandomInt(0, 1);
	int modelID = -1;
	switch (random)
	{
	case 0:
		modelID = mResourceManager->LoadModelDuplicate(ResourceManager::SRC::ROCK01);
		break;
	case 1:
		modelID = mResourceManager->LoadModelDuplicate(ResourceManager::SRC::ROCK02);
		break;
	default:
		break;
	}

	Rock* re = new Rock();

	float scale = RandomEngine::RandomFloat(30.0f, 150.0f);

	VECTOR pos = { RandomEngine::RandomFloat(-MAP_DIV_SIZE / 2.0f, MAP_DIV_SIZE / 2.0f),RandomEngine::RandomFloat(-MAP_DIV_SIZE / 2.0f, MAP_DIV_SIZE / 2.0f),RandomEngine::RandomFloat(-MAP_DIV_SIZE / 2.0f, MAP_DIV_SIZE / 2.0f) };
	VECTOR angle = { RandomEngine::RandomFloat(0.0f, DX_TWO_PI_F),RandomEngine::RandomFloat(0.0f, DX_TWO_PI_F),0.0f };
	VECTOR scales = { scale ,scale ,scale };

	pos = VAdd(pos, VGet(mPos.x * MAP_DIV_SIZE, mPos.y * MAP_DIV_SIZE, mPos.z * MAP_DIV_SIZE));

	re->Init(
		modelID,
		pos,
		angle,
		scales
	);

	return re;
}
