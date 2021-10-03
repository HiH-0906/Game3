#pragma once
#include "DxLib.h"
class SceneManager;
class Camera
{
public:
	// �J�����̍���
	static constexpr float HEGHT = 200.0f;

	// �����_����J�����܂ł�XZ����
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
	// �J�����̈ʒu
	VECTOR pos_;
	// �J�����̊p�x
	VECTOR angle_;
};

