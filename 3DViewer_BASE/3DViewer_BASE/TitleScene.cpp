#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "AsoUtility.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Unit.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	stage_ = new Stage(mSceneManager);
	stage_->Init();
	unit_ = new Unit(mSceneManager);
	unit_->Init();
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}
	stage_->Update();
	unit_->Update();
}

void TitleScene::Draw(void)
{
	stage_->Draw();
	unit_->Draw();
	DrawDebug();
}

void TitleScene::DrawDebug(void)
{
#ifdef _DEBUG
	auto camera = mSceneManager->GetCamera();
	auto cPos = camera->GetPos();
	auto cAngle = camera->GetAngle();

	DrawFormatString(0, 10, 0xffffff, "�J�������W�Fx:%.1fy:%.1fz:%.1f", cPos.x, cPos.y, cPos.z);
	DrawFormatString(0, 30, 0xffffff, "�J�����p�x�Fx:%.1fy:%.1fz:%.1f", AsoUtility::Rad2Deg(cAngle.x), AsoUtility::Rad2Deg(cAngle.y), AsoUtility::Rad2Deg(cAngle.z));

	auto uPos = unit_->GetPos();
	auto uAngle = unit_->GetAngle();

	DrawFormatString(0, 50, 0xffffff, "�L�����N�^�[���W�Fx:%.1fy:%.1fz:%.1f", uPos.x, uPos.y, uPos.z);
	DrawFormatString(0, 70, 0xffffff, "�L�����N�^�[�p�x�Fx:%.1fy:%.1fz:%.1f", AsoUtility::Rad2Deg(uAngle.x), AsoUtility::Rad2Deg(uAngle.y), AsoUtility::Rad2Deg(uAngle.z));
#endif // _DEBUG
	
}

void TitleScene::Release(void)
{
	stage_->Release();
	delete stage_;
	unit_->Release();
	delete unit_;

}
