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

	// 状態
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

	// アニメーション種別
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

	// 移動処理
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

	// アニメーション
	AnimationController* mAnimationController;

	// 状態
	STATE mState;

	// 移動速度
	float mSpeed;

	// 移動方向
	VECTOR mMoveDir;

	// 移動量
	VECTOR mMovePow;

	// 移動後の座標
	VECTOR mMovedPos;

	VECTOR mJumpPow;

	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	// 回転
	Quaternion mPlayerRotY;
	Quaternion mGoalQuaRotY;
	float mRotateRotTime;

	// 状態遷移
	void ChangeState(STATE state);

};

