#pragma once
#include "Object.h"
#include "characterID.h"

enum class PlayerColor
{
    BLUE,
    RED,
    WHITE
};

class Raycast;

class Player :
    public Object
{
public:
    Player(const Vector2& pos,const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    ~Player();
private:
    bool Init(const double& speed, unsigned int inputType)override final;
    void Update(const double& delta, std::weak_ptr<MapData> mapData)override final;

    bool isJunp_;

    std::unique_ptr<Raycast> raycast_;
};

