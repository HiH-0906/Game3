#pragma once
#include <memory>
#include <map>
#include <string>
#include "../common/Vector2.h"
#include "../Input/INPUT_ID.h"

class Controller;


class Object
{
public:
	Object(const Vector2& pos, const double& speed, unsigned int inputType = 0);
	virtual ~Object() = default;
	virtual bool Init(const double& speed, unsigned int inputType) = 0;
	virtual void Update(const double& delta) = 0;
	virtual void Draw(const double& delta);
private:
protected:
	std::string key_;
	Vector2 pos_;
	std::map<INPUT_ID, Vector2Dbl> speed_;
	std::unique_ptr<Controller> controller_;
};

