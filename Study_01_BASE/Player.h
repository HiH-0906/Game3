#pragma once
#include "Transform.h"
#include <map>
#include <functional>

class SceneManager;
class ParticleGenerator;
class SpriteAnimator;
class SpeechBalloon;

class Player
{
public:

	enum class PLAYER_STATE
	{
		NON,
		RUN,
		EXP,
		END
	};

	static constexpr float COLLISION_RADIUS = 20.0f;

	Player(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	Transform GetTransForm(void);

	void ProcessTurn(void);
	void Turn(float angle, VECTOR axis);

	void Dead(void);
	bool isAlive(void);
	bool isEnd(void);


	SpeechBalloon* speechBalloon_;
	
private:
	void ChengeState(PLAYER_STATE state);

	SceneManager* mSceneManager;
	ParticleGenerator* parGene_;
	SpriteAnimator* spriteAnimator_;

	// ÉÇÉfÉãêßå‰ÇÃäÓñ{èÓïÒ
	Transform mTransform;

	PLAYER_STATE state_;

	bool isAlive_;
};

