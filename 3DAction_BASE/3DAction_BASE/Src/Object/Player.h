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

	// 状態
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

	// 状態別更新ステップ
	void UpdateWarpReserve(void);
	void UpdateWarpMove(void);
	Capsule* GetCapsule(void);
	// 状態判定
	bool IsPlay(void);
	bool IsWarpMove(void);
	// ワープ開始
	void StartWarp(float time, Quaternion goalRot, VECTOR goalPos);

private:

	// 移動処理
	void ProcessMove(void);

	void ProcessJump(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	// 傾斜の計算
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

	// ワープ用
	float mTimeWarp;
	float mStepWarp;
	// ワープ準備完了時の情報
	Quaternion mWarpQua;
	VECTOR mWarpReservePos;
	// ワープ準備開始時のプレイヤー情報
	Quaternion mReserveStartQua;
	VECTOR mReserveStartPos;
	// ワープ前の惑星名
	Stage::NAME mPreWarpName;
	// 軌跡エフェクト
	int mEffectWarpOrbit;
	int mHandleWarpOrbitL;
	int mHandleWarpOrbitR;
	// モデルパーツのフレーム番号
	int mFrameLeftHand;
	int mFrameRightHand;

	// 軌跡エフェクト
	void EffectWarpOrbit(void);
	void SyncWarpOrbitPos(void);
	void StopOrbitEffect(void);

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

	VECTOR mSlopeDir;
	float mSlopeAngleDeg;
	VECTOR mSlopePow;
	VECTOR mHitNormal;
	VECTOR mHitPos;

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

