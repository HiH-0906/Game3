#include <string>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Common/AnimationController.h"
#include "Common/Capsule.h"
#include "Common/Collider.h"
#include "Common/SpeechBalloon.h"
#include "Planet.h"
#include "Player.h"

Player::Player(SceneManager* manager)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mGravityManager = manager->GetGravityManager();

	mAnimationController = nullptr;
	mState = STATE::NONE;
}

void Player::Init(void)
{

	// モデルの基本設定
	mTransform.SetModel(mResourceManager->LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	mTransform.scl = AsoUtility::VECTOR_ONE;
	mTransform.pos = { 0.0f, -30.0f, 0.0f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = 
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });
	mTransform.Update();

	// アニメーションの設定
	InitAnimation();

	// 初期状態の設定
	ChangeState(STATE::PLAY);
}

void Player::InitAnimation(void)
{

	std::string path = "Data/Model/Player/";
	mAnimationController = new AnimationController(mSceneManager, mTransform.modelId);
	mAnimationController->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::RUN, path + "Run.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::FAST_RUN, path + "FastRun.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::JUMP, path + "Jump.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::WARP_PAUSE, path + "WarpPose.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FLY, path + "Flying.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FALLING, path + "Falling.mv1", 80.0f);
	mAnimationController->Add((int)ANIM_TYPE::VICTORY, path + "Victory.mv1", 60.0f);

	mAnimationController->Play((int)ANIM_TYPE::IDLE);

}

void Player::Update(void)
{

	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		UpdatePlay();
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

	mTransform.Update();
	mAnimationController->Update();
	
}

void Player::UpdatePlay(void)
{
	ProcessMove();

	CalcGravityPow();

	Collision();

	mTransform.quaRot = mGravityManager->GetTransform()->quaRot;

	mTransform.quaRot = mTransform.quaRot.Mult(mPlayerRotY);
}

void Player::Draw(void)
{

	// モデルの描画
	MV1DrawModel(mTransform.modelId);

	// デバッグ用描画
	DrawDebug();

}

void Player::DrawDebug(void)
{

	int white = 0xffffff;
	int black = 0x000000;
	int red = 0xff0000;
	int green = 0x00ff00;
	int blue = 0x0000ff;
	int yellow = 0xffff00;
	int purpl = 0x800080;

	VECTOR v;

	// キャラ基本情報
	//-------------------------------------------------------
	// キャラ座標
	v = mTransform.pos;
	DrawFormatString(20, 60, black, "キャラ座標 ： (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);
	//-------------------------------------------------------

}

void Player::Release(void)
{
}

Transform* Player::GetTransform(void)
{
	return &mTransform;
}

void Player::ProcessMove(void)
{
	// 移動量のリセット
	mMovePow = AsoUtility::VECTOR_ZERO;

	const auto& camera = mSceneManager->GetCamera();

	Quaternion cameraRot = camera->GetQuaRotOutX();

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	double rotRad = 0.0;

	if (CheckHitKey(KEY_INPUT_W))
	{
		dir = cameraRot.GetForward();
		rotRad = AsoUtility::Deg2RadD(0.0);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		dir = cameraRot.GetLeft();
		rotRad = AsoUtility::Deg2RadD(270.0);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		dir = cameraRot.GetBack();
		rotRad = AsoUtility::Deg2RadD(180.0);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		dir = cameraRot.GetRight();
		rotRad = AsoUtility::Deg2RadD(90.0);
	}
	if (!AsoUtility::EqualsVZero(dir))
	{
		mSpeed = SPEED_MOVE;
		ANIM_TYPE type = ANIM_TYPE::RUN;
		if (CheckHitKey(KEY_INPUT_RSHIFT))
		{
			mSpeed = SPEED_RUN;
			type = ANIM_TYPE::FAST_RUN;
		}
		mMovePow = VScale(dir, mSpeed);
		mAnimationController->Play(static_cast<int>(type));
		SetGoalRotate(rotRad);
	}
	else
	{
		mAnimationController->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}

	// 振り向かせたい回転に回転させる
	Rotate();
}

void Player::SetGoalRotate(double rotRad)
{
	const auto& camera = mSceneManager->GetCamera();

	Quaternion cameraRot = camera->GetQuaRotOutX();

	Quaternion  axsis = Quaternion::AngleAxis(cameraRot.y + rotRad, AsoUtility::AXIS_Y);

	double angleDiffDeg = Quaternion::Angle(axsis, mGoalQuaRotY);

	if (std::abs(angleDiffDeg) >= 5.0)
	{
		mRotateRotTime = TIME_ROT;
		mGoalQuaRotY = axsis;
	}
}

void Player::Rotate(void)
{
	mRotateRotTime -= mSceneManager->GetDeltaTime();

	mPlayerRotY = Quaternion::Slerp(mPlayerRotY, mGoalQuaRotY, (TIME_ROT - mRotateRotTime) / TIME_ROT);
}

void Player::CalcGravityPow(void)
{
}

void Player::AddCollider(Collider* collider)
{
	mColliders.emplace_back(collider);
}

void Player::ClearCollider(void)
{
	mColliders.clear();
}

void Player::Collision(void)
{
	mMovedPos = VAdd(mTransform.pos, mMovePow);

	// 衝突(重力)
	CollisionGravity();

	mTransform.pos = mMovedPos;
}

void Player::CollisionGravity(void)
{
	VECTOR dirGravity = mGravityManager->GetDirGravity();
	VECTOR dirUpGravity = mGravityManager->GetDirUpGravity();
	float gravityPow = mGravityManager->GetPower();

	VECTOR gravity = VScale(dirGravity, gravityPow);

	mJumpPow = VAdd(mJumpPow, gravity);
	mMovedPos = VAdd(mMovedPos, mJumpPow);
	mGravHitUp = VAdd(mMovedPos, VScale(dirUpGravity, gravityPow));
	mGravHitUp = VAdd(mGravHitUp, VScale(dirUpGravity, CHECK_HEGHT));
	mGravHitDown = VAdd(mMovedPos, VScale(dirGravity, CHECK_HEGHT));
	for (auto col : mColliders)
	{
		auto hit = MV1CollCheck_Line(col->mModelId, -1, mGravHitUp, mGravHitDown);
		if (hit.HitFlag)
		{
			mMovedPos = VAdd(hit.HitPosition, VScale(dirUpGravity, 2.0f));
			mJumpPow = AsoUtility::VECTOR_ZERO;
		}
	}
}

void Player::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

}
