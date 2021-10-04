#include "Camera.h"
#include "AsoUtility.h"
#include "Unit.h"

Camera::Camera(SceneManager* manager)
{
	pos_ = {};
	angle_ = {};
}

void Camera::Init(void)
{
	pos_ = { 0.0f,HEIGHT,-DIS_TAGET_TO_CAMERA };
	angle_= { AsoUtility::Deg2Rad(30.0f),0.0f,0.0f };
}

void Camera::Update(void)
{
	//float movePow = 5.0f;
	//float rad = 0.0f;
	//// キーボード操作でカメラ位置の移動
	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	// カメラの前方
	//	rad = AsoUtility::Deg2Rad(180.0f);
	//	pos_.x += sinf(angle_.y + rad)* movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	// カメラの後方
	//	rad = AsoUtility::Deg2Rad(0.0f);
	//	pos_.x += sinf(angle_.y + rad) * movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	// カメラの左
	//	rad = AsoUtility::Deg2Rad(-90.0f);
	//	pos_.x += sinf(angle_.y + rad) * movePow;
	//	pos_.z += cosf(angle_.y + rad) * movePow;
	//}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	// カメラの右
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
	// キーボード操作でカメラ角度の移動
	float rotatePow = 1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		angle_.y += AsoUtility::Deg2Rad(rotatePow);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		angle_.y -= AsoUtility::Deg2Rad(rotatePow);;
	}
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	angle_.x -= AsoUtility::Deg2Rad(rotatePow);
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	angle_.x += AsoUtility::Deg2Rad(rotatePow);;
	//}
	//if (CheckHitKey(KEY_INPUT_NUMPAD1))
	//{
	//	angle_.z -= AsoUtility::Deg2Rad(rotatePow);
	//}
	//if (CheckHitKey(KEY_INPUT_NUMPAD0))
	//{
	//	angle_.z += AsoUtility::Deg2Rad(rotatePow);;
	//}
}

void Camera::SetBeforeDraw(void)
{
	if (target_ == nullptr)
	{
		// カメラ設定
		SetCameraPositionAndAngle(pos_, angle_.x, angle_.y, angle_.z);
	}
	else
	{

		// キャラクターの位置
		float dirX = sinf(angle_.y);
		float dirZ = cosf(angle_.y);

		VECTOR nVec = VNorm({ dirX,0.0f,dirZ });

		VECTOR movePow = VScale(nVec, DIS_TAGET_TO_UNIT);

		targetPos_ = VAdd(target_->GetPos(), movePow);


		//targetPos_ = target_->GetPos();
		// カメラの位置
		float RevRad = AsoUtility::Deg2Rad(180.f);
		dirX = sinf(angle_.y + RevRad);
		dirZ = cosf(angle_.y + RevRad);

		nVec = VNorm({ dirX,0.0f,dirZ });

		movePow = VScale(nVec, DIS_TAGET_TO_CAMERA);
		
		movePow.y = HEIGHT;

		pos_ = VAdd(targetPos_, movePow);

		SetCameraPositionAndTargetAndUpVec(pos_, targetPos_, { 0.0f,1.0f,0.0f });
	}
}

void Camera::Draw(void)
{
}

void Camera::Release(void)
{
}

void Camera::SetTarget(Unit* target)
{
	target_ = target;
}

VECTOR Camera::GetPos(void)
{
	return pos_;
}

VECTOR Camera::GetAngle(void)
{
	return angle_;
}

VECTOR Camera::GetTargetPos(void)
{
	return targetPos_;
}
