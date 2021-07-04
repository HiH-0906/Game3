#include <DxLib.h>
#include "Object.h"
#include "../Mng/AnimationMng.h"

Object::Object(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType) :
    pos_(pos), size_(size), charID_(cID), speed_(speed)
{
    exRate_ = 1.0;
    angle_ = 0.0;
    reverseXFlag_ = false;
}


const Vector2Flt Object::GetPos(void) const
{
    return pos_;
}

