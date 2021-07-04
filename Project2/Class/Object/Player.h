#pragma once
#include "Pawn.h"
#include "characterID.h"

enum class PlayerColor
{
    BLUE,
    RED,
    WHITE
};

class Raycast;

class Player :
    public Pawn
{
public:
    Player(const Vector2Flt& pos,const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    ~Player();
private:
    bool Init(const double& speed, unsigned int inputType)override final;
    void Update(const double& delta, std::weak_ptr<MapData> mapData)override final;

    float defJunpPower_;
    float yaddPower_;

    std::unique_ptr<Raycast> raycast_;
};

