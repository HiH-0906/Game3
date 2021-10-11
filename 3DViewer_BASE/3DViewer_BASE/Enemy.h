#pragma once
#include "DxLib.h"
class SceneManager;
class Unit;

class Enemy
{
public:
	static constexpr float VIEW_RENGE = 300.0f;
	static constexpr float VIEW_ANGLE = 30.0f * (DX_PI_F / 180.0f);
	// 徐々に開店する量
	static constexpr float ROT_SPEED = 5.0f;
	static constexpr float ROT_SPEED_RAD = ROT_SPEED * (DX_PI_F / 180.0f);

	Enemy(SceneManager* manager);
	void Init(void);
	void Update(Unit* unit);
	void Draw(void);
	void Release(void);


	VECTOR GetPos(void);
	VECTOR GetAngle(void);

private:
	SceneManager* mSceneMnager_;

	// モデルのハンドルID
	int modelID_;

	bool mIsNotice;

	// モデルのPos
	VECTOR pos_;

	// モデルの角度
	VECTOR angle_;
	VECTOR angleLocal_;

};

