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
    // @@@ 画像のキー獲得時に使ってるだけだからいらないかも
    PlayerColor playerColor_;
};

