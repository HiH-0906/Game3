#pragma once
#include "Transform.h"

class SceneManager;
class Player;
class EventShot;

class BossShip
{
public:
	enum class BOSS_STATE
	{
		NON,
		EVENT,
		BATTLE,
		EXP,
		END,
	};
	BossShip(SceneManager* manager, Player* player);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	SceneManager* sceneManager_;
	Player* player_;
	EventShot* eventShot_;

	Transform transform_;

	float stepEvent_;


	BOSS_STATE state_;

	void ChengeState(BOSS_STATE state);
};

