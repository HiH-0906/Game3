#pragma once
#include "DxLib.h"
class SceneManager;

class Bullet
{
public:
	static constexpr float BULLET_SPEED = 10.0f;
	static constexpr float BULLET_RAD = 10.0f;

	Bullet(SceneManager* sceneManager);
	~Bullet();
	void Init(VECTOR pos, VECTOR angle);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	SceneManager* mSceneMnager_;

	// Pos
	VECTOR pos_;

	// ”ò‚ñ‚Å‚­Šp“x
	VECTOR angle_;
};

