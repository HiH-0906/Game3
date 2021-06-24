#pragma once
#include <memory>
#include <map>
#include "../common/Vector2.h"
#include "../Input/INPUT_ID.h"
#include "../Animation/Anim_ID.h"
#include "characterID.h"

class Controller;


class Object
{
public:
	Object(const Vector2& pos, const double& speed,const char_ID cID, unsigned int inputType = 0);
	virtual ~Object() = default;
	virtual bool Init(const double& speed, unsigned int inputType) = 0;
	virtual void Update(const double& delta) = 0;
	virtual void Draw(const double& delta);
	
private:
protected:
	// アニメーション変更
	void SetAnimation(Anim_ID id);

	Vector2 pos_;
	std::map<INPUT_ID, Vector2Dbl> speed_;
	std::unique_ptr<Controller> controller_;

	// アニメーション関連変数
	// @@Object側から使うことがもしないのならAnimationMng持ちでもいいかも別途Object番号いるけど
	Anim_ID animID_;
	char_ID charID_;
	int animCnt_;
	int animLoopCnt_;

	bool reverseXFlag_;

	double exRate_;
	double angle_;
};

