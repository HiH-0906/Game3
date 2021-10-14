#include "Unit.h"
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"
#include "Bullet.h"

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
	for (const auto& bulet : bulet_)
	{
		bulet->Update();
	}
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
		auto bulet = std::make_shared<Bullet>(mSceneMnager_);
		auto pos = pos_;
		pos.y += 100.0f;
		bulet->Init(pos, angle_);
		bulet_.emplace_back(bulet);
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

		int aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

		if (abs(radUnitAngleY - radMoveAngleY) >= ROT_SPEED_RAD * 2.0f)
		{
			angle_.y += ROT_SPEED_RAD * static_cast<float>(aroundDir);
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
	for (const auto& bulet : bulet_)
	{
		bulet->Draw();
	}
	DrawSphere3D(pos_, 10, 16, 0x88ff88, 0x88ff88, true);
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
