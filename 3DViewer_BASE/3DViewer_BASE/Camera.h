#pragma once
#include "DxLib.h"
class SceneManager;
class Camera
{
public:
	// カメラの高さ
	static constexpr float HEGHT = 200.0f;

	// 注視点からカメラまでのXZ距離
	static constexpr float DIS_TAGET_TO_CAMERA = 500.0f;

	Camera(SceneManager* manager);
	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);

private:
	// カメラの位置
	VECTOR pos_;
	// カメラの角度
	VECTOR angle_;
};

