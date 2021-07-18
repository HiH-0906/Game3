#pragma once
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <string>
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
	Object(const Vector2Flt& pos,const Vector2& size,const Object_ID oID);
	virtual ~Object() = default;
	virtual void Update(const double& delta,std::weak_ptr<MapData> mapData) = 0;
	virtual void Draw(const double& delta);

	bool Alive(void);

	const Vector2Flt GetPos(void)const;
	
private:
protected:

	Vector2Flt pos_;
	Vector2 size_;

	double delta_;

	Object_ID objectID_;

	std::string imageKey_;


	bool reverseXFlag_;
	bool isAlive_;

	double exRate_;
	double angle_;

	int animCnt_;
	int animMax_;
	int animFlam_;
};

