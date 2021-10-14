#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>
class SceneManager;
class Bullet;
class Unit
{
public:
	static constexpr float ANIM_SPEED = 30.0f;
	// ���X�ɊJ�X�����
	static constexpr float ROT_SPEED = 5.0f;
	static constexpr float ROT_SPEED_RAD = ROT_SPEED * (DX_PI_F / 180.0f);

	Unit(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngle(void);

private:
	SceneManager* mSceneMnager_;
	std::vector<std::shared_ptr<Bullet>> bulet_;

	// ���f���̃n���h��ID
	int modelID_;

	// ���f����Pos
	VECTOR pos_;

	// ���f���̊p�x
	VECTOR angle_;
	VECTOR angleLocal_;

	// Aniumation�p��HandleID
	int animWalk_;

	// Animation�̑��Đ�����
	float timeTotalAnimWalk_;

	// Animation�p�̍X�V�X�e�b�v
	float stepAnim_;
};

