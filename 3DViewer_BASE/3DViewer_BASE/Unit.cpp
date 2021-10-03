#include "Unit.h"
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"

Unit::Unit(SceneManager* manager)
{
	mSceneMnager_ = manager;
}

void Unit::Init(void)
{
	modelID_ = MV1LoadModel("Model/Hip Hop Dancing.mv1");
	pos_ = { 0.0f,0.0f,0.0f };
	angle_ = { 0.0f,0.0f,0.0f };
	angleLocal_ = { 0.0f,AsoUtility::Deg2Rad(180.0f),0.0f };

	// ���f���̍��W��ݒ�
	MV1SetPosition(modelID_, pos_);

	VECTOR angle = angle_;
	angle.x += angleLocal_.x;
	angle.y += angleLocal_.y;
	angle.z += angleLocal_.z;

	MV1SetRotationXYZ(modelID_, angle);

	// �Đ�����Animation�̐ݒ�
	animWalk_ = MV1AttachAnim(modelID_, 1);

	timeTotalAnimWalk_ = MV1GetAttachAnimTotalTime(modelID_, animWalk_);

	stepAnim_ = 0.0f;

	MV1SetAttachAnimTime(modelID_, animWalk_, stepAnim_);
}

void Unit::Update(void)
{
	// �o�ߎ��Ԃ��擾
	float deltaTime = mSceneMnager_->GetDeltaTime();

	// �V����Animation�Đ����Ԃ��Z�b�g
	stepAnim_ += (deltaTime * ANIM_SPEED);
	if (stepAnim_ > timeTotalAnimWalk_)
	{
		// Animation�̃��[�v����
		stepAnim_ = 0.0f;
	}
	MV1SetAttachAnimTime(modelID_, animWalk_, stepAnim_);


	float movePow = 5.0f;
	float rad = 0.0f;

	// ����L�[����
	bool isHitMove = false;

	// ��]�������p�x
	float rotRad = 0.0f;
	// �L�[�{�[�h����ŃJ�����ʒu�̈ړ�
	if (CheckHitKey(KEY_INPUT_S))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(180.0f);
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(0.0f);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(-90.0f);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(90.0f);
	}
	if (CheckHitKey(KEY_INPUT_Q))
	{
		pos_.y -= movePow;
	}
	if (CheckHitKey(KEY_INPUT_E))
	{
		pos_.y += movePow;
	}
	auto camera = mSceneMnager_->GetCamera();
	auto cAngle = camera->GetAngle().y;
	if (isHitMove)
	{
		// �L�����N�^�[�������Ă�������Ɉړ�����
		pos_.x += sinf(cAngle + rotRad) * movePow;
		pos_.z += cosf(cAngle + rotRad) * movePow;

		auto radUnitAngleY = AsoUtility::RadIn2PI(angle_.y);
		auto radMoveAngleY = AsoUtility::RadIn2PI(cAngle + rotRad);

		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

		if (abs(radUnitAngleY - radMoveAngleY) >= ROT_SPEED_RAD * 2.0f)
		{
			angle_.y += ROT_SPEED_RAD * aroundDir;
		}
		else
		{
			angle_.y = radMoveAngleY;
		}
	}
	

	// ���f���̍��W��ݒ�
	MV1SetPosition(modelID_, pos_);
	VECTOR angle = angle_;
	angle.x += angleLocal_.x;
	angle.y += angleLocal_.y;
	angle.z += angleLocal_.z;
	MV1SetRotationXYZ(modelID_, angle);
}

void Unit::Draw(void)
{
	// Model�̕`��
	MV1DrawModel(modelID_);
}

void Unit::Release(void)
{
	MV1DeleteModel(modelID_);
}

VECTOR Unit::GetPos(void)
{
	return pos_;
}

VECTOR Unit::GetAngle(void)
{
	return angle_;
}