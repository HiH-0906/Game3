#pragma once
#include "HomingShot.h"

struct HomingLaser :
    public HomingShot
{
    HomingLaser(char& isButton,Position2f& pos);
    void Update(const Position2f& enePos)override;
private:
    char& isButton_;
    Position2f& ownerPos_;
};

