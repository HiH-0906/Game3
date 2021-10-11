#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "AsoUtility.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Unit.h"
#include "Enemy.h"
#include "RotateBall.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	stage_ = new Stage(mSceneManager);
	stage_->Init();
	unit_ = new Unit(mSceneManager);
	unit_->Init();
	enemy_ = new Enemy(mSceneManager);
	enemy_->Init();
	auto camera = mSceneManager->GetCamera();
	camera->SetTarget(unit_);
	ball_ = new RotateBall(mSceneManager, unit_);
	ball_->Init();
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}
	stage_->Update();
	unit_->Update();
	enemy_->Update(unit_);
	ball_->Update();
}

void TitleScene::Draw(void)
{
	stage_->Draw();
	unit_->Draw();
	enemy_->Draw();
	ball_->Draw();
	DrawDebug();
}

void TitleScene::DrawDebug(void)
{
#ifdef _DEBUG
	auto camera = mSceneManager->GetCamera();
	auto cPos = camera->GetPos();
	auto cAngle = camera->GetAngle();

	DrawFormatString(0, 10, 0xffffff, "カメラ座標：x:%.1fy:%.1fz:%.1f", cPos.x, cPos.y, cPos.z);
	DrawFormatString(0, 30, 0xffffff, "カメラ角度：x:%.1fy:%.1fz:%.1f", AsoUtility::Rad2Deg(cAngle.x), AsoUtility::Rad2Deg(cAngle.y), AsoUtility::Rad2Deg(cAngle.z));

	auto tarPos = camera->GetTargetPos();

	DrawFormatString(0, 50, 0xffffff, "カメラターゲット座標：x:%.1fy:%.1fz:%.1f", tarPos.x, tarPos.y, tarPos.z);
	DrawSphere3D(tarPos, 10, 5,0xffffff,0xfffff,false);

	auto uPos = unit_->GetPos();
	auto uAngle = unit_->GetAngle();

	DrawFormatString(0, 70, 0xffffff, "キャラクター座標：x:%.1fy:%.1fz:%.1f", uPos.x, uPos.y, uPos.z);
	DrawFormatString(0, 90, 0xffffff, "キャラクター角度：x:%.1fy:%.1fz:%.1f", AsoUtility::Rad2Deg(uAngle.x), AsoUtility::Rad2Deg(uAngle.y), AsoUtility::Rad2Deg(uAngle.z));

	auto bPos = ball_->GetPos();

	DrawFormatString(0, 110, 0xffffff, "ボール座標：x:%.1fy:%.1fz:%.1f", bPos.x, bPos.y, bPos.z);

	auto tmpPos = VSub(bPos, uPos);
	auto bAngle = atan2f(tmpPos.x, tmpPos.z);

	DrawFormatString(0, 130, 0xffffff, "Z正方向からのボール角度：%.1f", abs(AsoUtility::DegIn360(AsoUtility::Rad2Deg(bAngle))));
	DrawFormatString(0, 150, 0xffffff, "Unitからのボール角度：%.1f", abs(AsoUtility::DegIn360(AsoUtility::Rad2Deg(bAngle - uAngle.y))));
#endif // _DEBUG
	
}

void TitleScene::Release(void)
{
	stage_->Release();
	delete stage_;
	unit_->Release();
	delete unit_;
	enemy_->Release();
	delete enemy_;
	ball_->Release();
	delete ball_;
}
