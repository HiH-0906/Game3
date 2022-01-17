#include <string>
#include <EffekseerForDXLib.h>
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

	// ���f���̊�{�ݒ�
	mTransform.SetModel(mResourceManager->LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	mTransform.scl = AsoUtility::VECTOR_ONE;
	mTransform.pos = { 0.0f, -30.0f, 0.0f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = 
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });
	mTransform.Update();
	
	// �ۉe�ǂݍ���
	mImageShadow = LoadGraph("Data/Image/Shadow.png");

	// �����ǂݍ���
	mEffectSmoke = mResourceManager->Load(ResourceManager::SRC::FOOT_SMOKE).mHandleId;

	mEffectWarpOrbit = mResourceManager->Load(
		ResourceManager::SRC::WARP_ORBIT).mHandleId;

	mFrameLeftHand = MV1SearchFrame(mTransform.modelId, "mixamorig:LeftHand");
	mFrameRightHand = MV1SearchFrame(mTransform.modelId, "mixamorig:RightHand");

	// �W�����v�n�ϐ��̏�����
	mIsJump = false;
	mStepJump = 0.0f;
	mJumpPow = AsoUtility::VECTOR_ZERO;

	mCapsule = new Capsule(&mTransform);
	mCapsule->SetRelativePosTop({ 0.0f,110.0f,0.0f });
	mCapsule->SetRelativePosDown({ 0.0f,30.0f,0.0f });
	mCapsule->SetRadius(20.0f);

	// �A�j���[�V�����̐ݒ�
	InitAnimation();

	// ������Ԃ̐ݒ�
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
		UpdateWarpReserve();
		break;
	case Player::STATE::WARP_MOVE:
		UpdateWarpMove();
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

	ProcessJump();

	CalcSlope();

	CalcGravityPow();

	Collision();

	mTransform.quaRot = mGravityManager->GetTransform()->quaRot;

	mTransform.quaRot = mTransform.quaRot.Mult(mPlayerRotY);

	EffectFootSmoke();
}

void Player::Draw(void)
{

	// ���f���̕`��
	MV1DrawModel(mTransform.modelId);

	// �ۉe�`��
	DrawShadow();

	// �f�o�b�O�p�`��
	DrawDebug();

}

