#include "BossShip.h"
#include "SceneManager.h"
#include "EventShot.h"
#include "Camera.h"
#include "AsoUtility.h"

namespace
{
	constexpr float SPEED_MOVE = 4.0f;
	constexpr float EVENT_TIME = 2.0f;
}

BossShip::BossShip(SceneManager* manager, Player* player) :
	sceneManager_(manager), player_(player)
{
}

void BossShip::Init(void)
{
	VECTOR pos = { 0.0f,0.0f,4000.0f };
	transform_.SetModel(MV1LoadModel("Model/BossShip/BossShip.mv1"));
	transform_.scl = { 2.0f,2.0f,2.0f };
	transform_.pos = pos;
	transform_.quaRot = Quaternion::Euler(AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(210.0f), AsoUtility::Deg2RadF(20.0f));
	transform_.quaRotLocal = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	transform_.Update();

	SceneManager::SCENE_ID id = sceneManager_->GetmSceneID();
	switch (id)
	{
	case SceneManager::SCENE_ID::EVENT:
		ChengeState(BOSS_STATE::EVENT);
		break;
	case SceneManager::SCENE_ID::BATTLE:
		ChengeState(BOSS_STATE::BATTLE);
		break;
	default:
		break;
	}

}

void BossShip::Update(void)
{
	switch (state_)
	{
	case BOSS_STATE::EVENT:
		auto nor = VNorm(transform_.GetForward());
		auto moveVec = VScale(nor, SPEED_MOVE);
		transform_.pos = VAdd(transform_.pos, moveVec);

		eventShot_->Update();
		if (!eventShot_->IsAlive())
		{
			stepEvent_ -= sceneManager_->GetDeltaTime();
			if (stepEvent_ < 0.0f)
			{
				sceneManager_->ChangeScene(SceneManager::SCENE_ID::BATTLE,true);
				return;
			}
		}
		break;
	case BOSS_STATE::BATTLE:
		break;
	case BOSS_STATE::EXP:
		break;
	default:
		break;
	}
	transform_.Update();
}

void BossShip::Draw(void)
{
	switch (state_)
	{
	case BOSS_STATE::EVENT:
		MV1DrawModel(transform_.modelId);
		eventShot_->Draw();
		break;
	case BOSS_STATE::BATTLE:
		break;
	case BOSS_STATE::EXP:
		break;
	default:
		break;
	}
}

void BossShip::Release(void)
{
	MV1DeleteModel(transform_.modelId);
	if (eventShot_ != nullptr)
	{
		eventShot_->Release();
		delete eventShot_;
	}
}

void BossShip::ChengeState(BOSS_STATE state)
{
	if (state_ == state)
	{
		return;
	}
	state_ = state;
	switch (state_)
	{
	case BossShip::BOSS_STATE::NON:
		break;
	case BossShip::BOSS_STATE::EVENT:
		stepEvent_ = EVENT_TIME;
		eventShot_ = new EventShot(sceneManager_, &transform_);
		auto norVec = VNorm(VSub(sceneManager_->GetCamera()->GetPos(), transform_.pos));
		eventShot_->Create(transform_.pos, norVec);
		break;
	case BossShip::BOSS_STATE::BATTLE:
		break;
	case BossShip::BOSS_STATE::EXP:
		break;
	case BossShip::BOSS_STATE::END:
		break;
	default:
		break;
	}
}
