#pragma once
#include <vector>
#include <DxLib.h>
#include "Common/Transform.h"
#include "Stage.h"
class SceneManager;
class ResourceManager;
class GravityManager;
class AnimationController;
class Capsule;
class Collider;
class Bullet;

class Player
{

public:

	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_RUN = SPEED_MOVE * 2.0f;

	static constexpr float POW_JUMP = 35.0f;

	static constexpr float TIME_JUMP_IN = 0.5f;

	static constexpr double TIME_ROT = 1.0;

	static constexpr float CHECK_HEGHT = 10.0f;

	// ���
	enum class STATE
	{
		NONE,
		PLAY,
		TANK,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	// �A�j���[�V�������
	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		JUMP,
		WARP_PAUSE,
		FLY,
		FALLING,
		VICTORY
	};

	Player(SceneManager* manager);
	void Init(bool isTank = false);
	void TankModelInit(void);
	void InitAnimation(void);
	void Update(void);
	void UpdatePlay(void);
	void UpdateTank(void);

	void Draw(void);
	void DrawShadow(void);
	void DrawDebug(void);

	void Release(void);

	Transform* GetTransform(void);


	void AddCollider(Collider* collider);
	void ClearCollider(void);

	// ��ԕʍX�V�X�e�b�v
	void UpdateWarpReserve(void);
	void UpdateWarpMove(void);
	Capsule* GetCapsule(void);
	// ��Ԕ���
	bool IsPlay(void);
	bool IsWarpMove(void);
	// ���[�v�J�n
	void StartWarp(float time, Quaternion goalRot, VECTOR goalPos);

private:

	// �ړ�����
	void ProcessMove(void);

	void ProcessJump(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	// �X�΂̌v�Z
	void CalcSlope(void);

	void CalcGravityPow(void);


	void ProcessTank(void);
	void ProcessTankMove(void);
	void ProcessTankRotate(void);
	void ProcessTankBarrel(void);
	void ProcessTankShot(void);


	void Collision(void);
	void CollisionGravity(void);

	void CollisionCapsule(void);

	void EffectFootSmoke(void);

	// ���[�v�p
	float mTimeWarp;
	float mStepWarp;
	// ���[�v�����������̏��
	Quaternion mWarpQua;
	VECTOR mWarpReservePos;
	// ���[�v�����J�n���̃v���C���[���
	Quaternion mReserveStartQua;
	VECTOR mReserveStartPos;
	// ���[�v�O�̘f����
	Stage::NAME mPreWarpName;
	// �O�ՃG�t�F�N�g
	int mEffectWarpOrbit;
	int mHandleWarpOrbitL;
	int mHandleWarpOrbitR;
	// ���f���p�[�c�̃t���[���ԍ�
	int mFrameLeftHand;
	int mFrameRightHand;

	// �O�ՃG�t�F�N�g
	void EffectWarpOrbit(void);
	void SyncWarpOrbitPos(void);
	void StopOrbitEffect(void);

	// ��ԑJ��
	void ChangeState(STATE state);

	bool isEndLanding(void);

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	Capsule* mCapsule;

	// �A�j���[�V����
	AnimationController* mAnimationController;

	// ���
	STATE mState;

	// �ړ����x
	float mSpeed;

	// �ړ�����
	VECTOR mMoveDir;

	// �ړ���
	VECTOR mMovePow;

	// �ړ���̍��W
	VECTOR mMovedPos;

	// �W�����v��
	VECTOR mJumpPow;

	// �W�����v����
	bool mIsJump;

	// �W�����v���͎�t����
	float mStepJump;

	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	VECTOR mSlopeDir;
	float mSlopeAngleDeg;
	VECTOR mSlopePow;
	VECTOR mHitNormal;
	VECTOR mHitPos;

	// ��]
	Quaternion mPlayerRotY;
	Quaternion mGoalQuaRotY;
	float mRotateRotTime;

	// �ۉe�摜�n���h��
	int mImageShadow;

	// ����
	int mEffectSmoke;
	float mStepFootSmoke;

	VECTOR mMoveDiff;

	bool isTank_;

	Transform t_Body_;
	Transform t_Wheel_L_;
	Transform t_Wheel_R_;
	Transform t_Barrel_;

	Transform t_Parent_;

	float delta_;
	float waitTIme_;
	std::vector<Bullet*> bullet_;
};

