#include <DxLib.h>
#include "Object.h"
#include "../Mng/ImageMng.h"
#include "../Input/Controller.h"
#include "../Input/KeyBoard.h"
#include "../Input/Pad.h"

Object::Object(const Vector2& pos, const double& speed,unsigned int inputType):
    pos_(pos)
{
}



void Object::Update(const double& delta)
{
    
}

void Object::Draw(const double& delta)
{
    DrawGraph(pos_.x, pos_.y, lpImageMng.GetID(key_)[0],true);
}

