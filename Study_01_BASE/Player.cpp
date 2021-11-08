#include "Player.h"
#include "SceneManager.h"
#include "ParticleGenerator.h"
#include "AsoUtility.h"


namespace
{
	constexpr float MOVE_POW = 10.0f;
	constexpr float MOVE_ROT_DEG_X = 1.0f;
	constexpr float MOVE_ROT_DEG_Y = 1.0f;
}

Player::Player(SceneManager* manager)
{
	mSceneManager = manager;
	parGene_ = nullptr;
}

void Player::Init(void)
{
	mTransform.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));
	float scale = 10.0;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;

	mTransform.Update();

	parGene_ = new ParticleGenerator(mSceneManager, mTransform.pos, 20.0f);
	parGene_->Init();
}

void Player::Update(void)
{
	ProcessTurn();
	VECTOR forward = VNorm(mTransform.GetForward());

	VECTOR moveVec = VScale(forward, MOVE_POW);

	mTransform.pos = VAdd(mTransform.pos, moveVec);

	mTransform.Update();
	parGene_->SetPos(VAdd(mTransform.pos, VScale(mTransform.GetForward(), 10.0f)));

	Quaternion rot = mTransform.rot;
	Quaternion axis;
	axis = Quaternion::AngleAxis(AsoUtility::Deg2RadF(180.0f), AsoUtility::AXIS_Y);
	rot = rot.Mult(axis);
	axis = Quaternion::AngleAxis(AsoUtility::Deg2RadF(90.0f), AsoUtility::AXIS_X);
	rot = rot.Mult(axis);
	parGene_->SetRot(rot);
	parGene_->Update();
}

void Player::Draw(void)
{
	parGene_->Draw();
	MV1DrawModel(mTransform.modelId);
}

void Player::Release(void)
{
	parGene_->Release();
	delete parGene_;
}

Transform Player::GetTransForm(void)
{
	return mTransform;
}

void Player::ProcessTurn(void)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		Turn(MOVE_ROT_DEG_X, AsoUtility::AXIS_Y);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		Turn(-MOVE_ROT_DEG_X, AsoUtility::AXIS_Y);
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		Turn(-MOVE_ROT_DEG_Y, AsoUtility::AXIS_X);
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		Turn(MOVE_ROT_DEG_Y, AsoUtility::AXIS_X);
	}
}

void Player::Turn(float angle, VECTOR axis)
{
	double rad = AsoUtility::Deg2RadD(angle);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	mTransform.quaRot = mTransform.quaRot.Mult(tmpQ);
}
