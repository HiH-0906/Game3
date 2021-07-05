#pragma once
#include "Pawn.h"
#include "characterID.h"
#include "state/state.h"

enum class PlayerColor
{
    BLUE,
    RED,
    WHITE
};


namespace rapidxml
{
    template<class Ch = char>
    class xml_node;
}


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

    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;

    state::ModuleNode moduleNode_;
};

