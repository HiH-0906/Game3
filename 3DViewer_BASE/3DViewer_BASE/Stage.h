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

	// ���f���̃n���h��ID
	int modelID_;

	// ���f����Pos
	VECTOR pos_;
};