void Player::DrawShadow(void)
{
	float PLAYER_SHADOW_HEIGHT = 300.0f;
	float PLAYER_SHADOW_SIZE = 40.0f;

	int i;
	MV1_COLL_RESULT_POLY_DIM HitResDim;
	MV1_COLL_RESULT_POLY* HitRes;
	VERTEX3D Vertex[3];
	VECTOR SlideVec;
	int ModelHandle;

	// ���C�e�B���O�𖳌��ɂ���
	SetUseLighting(FALSE);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �e�N�X�`���A�h���X���[�h�� CLAMP �ɂ���( �e�N�X�`���̒[����͒[�̃h�b�g�����X���� )
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// �e�𗎂Ƃ����f���̐������J��Ԃ�
	for(const auto& col :mColliders)
	{
		ModelHandle = col->mModelId;

		// �v���C���[�̒����ɑ��݂���n�ʂ̃|���S�����擾
		HitResDim = MV1CollCheck_Capsule(ModelHandle, -1, mTransform.pos, VAdd(mTransform.pos, VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)), PLAYER_SHADOW_SIZE);

		// ���_�f�[�^�ŕω��������������Z�b�g
		Vertex[0].dif = GetColorU8(255, 255, 255, 255);
		Vertex[0].spc = GetColorU8(0, 0, 0, 0);
		Vertex[0].su = 0.0f;
		Vertex[0].sv = 0.0f;
		Vertex[1] = Vertex[0];
		Vertex[2] = Vertex[0];

		// ���̒����ɑ��݂���|���S���̐������J��Ԃ�
		HitRes = HitResDim.Dim;
		for (i = 0; i < HitResDim.HitNum; i++, HitRes++)
		{
			// �|���S���̍��W�͒n�ʃ|���S���̍��W
			Vertex[0].pos = HitRes->Position[0];
			Vertex[1].pos = HitRes->Position[1];
			Vertex[2].pos = HitRes->Position[2];

			// ������Ǝ����グ�ďd�Ȃ�Ȃ��悤�ɂ���
			SlideVec = VScale(HitRes->Normal, 0.5f);
			Vertex[0].pos = VAdd(Vertex[0].pos, SlideVec);
			Vertex[1].pos = VAdd(Vertex[1].pos, SlideVec);
			Vertex[2].pos = VAdd(Vertex[2].pos, SlideVec);

			// �|���S���̕s�����x��ݒ肷��
			Vertex[0].dif.a = 0;
			Vertex[1].dif.a = 0;
			Vertex[2].dif.a = 0;
			if (HitRes->Position[0].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[0].dif.a = 128 * (1.0f - fabs(HitRes->Position[0].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			if (HitRes->Position[1].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[1].dif.a = 128 * (1.0f - fabs(HitRes->Position[1].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			if (HitRes->Position[2].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[2].dif.a = 128 * (1.0f - fabs(HitRes->Position[2].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			// �t�u�l�͒n�ʃ|���S���ƃv���C���[�̑��΍��W���犄��o��
			Vertex[0].u = (HitRes->Position[0].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[0].v = (HitRes->Position[0].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[1].u = (HitRes->Position[1].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[1].v = (HitRes->Position[1].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[2].u = (HitRes->Position[2].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[2].v = (HitRes->Position[2].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;

			// �e�|���S����`��
			DrawPolygon3D(Vertex, 1, mImageShadow, TRUE);
		}

		// ���o�����n�ʃ|���S�����̌�n��
		MV1CollResultPolyDimTerminate(HitResDim);
	}

	// ���C�e�B���O��L���ɂ���
	SetUseLighting(TRUE);

	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBuffer3D(FALSE);
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

	// �L������{���
	//-------------------------------------------------------
	// �L�������W
	v = mTransform.pos;
	DrawFormatString(20, 60, black, "�L�������W �F (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);
	//-------------------------------------------------------

	DrawLine3D(mGravHitUp, mGravHitDown, 0xffffff);

	// �L�������W
	v = mJumpPow;
	DrawFormatString(20, 80, black, "�d�� �F (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);

	
	DrawFormatString(20, 100, black, "�X�Ίp �F (%0.2f)",
		mSlopeAngleDeg
	);

	mCapsule->Draw();
}

void Player::Release(void)
{
	DeleteGraph(mImageShadow);
	delete mCapsule;
}

Transform* Player::GetTransform(void)
{
	return &mTransform;
}

void Player::ProcessMove(void)
{
	// �ړ��ʂ̃��Z�b�g
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
	ANIM_TYPE type = ANIM_TYPE::IDLE;
	if (!AsoUtility::EqualsVZero(dir) && (mIsJump || isEndLanding()))
	{
		mSpeed = SPEED_MOVE;
		type = ANIM_TYPE::RUN;
		if (CheckHitKey(KEY_INPUT_RSHIFT))
		{
			mSpeed = SPEED_RUN;
			type = ANIM_TYPE::FAST_RUN;
		}
		mMovePow = VScale(dir, mSpeed);
		SetGoalRotate(rotRad);
	}
	if (!mIsJump && isEndLanding())
	{
		mAnimationController->Play(static_cast<int>(type));
	}

	// �U�������������]�ɉ�]������
	Rotate();
}

void Player::ProcessJump(void)
{
	bool isHitKey = CheckHitKey(KEY_INPUT_BACKSLASH);
	if (isHitKey && (mIsJump || isEndLanding()))
	{
		
		if (mIsJump)
		{
			// �W�����v�A�j���[�V����
			//mAnimationController->Play(static_cast<int>(ANIM_TYPE::JUMP));
			mAnimationController->Play(static_cast<int>(ANIM_TYPE::JUMP), true, 13.0f, 25.0f);
			mAnimationController->SetEndLoop(23.0f, 25.0f, 5.0f);
		}

		mStepJump += mSceneManager->GetDeltaTime();
		if (mStepJump < TIME_JUMP_IN)
		{
			mJumpPow = VScale(mGravityManager->GetDirUpGravity(), POW_JUMP);
		}
		mIsJump = true;
	}

	if (!isHitKey)
	{
		mStepJump = TIME_JUMP_IN;
	}
}

void Player::SetGoalRotate(double rotRad)
{
	const auto& camera = mSceneManager->GetCamera();

	Quaternion cameraRot = camera->GetQuaRot();

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

void Player::CalcSlope(void)
{
	VECTOR gravityUp = mGravityManager->GetDirUpGravity();
	// �d�͂̔��Ε�������n�ʂ̖@�������Ɍ�������]�ʂ��擾
	Quaternion up2GNorQua = Quaternion::FromToRotation(gravityUp, mHitNormal);
	// �擾������]�̎��Ɗp�x���擾����
	float angle;
	float* anglePtr = &angle;
	VECTOR axis;
	up2GNorQua.ToAngleAxis(anglePtr, &axis);
	// 90�x�����āA�X�΃x�N�g���ւ̉�]���擾����
	Quaternion slopeQ = Quaternion::AngleAxis(angle + AsoUtility::Deg2RadD(90.0), axis);
	// �n�ʂ̌X�ΐ�(��)
	mSlopeDir = slopeQ.PosAxis(gravityUp);
	// �X�΂̊p�x
	mSlopeAngleDeg = AsoUtility::AngleDeg(gravityUp, mSlopeDir);
	// �X�΂ɂ��ړ�
	if (AsoUtility::SqrMagnitude(mJumpPow) == 0.0f)
	{
		float CHECK_ANGLE = 120.0f;
		if (mSlopeAngleDeg >= CHECK_ANGLE)
		{
			float diff = abs(mSlopeAngleDeg - CHECK_ANGLE);
			mSlopePow = VScale(mSlopeDir, diff / 3.0f);mMovePow = VAdd(mMovePow, mSlopePow);
		}
	}
}

void Player::CalcGravityPow(void)
{
	VECTOR dirGravity = mGravityManager->GetDirGravity();

	float gravityPow = mGravityManager->GetPower();

	VECTOR gravity = VScale(dirGravity, gravityPow);

	mJumpPow = VAdd(mJumpPow, gravity);

	float dot = VDot(dirGravity, mJumpPow);

	if (dot >= 0.0f)
	{
		mJumpPow = gravity;
	}
}

void Player::AddCollider(Collider* collider)
{
	mColliders.emplace_back(collider);
}

void Player::ClearCollider(void)
{
	mColliders.clear();
}

void Player::UpdateWarpReserve(void)
{
	mStepWarp -= mSceneManager->GetDeltaTime(); 
	if (mStepWarp < 0.0f) 
	{ 
		mTransform.quaRot = mWarpQua; mTransform.pos = mWarpReservePos; ChangeState(STATE::WARP_MOVE); 
		return; 
	}
	else 
	{ 
		float t = 1.0f - (mStepWarp / mTimeWarp);
		mTransform.quaRot = Quaternion::Slerp(mReserveStartQua, mWarpQua, t);
		mTransform.pos = AsoUtility::Lerp(mReserveStartPos, mWarpReservePos, t); 
	}
}

void Player::UpdateWarpMove(void)
{
	VECTOR dir = mWarpQua.GetForward(); 
	mTransform.pos = VAdd(mTransform.pos, VScale(dir, 30.0f)); 
	Stage::NAME name = mGravityManager->GetActivePlanet()->GetName();
	if (name != mPreWarpName) 
	{
		// �G�t�F�N�g��~
		StopOrbitEffect();
		// �����A�j���[�V����
		mAnimationController->Play((int)ANIM_TYPE::JUMP, true, 13.0f, 25.0f);
		mAnimationController->SetEndLoop(23.0f, 25.0f, 5.0f);
		ChangeState(Player::STATE::PLAY);
		return;
	}mTransform.Update();
	// �G�t�F�N�g�̈ʒu�𓯊�
	SyncWarpOrbitPos();
}

Capsule* Player::GetCapsule(void)
{
	return mCapsule;
}

bool Player::IsPlay(void)
{
	return mState == STATE::PLAY;
}

bool Player::IsWarpMove(void)
{
	return mState == STATE::WARP_MOVE;
}

void Player::StartWarp(float time, Quaternion goalRot, VECTOR goalPos)
{
	mTimeWarp = time;
	mStepWarp = time; 
	mWarpQua = goalRot;
	mWarpReservePos = goalPos; 
	mPreWarpName = mGravityManager->GetActivePlanet()->GetName(); 
	ChangeState(STATE::WARP_RESERVE);
}

void Player::Collision(void)
{
	mMovedPos = VAdd(mTransform.pos, mMovePow);

	// �Փ�(�d��)
	CollisionGravity();

	CollisionCapsule();



	mMoveDiff = VSub(mMovedPos, mTransform.pos);
	mTransform.pos = mMovedPos;
}

void Player::CollisionGravity(void)
{
	VECTOR dirGravity = mGravityManager->GetDirGravity();
	float gravityPow = mGravityManager->GetPower();
	VECTOR dirUpGravity = mGravityManager->GetDirUpGravity();
	mMovedPos = VAdd(mMovedPos, mJumpPow);
	mGravHitUp = VAdd(mMovedPos, VScale(dirUpGravity, gravityPow));
	mGravHitUp = VAdd(mGravHitUp, VScale(dirUpGravity, CHECK_HEGHT * 2.0f));
	mGravHitDown = VAdd(mMovedPos, VScale(dirGravity, CHECK_HEGHT));

	for (auto col : mColliders)
	{
		auto hit = MV1CollCheck_Line(col->mModelId, -1, mGravHitUp, mGravHitDown);
		if (hit.HitFlag)
		{
			// �X�Όv�Z�p�Փˏ��ۑ�
			mHitNormal = hit.Normal;
			mHitPos = hit.HitPosition;

			mMovedPos = VAdd(hit.HitPosition, VScale(dirUpGravity, 2.0f));
			mJumpPow = AsoUtility::VECTOR_ZERO;
			mStepJump = 0.0f;
			if (mIsJump)
			{
				// ���n���[�V����
				mAnimationController->Play(static_cast<int>(ANIM_TYPE::JUMP), false, 29.0f, 45.0f, false, true);
			}
			mIsJump = false;
		}
	}
}

void Player::CollisionCapsule(void)
{
	// �J�v�Z���̈ړ�
	Transform trans = Transform(&mTransform);
	trans.pos = mMovedPos;
	trans.Update();

	Capsule cap = mCapsule->Copy(&trans);

	for (const auto& col : mColliders)
	{
		auto hits = MV1CollCheck_Capsule(col->mModelId, -1, cap.GetPosTop(), cap.GetPosDown(), cap.GetRadius());

		for (int num = 0; num < hits.HitNum; num++)
		{
			auto hit = hits.Dim[num];
			for (int tryCnt = 0; tryCnt < 10; tryCnt++)
			{
				int pHit = HitCheck_Capsule_Triangle(
					cap.GetPosTop(), cap.GetPosDown(), cap.GetRadius(),
					hit.Position[0], hit.Position[1], hit.Position[2]
				);
				if (pHit)
				{
					mMovedPos = VAdd(mMovedPos, VScale(hit.Normal, 1.0f));
					trans.pos = mMovedPos;
					trans.Update();
					cap = mCapsule->Copy(&trans);
					continue;
				}

				break;
			}
		}
		MV1CollResultPolyDimTerminate(hits);
	}

}

void Player::EffectFootSmoke(void)
{
	int playHandle = -1;

	float len = AsoUtility::SqrMagnitude(mMoveDiff);

	mStepFootSmoke += 1.0f;

	if (fmodf(mStepFootSmoke, 15.0f) == 0.0f && len > 1.0f && !mIsJump)
	{
		playHandle = PlayEffekseer3DEffect(mEffectSmoke);
		float scale = 5.0f;
		SetScalePlayingEffekseer3DEffect(playHandle, scale, scale, scale);
		SetPosPlayingEffekseer3DEffect(playHandle, mTransform.pos.x, mTransform.pos.y, mTransform.pos.z);
	}
}

void Player::EffectWarpOrbit(void)
{
	// �G�t�F�N�g�Đ�
	mHandleWarpOrbitL = PlayEffekseer3DEffect(mEffectWarpOrbit);
	mHandleWarpOrbitR = PlayEffekseer3DEffect(mEffectWarpOrbit);
	// �傫��
	SetScalePlayingEffekseer3DEffect(mHandleWarpOrbitL, 10.0f, 10.0f, 10.0f);
	SetScalePlayingEffekseer3DEffect(mHandleWarpOrbitR, 10.0f, 10.0f, 10.0f);
	// �G�t�F�N�g�̈ʒu
	SyncWarpOrbitPos();
	// �G�t�F�N�g�̉�]
	VECTOR euler = mTransform.quaRot.ToEuler();
	SetRotationPlayingEffekseer3DEffect(mHandleWarpOrbitL, euler.x, euler.y, euler.z);
	SetRotationPlayingEffekseer3DEffect(mHandleWarpOrbitR, euler.x, euler.y, euler.z);
}

void Player::SyncWarpOrbitPos(void)
{
	VECTOR pos; pos = MV1GetFramePosition(mTransform.modelId, mFrameLeftHand);
	SetPosPlayingEffekseer3DEffect(mHandleWarpOrbitL, pos.x, pos.y, pos.z);
	pos = MV1GetFramePosition(mTransform.modelId, mFrameRightHand); 
	SetPosPlayingEffekseer3DEffect(mHandleWarpOrbitR, pos.x, pos.y, pos.z);
}

void Player::StopOrbitEffect(void)
{
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
		mJumpPow = AsoUtility::VECTOR_ZERO;
		// ���[�v�����J�n���̃v���C���[���
		mReserveStartQua = mTransform.quaRot;
		mReserveStartPos = mTransform.pos;
		mAnimationController->Play((int)Player::ANIM_TYPE::WARP_PAUSE);
		break;
	case Player::STATE::WARP_MOVE:
		// ���ʂ������Ă���͂��Ȃ̂Ń��Z�b�g
		mPlayerRotY = Quaternion();
		mGoalQuaRotY = Quaternion();
		mAnimationController->Play((int)Player::ANIM_TYPE::FLY);
		// �G�t�F�N�g�Đ�
		EffectWarpOrbit();
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

}

bool Player::isEndLanding(void)
{
	if (mAnimationController->GetPlayType() != static_cast<int>(ANIM_TYPE::JUMP))
	{
		return true;
	}
	if (mAnimationController->IsEnd())
	{
		return true;
	}
	return false;
}
