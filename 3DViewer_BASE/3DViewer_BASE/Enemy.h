#pragma once
#include "DxLib.h"
class SceneManager;
class Unit;

class Enemy
{
public:
	static constexpr float VIEW_RENGE = 300.0f;
	static constexpr float VIEW_ANGLE = 30.0f * (DX_PI_F / 180.0f);
	// ���X�ɊJ�X�����
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

	// ���f���̃n���h��ID
	int modelID_;

	bool mIsNotice;

	// ���f����Pos
	VECTOR pos_;

	// ���f���̊p�x
	VECTOR angle_;
	VECTOR angleLocal_;

};

