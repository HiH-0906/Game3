#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "Common/Transform.h"
#include "Common/Capsule.h"
#include "Player.h"
#include "WarpStar.h"

WarpStar::WarpStar(SceneManager* manager, Player* player, Transform transform)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mPlayer = player;
	mTransform = transform;

	mState = STATE::NONE;
}

void WarpStar::Init(void)
{

	// モデルの基本情報
	mTransform.SetModel(
		mSceneManager->GetResourceManager()->LoadModelDuplicate(
			ResourceManager::SRC::WARP_STAR)
	);
	mTransform.Update();

	// Z無回転状態の保存
	VECTOR angle = mTransform.quaRot.ToEuler();
	mWarpQua = Quaternion::Euler(angle.x, angle.y, 0.0f);

	// ワープの準備
	mWarpReservePos = VAdd(mTransform.pos, mWarpQua.PosAxis(WARP_RELATIVE_POS));

	ChangeState(STATE::IDLE);

}

void WarpStar::Update(void)
{

	switch (mState)
	{
	case WarpStar::STATE::IDLE:
		UpdateIdle();
		break;
	case WarpStar::STATE::RESERVE:
		UpdateReserve();
		break;
	case WarpStar::STATE::MOVE:
		UpdateMove();
		break;
	}

}

void WarpStar::UpdateIdle(void)
{
	RotateZ(SPEED_ROT_IDLE);

	// 球
	VECTOR sPos = mTransform.pos;
	RADIUS;

	// 点
	VECTOR pPos = mPlayer->GetCapsule()->GetCenter();

	VECTOR diff = VSub(sPos, pPos);

	float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);

	if (dis < (RADIUS * RADIUS))
	{
		ChangeState(STATE::RESERVE);
		return;
	}
}

void WarpStar::UpdateReserve(void)
{
	RotateZ(SPEED_ROT_RESERVE);
	if (mPlayer->IsWarpMove())
	{
		ChangeState(STATE::MOVE);
		return;
	}
}

void WarpStar::UpdateMove(void)
{
	if (mPlayer->IsPlay())
	{
		ChangeState(STATE::IDLE);
	}
}

void WarpStar::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void WarpStar::Release(void)
{
}

Transform* WarpStar::GetTransform(void)
{
	return &mTransform;
}

void WarpStar::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case WarpStar::STATE::IDLE:
		break;
	case WarpStar::STATE::RESERVE:
		mPlayer->StartWarp(TIME_WARP_RESERVE, mWarpQua, mWarpReservePos);
		break;
	case WarpStar::STATE::MOVE:
		break;
	}

}

void WarpStar::RotateZ(const float& speed)
{
	mTransform.quaRot = mTransform.quaRot.Mult(Quaternion::AngleAxis(AsoUtility::Deg2RadF(speed), AsoUtility::AXIS_Z));
	mTransform.Update();
}
