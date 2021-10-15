#include <cmath>
#include "Enemy.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Unit.h"

Enemy::Enemy(SceneManager* manager)
{
	mSceneMnager_ = manager;
	mIsNotice = false;
}

void Enemy::Init(void)
{
	modelID_ = MV1LoadModel("Model/Human.mv1");
	pos_ = { 200.0f,0.0f,100.0f };
	angle_ = { 0.0f,AsoUtility::Deg2Rad(225.0f),0.0f };
	angleLocal_ = { 0.0f,AsoUtility::Deg2Rad(180.0f),0.0f };

	// ƒ‚ƒfƒ‹‚ÌÀ•W‚ðÝ’è
	MV1SetPosition(modelID_, pos_);

	VECTOR angle = angle_;
	angle.x += angleLocal_.x;
	angle.y += angleLocal_.y;
	angle.z += angleLocal_.z;

	MV1SetRotationXYZ(modelID_, angle);
}

void Enemy::Update(Unit* unit)
{
	mIsNotice = false; 

	const auto uPos = unit->GetPos();
	const auto uAngle = unit->GetAngle();

	auto diffPos = VSub(uPos, pos_);

	float diffLength = diffPos.x * diffPos.x + diffPos.z * diffPos.z;

	if (diffLength <= VIEW_RENGE * VIEW_RENGE)
	{
		float diffAngle = std::atan2(diffPos.x, diffPos.z);

		diffAngle = AsoUtility::RadIn2PI(diffAngle - angle_.y);

		if (diffAngle <= VIEW_ANGLE || diffAngle >= DX_TWO_PI - VIEW_ANGLE)
		{
			mIsNotice = true;
		}
	}
}

void Enemy::Draw(void)
{
	if (mIsNotice)
	{
		MV1SetMaterialDifColor(modelID_, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		MV1SetMaterialDifColor(modelID_, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}

	MV1DrawModel(modelID_);

	VECTOR vertex1 = { sin(angle_.y) * VIEW_RENGE,0.0f, cos(angle_.y) * VIEW_RENGE };

	VECTOR vertex2 = { sin(angle_.y - VIEW_ANGLE) * VIEW_RENGE,0.0f, cos(angle_.y - VIEW_ANGLE) * VIEW_RENGE };
	VECTOR vertex3 = { sin(angle_.y + VIEW_ANGLE) * VIEW_RENGE,0.0f, cos(angle_.y + VIEW_ANGLE) * VIEW_RENGE };

	vertex1 = VAdd(pos_, vertex1);
	vertex2 = VAdd(pos_, vertex2);
	vertex3 = VAdd(pos_, vertex3);

	DrawTriangle3D(pos_, vertex2, vertex1, 0xffffff, true);
	DrawTriangle3D(pos_, vertex1, vertex3, 0xffffff, true);
	DrawLine3D(pos_, vertex1,0);
}

void Enemy::Release(void)
{
	MV1DeleteModel(modelID_);
}

VECTOR Enemy::GetPos(void)
{
	return pos_;
}

VECTOR Enemy::GetAngle(void)
{
	return angle_;
}
