#pragma once
#include <DxLib.h>
#include "Common/Transform.h"
class SceneManager;
class ResourceManager;
class GravityManager;
class AnimationController;
class Capsule;
class Collider;

class Player
{

public:

	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_RUN = SPEED_MOVE * 2.0f;

	static constexpr double TIME_ROT = 1.0;

	static constexpr float CHECK_HEGHT = 20.0f;

	// ���
	enum class STATE
	{
		NONE,
		PLAY,
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
	void Init(void);
	void InitAnimation(void);
	void Update(void);
	void UpdatePlay(void);
	void Draw(void);
	void DrawDebug(void);
	void Release(void);

	Transform* GetTransform(void);

	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	// �ړ�����
	void ProcessMove(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	void CalcGravityPow(void);


	void Collision(void);
	void CollisionGravity(void);

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

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

	VECTOR mJumpPow;

	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	// ��]
	Quaternion mPlayerRotY;
	Quaternion mGoalQuaRotY;
	float mRotateRotTime;

	// ��ԑJ��
	void ChangeState(STATE state);

};

