#pragma once
#include "SceneBase.h"
class SceneManager;
class Stage;
class Unit;
class Enemy;
class RotateBall;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawDebug(void);
	void Release(void) override;

private:
	Stage* stage_;
	Unit* unit_;
	Enemy* enemy_;
	RotateBall* ball_;
};
