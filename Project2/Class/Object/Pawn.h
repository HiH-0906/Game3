#pragma once
#include "Object.h"
class Pawn :
    public Object
{
public:
    Pawn(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    virtual ~Pawn() = default;
private:
protected:
};

