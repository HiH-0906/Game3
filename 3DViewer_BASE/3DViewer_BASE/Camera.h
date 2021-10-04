#pragma once
#include "DxLib.h"
class SceneManager;
class Unit;
class Camera
{
public:
	// �J�����̍���
	static constexpr float HEIGHT = 300.0f;

	// �����_����J�����܂ł�XZ����
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
	// �J�����̈ʒu
	VECTOR pos_;
	// �J�����̊p�x
	VECTOR angle_;
	// �����_
	VECTOR targetPos_;
	// targetUnit
	Unit* target_;
};

