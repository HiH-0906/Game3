#pragma once
#include "DxLib.h"
class SceneManager;
class Unit;
class Camera
{
public:
	// カメラの高さ
	static constexpr float HEIGHT = 300.0f;

	// 注視点からカメラまでのXZ距離
	static constexpr float DIS_TAGET_TO_CAMERA = 800.0f;

	static constexpr float DIS_TAGET_TO_UNIT = 300.0f;

	Camera(SceneManager* manager);
	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	void SetTarget(Unit* target);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);
	VECTOR GetTargetPos(void);

private:
	// カメラの位置
	VECTOR pos_;
	// カメラの角度
	VECTOR angle_;
	// 注視点
	VECTOR targetPos_;
	// targetUnit
	Unit* target_;
};

