#include "Coin.h"
#include "AsoUtility.h"

Coin::Coin(SceneManager* manager)
{
}

void Coin::Init(void)
{
	mModelId = MV1LoadModel("model/Coin.mv1");
	mPos = { 0.0f,50.0f,0.0f };
	mAngles = { 0.0f,0.0f,0.0f };
	mAnglesLocal = { -DX_PI_F / 2.0f,0.0f,0.0f };
	// モデルの座標を設定

	MV1SetScale(mModelId, SCALE);

	VECTOR angle = VAdd(mAngles, mAnglesLocal);

	MV1SetRotationXYZ(mModelId, angle);

	MV1SetPosition(mModelId, mPos);

	mMatRotLocal = MGetIdent();
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.x));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.y));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.z));

	mType = TYPE::MATRIX;
}

void Coin::Update(void)
{
	mAngles.x += AsoUtility::Deg2RadF(1.0f);
	mAngles.y += AsoUtility::Deg2RadF(1.0f);
	mAngles.z += AsoUtility::Deg2RadF(0.0f);

	switch (mType)
	{
	case TYPE::VECTOR:
		SetModelVector();
		break;
	case TYPE::MATRIX:
		SetModelMatrix();
		break;
	default:
		break;
	}
}

void Coin::Draw(void)
{
	MV1DrawModel(mModelId);
	DrawDirection();
}

void Coin::Release(void)
{
}

void Coin::SetModelVector(void)
{

	VECTOR angle = VAdd(mAngles, mAnglesLocal);


	MV1SetRotationXYZ(mModelId, angle);
}

void Coin::SetModelMatrix(void)
{
	mMatScl = MGetScale(SCALE);
	
	mMatRot = MGetIdent();

	mMatRot = MMult(mMatRot, MGetRotX(mAngles.x));
	mMatRot = MMult(mMatRot, MGetRotY(mAngles.y));
	mMatRot = MMult(mMatRot, MGetRotZ(mAngles.z));

	mMatTrn = MGetTranslate(mPos);

	MATRIX mat = MGetIdent();
	mat = MMult(mat, mMatScl);

	MATRIX rot = MGetIdent();
	rot = MMult(rot, mMatRotLocal);
	rot = MMult(rot, mMatRot);
	rot = MMult(rot, mMatTrn);

	mat = MMult(mat, rot);

	MV1SetMatrix(mModelId,mat);

}

void Coin::DrawDirection(void)
{
	MATRIX mat = MGetIdent();
	switch (mType)
	{
	case TYPE::VECTOR:
		
		break;
	case TYPE::MATRIX:
		mat = mMatRot;
		break;
	default:
		break;
	}
	// 前方方向
	VECTOR foward = VNorm(VTransform({ 0.0f,0.0f,1.0f }, mat));
	// 前方方向
	VECTOR right = VNorm(VTransform({ 0.0f,1.0f,0.0f }, mat));
	// 前方方向
	VECTOR left = VNorm(VTransform({ 1.0f,0.0f,0.0f }, mat));

	VECTOR dir;
	VECTOR start;
	VECTOR end;
	float len = 30.0f;
	float size = 2.0f;

	dir = foward;
	start = VAdd(mPos, VScale(dir, -len));
	end = VAdd(mPos, VScale(dir, len));

	DrawLine3D(start, end, 0x0000ff);
	DrawSphere3D(end, size, 16, 0x0000ff, 0x0000ff, true);

	foward = VNorm(VTransform({ 0.0f,1.0f,0.0f }, mat));

	dir = right;
	start = VAdd(mPos, VScale(dir, -len));
	end = VAdd(mPos, VScale(dir, len));

	DrawLine3D(start, end, 0x00ff00);
	DrawSphere3D(end, size, 16, 0x00ff00, 0x00ff00, true);

	foward = VNorm(VTransform({ 1.0f,0.0f,0.0f }, mat));

	dir = left;
	start = VAdd(mPos, VScale(dir, -len));
	end = VAdd(mPos, VScale(dir, len));

	DrawLine3D(start, end, 0xff0000);
	DrawSphere3D(end, size, 16, 0xff0000, 0xff0000, true);
}
