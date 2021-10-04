#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class RotateBall
{
public:
	RotateBall(SceneManager* manager,Unit* unit);
	void Init(void);
	void Update(void);
	void Draw(void);

	VECTOR GetPos(void);

private:
	SceneManager* mSceneMnager_;
	Unit* unit_;

	// モデルのPos
	VECTOR pos_;

	// Animation用の更新ステップ
	float deltaTime_;
};

