#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>
class SceneManager;
class Bullet;
class Unit
{
public:
	static constexpr float ANIM_SPEED = 30.0f;
	// 徐々に開店する量
	static constexpr float ROT_SPEED = 5.0f;
	static constexpr float ROT_SPEED_RAD = ROT_SPEED * (DX_PI_F / 180.0f);

	Unit(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);

private:
	SceneManager* mSceneMnager_;
	std::vector<std::shared_ptr<Bullet>> bulet_;

	// モデルのハンドルID
	int modelID_;

	// モデルのPos
	VECTOR pos_;

	// モデルの角度
	VECTOR angle_;
	VECTOR angleLocal_;

	// Aniumation用のHandleID
	int animWalk_;

	// Animationの総再生時間
	float timeTotalAnimWalk_;

	// Animation用の更新ステップ
	float stepAnim_;
};

