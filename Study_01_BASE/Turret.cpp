#include "DxLib.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Turret.h"
#include "TurretShot.h"

Turret::Turret(SceneManager* manager,
	Transform* transformPlayer,
	Transform* transformParent,
	VECTOR localPos,
	VECTOR localAddAxis)
{

	mSceneManager = manager;
	mTransformPlayer = transformPlayer;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;

	ResourceManager* rem = mSceneManager->GetResource();

	mTransformStand.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_STAND));
	mTransformGun.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_GUN));

	mExplosion = new SpriteAnimator(
		mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);

	mStepDamaged = -1;

	// 砲身ローカル回転
	mLocalAddAxisStand = { 0.0f, 0.0f, 0.0f };
	mLocalAddAxisGun = { 0.0f, 0.0f, 0.0f };

	mAttackTime = ATTACK_TIME;

	ChangeState(STATE::ATTACK);

}

void Turret::Init(void)
{

	Quaternion localRot;
	Quaternion axis;

	// モデル制御の基本情報(砲台)
	mTransformStand.scl = { SCALE, SCALE, SCALE };
	mTransformStand.quaRot = Quaternion();

	// ローカル回転
	mTransformStand.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// 親モデルと同期
	SyncParent(&mTransformStand, mLocalAddAxisStand);



	// モデル制御の基本情報(砲身)
	mTransformGun.scl = { SCALE, SCALE, SCALE };
	mTransformGun.quaRot = Quaternion();

	// ローカル回転
	mTransformGun.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(-5.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// 親モデルと同期
	SyncParent(&mTransformGun, mLocalAddAxisGun);
	// 耐久力
	mHp = 2;

	// 砲台ローカル稼働量(deg)
	mAnglePowStand = ANGLE_POW_STAND;

	// 砲身ローカル稼働量(deg)
	mAnglePowGun = ANGLE_POW_GUN;

}

void Turret::Update(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
	{

		float deg;

		// 砲台ローカル回転

		// 砲台
		mLocalAddAxisStand.y += mAnglePowStand * mSceneManager->GetDeltaTime();
		if (std::abs(mLocalAddAxisStand.y) >= AsoUtility::Deg2RadF(ANGLE_Y_MAX_STAND))
		{
			mAnglePowStand *= -1.0f;
		}
		SyncParent(&mTransformStand, mLocalAddAxisStand);

		// 砲身ローカル回転
		mLocalAddAxisGun.x += mAnglePowGun * mSceneManager->GetDeltaTime();
		if (mLocalAddAxisGun.x >= AsoUtility::Deg2RadF(ANGLE_X_MAX_GUN) || mLocalAddAxisGun.x <= AsoUtility::Deg2RadF(ANGLE_X_MIN_GUN))
		{
			mAnglePowGun *= -1.0f;
		}
		// 砲身
		Quaternion stand = Quaternion::Euler(mLocalAddAxisStand);
		Quaternion gun = Quaternion::Euler(mLocalAddAxisGun);

		Quaternion mix = stand.Mult(gun);


		SyncParent(&mTransformGun, mix.ToEuler());

		// 被ダメ判定
		if (mStepDamaged > 0.0f)
		{
			mStepDamaged -= mSceneManager->GetDeltaTime();
		}
		mAttackTime -= mSceneManager->GetDeltaTime();
		if (mAttackTime <= 0.0f)
		{
			auto shot = new TurretShot(mSceneManager, &mTransformGun);
			auto shotPos = mTransformGun.pos;
			shotPos = VAdd(shotPos, VScale(VNorm(mTransformGun.GetUp()), 155.0f));
			shotPos = VAdd(shotPos, VScale(VNorm(mTransformGun.GetForward()), 155.0f));
			shot->Create(shotPos, mTransformGun.GetForward());
			shots_.emplace_back(std::move(shot));
			mAttackTime = ATTACK_TIME;
		}
	}
		break;
	case Turret::STATE::DESTROY:

		// 弾の更新
		mExplosion->Update();
		break;
	}
	for (const auto& shot : shots_)
	{
		if (!shot->IsAlive())
		{
			continue;
		}
		shot->Update();
	}
}

void Turret::Draw(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:

		if (mStepDamaged > 0.0f)
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
		}
		else
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.48f, 0.52f, 0.4f, 1.0f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.2f, 0.4f, 0.3f, 1.0f));
		}

		MV1DrawModel(mTransformStand.modelId);
		MV1DrawModel(mTransformGun.modelId);

		if (IS_DEBUG)
		{
			DrawSphere3D(mTransformStand.pos, COLLISION_RADIUS, 10, 0xff0000, 0xffffff, false);
		}

		break;
	case Turret::STATE::DESTROY:
		mExplosion->Draw();
		break;
	}
	for (const auto& shot : shots_)
	{
		if (!shot->IsAlive())
		{
			continue;
		}
		shot->Draw();
	}
}

void Turret::Release(void)
{

	mExplosion->Release();
	delete mExplosion;
	for (const auto& shot : shots_)
	{
		shot->Release();
		delete shot;
	}
}

void Turret::SyncParent(Transform* transform, VECTOR addAxis)
{
	VECTOR localPos;
	transform->quaRot = mTransformParent->quaRot;
	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);
	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	Quaternion localRot = Quaternion::Euler(mLocalAddAxis);

	transform->quaRot = transform->quaRot.Mult(localRot);

	localRot = {};
	Quaternion axis;

	// 回転順が大事
	// Unity z->x->y-> = y * x * z

	axis = Quaternion::AngleAxis(addAxis.y, AsoUtility::AXIS_Y);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.x, AsoUtility::AXIS_X);
	localRot = localRot.Mult(axis);

	axis = Quaternion::AngleAxis(addAxis.z, AsoUtility::AXIS_Z);
	localRot = localRot.Mult(axis);

	transform->quaRot = transform->quaRot.Mult(localRot);



	// モデルの情報更新
	transform->Update();

}

const std::vector<TurretShot*> Turret::GetShots(void) const
{
	return shots_;
}

bool Turret::IsAlive(void)
{
	return mState == STATE::ATTACK;
}

VECTOR Turret::GetPos(void)
{
	return mTransformStand.pos;
}

void Turret::Damage(void)
{

	mStepDamaged = TIME_DAMAGED_EFFECT;

	mHp -= 1;
	if (mHp <= 0)
	{
		ChangeState(STATE::DESTROY);
	}

}

void Turret::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
		break;
	case Turret::STATE::DESTROY:
	{
		auto mat = mTransformGun.quaRot.ToMatrix();
		auto localPos = VTransform({ 0.0f, 1.2f, 0.0f }, mat);
		auto birthPos = VAdd(mTransformStand.pos, VScale(localPos, SCALE));
		mExplosion->Create(birthPos);
	}
	break;
	}

}
