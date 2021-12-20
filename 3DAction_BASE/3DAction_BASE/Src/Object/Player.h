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

	static constexpr float POW_JUMP = 35.0f;

	static constexpr float TIME_JUMP_IN = 0.5f;

	static constexpr double TIME_ROT = 1.0;

	static constexpr float CHECK_HEGHT = 10.0f;

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
	void DrawShadow(void);
	void DrawDebug(void);

	void Release(void);

	Transform* GetTransform(void);

	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	// 移動処理
	void ProcessMove(void);

	void ProcessJump(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	void CalcGravityPow(void);


	void Collision(void);
	void CollisionGravity(void);

	void CollisionCapsule(void);

	void EffectFootSmoke(void);

	// 状態遷移
	void ChangeState(STATE state);

	bool isEndLanding(void);

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	Capsule* mCapsule;

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

	// ジャンプ量
	VECTOR mJumpPow;

	// ジャンプ判定
	bool mIsJump;

	// ジャンプ入力受付時間
	float mStepJump;

	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	// 回転
	Quaternion mPlayerRotY;
	Quaternion mGoalQuaRotY;
	float mRotateRotTime;

	// 丸影画像ハンドル
	int mImageShadow;

	// 足煙
	int mEffectSmoke;
	float mStepFootSmoke;

	VECTOR mMoveDiff;

};

