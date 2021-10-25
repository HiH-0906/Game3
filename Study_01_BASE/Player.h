#pragma once
#include "Transform.h"

class SceneManager;

class Player
{
public:

	Player(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	Transform GetTransForm(void);

	void ProcessTurn(void);
	void Turn(float angle, VECTOR axis);
private:
	SceneManager* mSceneManager;

	// モデル制御の基本情報
	Transform mTransform;
};

