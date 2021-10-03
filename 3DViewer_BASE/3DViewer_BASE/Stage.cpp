#include "Stage.h"
#include "SceneManager.h"

Stage::Stage(SceneManager* manager)
{
	mSceneMnager_ = manager;
}

void Stage::Init(void)
{
	modelID_ = MV1LoadModel("Model/Stage.mv1");
	pos_ = { 0.0f,-100.0f,0.0f };
	// モデルの座標を設定
	MV1SetPosition(modelID_, pos_);
}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{

	// XYZのグリッド線描画
	float Line = 500.0f;
	float Width = 50.0f;
	for (float cnt = 0.0f; cnt <= (Line / Width) * 2.0f; cnt += 1.0f)
	{
		auto Grid = -Line + Width * cnt;
		// X
		DrawLine3D({ -Line,0.0f, Grid }, { Line,0.0f,Grid }, 0xff0000);
		// Z
		DrawLine3D({ Grid,0.0f,-Line }, { Grid,0.0f,Line }, 0x0000ff);
	}
	// Y
	DrawLine3D({ 0.0f,-Line,0.0f }, { 0.0f,Line,0.0f }, 0x00ff00);

	// Modelの描画
	MV1DrawModel(modelID_);
}

void Stage::Release(void)
{
	MV1DeleteModel(modelID_);
}
