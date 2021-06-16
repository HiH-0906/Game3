#pragma once
#include "Object.h"

enum class PlayerColor
{
    BLUE,
    RED,
    WHITE
};

class Player :
    public Object
{
public:
    Player(const Vector2& pos, const double& speed, PlayerColor col, unsigned int inputType = 0);
    ~Player();
private:
    bool Init(const double& speed, unsigned int inputType)override final;
    void Update(const double& delta)override final;
    // @@@ ‰æ‘œ‚ÌƒL[Šl“¾‚Ég‚Á‚Ä‚é‚¾‚¯‚¾‚©‚ç‚¢‚ç‚È‚¢‚©‚à
    PlayerColor playerColor_;
};

