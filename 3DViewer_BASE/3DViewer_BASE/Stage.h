#pragma once
#include "DxLib.h"
class SceneManager;
class Stage
{

public:
	
	Stage(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	
	SceneManager* mSceneMnager_;

	// モデルのハンドルID
	int modelID_;

	// モデルのPos
	VECTOR pos_;
};

