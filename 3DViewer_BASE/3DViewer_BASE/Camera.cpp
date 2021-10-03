#include "Camera.h"
#include "AsoUtility.h"

Camera::Camera(SceneManager* manager)
{
	pos_ = {};
	angle_ = {};
}

void Camera::Init(void)
{
	pos_ = { 0.0f,200.0,-500.0f };
	angle_= { AsoUtility::Deg2Rad(30.0f),0.0f,0.0f };
}

void Camera::Update(void)
{
	//float movePow = 5.0f;
	//float rad = 0.0f;
	//// �L�[�{�[�h����ŃJ�����ʒu�̈ړ�
	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	// �J�����̑O��
	//	rad = AsoUtility::Deg2Rad(180.0f);
	//	pos_.x += sinf(angle_.y + rad)* movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	// �J�����̌��
	//	rad = AsoUtility::Deg2Rad(0.0f);
	//	pos_.x += sinf(angle_.y + rad) * movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	// �J�����̍�
	//	rad = AsoUtility::Deg2Rad(-90.0f);
	//	pos_.x += sinf(angle_.y + rad) * movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	// �J�����̉E
	//	rad = AsoUtility::Deg2Rad(90.0f);
	//	pos_.x += sinf(angle_.y + rad) * movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_Q))
	//{
	//	pos_.y -= movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_E))
	//{
	//	pos_.y += movePow;
	//}
	// �L�[�{�[�h����ŃJ�����p�x�̈ړ�
	float rotatePow = 1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		angle_.y += AsoUtility::Deg2Rad(rotatePow);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		angle_.y -= AsoUtility::Deg2Rad(rotatePow);;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		angle_.x -= AsoUtility::Deg2Rad(rotatePow);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		angle_.x += AsoUtility::Deg2Rad(rotatePow);;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		angle_.z -= AsoUtility::Deg2Rad(rotatePow);
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD0))
	{
		angle_.z += AsoUtility::Deg2Rad(rotatePow);;
	}
}

void Camera::SetBeforeDraw(void)
{
	// �J�����ݒ�
	SetCameraPositionAndAngle(pos_, angle_.x, angle_.y, angle_.z);
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return pos_;
}

VECTOR Camera::GetAngle(void)
{
	return angle_;
}