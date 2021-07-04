#pragma once
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "../common/Vector2.h"
#include "../Input/INPUT_ID.h"
#include "../Animation/Anim_ID.h"
#include "characterID.h"

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
	Object(const Vector2Flt& pos,const Vector2& size, const double& speed,const char_ID cID, unsigned int inputType = 0);
	virtual ~Object() = default;
	virtual bool Init(const double& speed, unsigned int inputType) = 0;
	virtual void Update(const double& delta,std::weak_ptr<MapData> mapData) = 0;
	virtual void Draw(const double& delta) = 0;

	const Vector2Flt GetPos(void)const;
	
private:
protected:

	Vector2Flt pos_;
	Vector2 size_;

	double speed_;

	char_ID charID_;

	bool reverseXFlag_;

	double exRate_;
	double angle_;
};

