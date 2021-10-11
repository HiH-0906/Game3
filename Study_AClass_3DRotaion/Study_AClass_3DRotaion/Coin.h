#pragma once
#include "DxLib.h"
class SceneManager;

class Coin
{

public:

	static constexpr float SIZE = 15.0f;
	static constexpr VECTOR SCALE = { SIZE,SIZE,SIZE };

	enum class TYPE
	{
		VECTOR,
		MATRIX,
		QUATERNION,
	};

	Coin(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SetModelVector(void);
	void SetModelMatrix(void);

	/// <summary>
	/// 各角度の線を描画する
	/// </summary>
	void DrawDirection(void);

private:

	// モデルID
	int mModelId;

	TYPE mType;

	// 座標
	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;

	MATRIX mMatScl;
	MATRIX mMatRot;
	MATRIX mMatTrn;

	MATRIX mMatRotLocal;
};

