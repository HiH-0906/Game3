#pragma once
#include "Pawn.h"
#include "characterID.h"
#include "../XML/RapidXml/rapidxml.hpp"
#include "../XML/RapidXml/rapidxml_utils.hpp"



class Player :
    public Pawn
{
public:
    Player(const Vector2Flt& pos,const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    ~Player();
private:
    bool Init(const double& speed, unsigned int inputType)override final;
    void Update(const double& delta, std::weak_ptr<MapData> mapData)override final;

    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
};

