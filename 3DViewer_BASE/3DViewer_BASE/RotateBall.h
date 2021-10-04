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

	// ���f����Pos
	VECTOR pos_;

	// Animation�p�̍X�V�X�e�b�v
	float deltaTime_;
};

