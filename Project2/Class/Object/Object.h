#pragma once
#include <memory>
#include <map>
#include <string>
#include "../common/Vector2.h"
#include "../Input/INPUT_ID.h"

class Controller;

enum class PlayerColor
{
	BLUE,
	RED,
	WHITE
};

class Object
{
public:
	Object(const Vector2& pos, const double& speed, PlayerColor col, unsigned int inputType = 0);
	virtual ~Object() = default;
	bool Init(const double& speed,unsigned int inputType);
	void Update(const double& delta);
	void Draw(const double& delta);
private:
	std::map<PlayerColor,std::string> id_;
	PlayerColor playerColor_;
protected:
	Vector2 pos_;
	std::map<INPUT_ID, Vector2Dbl> speed_;
	std::unique_ptr<Controller> controller_;
};

