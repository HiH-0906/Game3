#pragma once
#include <memory>
#include <vector>
#include <map>
#include "../common/Vector2.h"
#include "../Input/INPUT_ID.h"
#include "../Animation/Anim_ID.h"
#include "characterID.h"

class Controller;
class MapData;

enum class DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX,
};

class Object
{
public:
	Object(const Vector2& pos,const Vector2& size, const double& speed,const char_ID cID, unsigned int inputType = 0);
	virtual ~Object() = default;
	virtual bool Init(const double& speed, unsigned int inputType) = 0;
	virtual void Update(const double& delta,std::weak_ptr<MapData> mapData) = 0;
	virtual void Draw(const double& delta);

	const Vector2 GetPos(void)const;
	
private:
protected:
	// �A�j���[�V�����ύX
	void SetAnimation(Anim_ID id);

	Vector2 pos_;
	Vector2 size_;

	double speed_;
	std::map<DIR, std::vector<Vector2>> collisionPos_;

	std::unique_ptr<Controller> controller_;

	// �A�j���[�V�����֘A�ϐ�
	// @@Object������g�����Ƃ������Ȃ��̂Ȃ�AnimationMng�����ł����������ʓrObject�ԍ����邯��
	Anim_ID animID_;
	char_ID charID_;
	DIR dir_;
	int animCnt_;
	int animLoopCnt_;

	bool reverseXFlag_;

	double exRate_;
	double angle_;
};

