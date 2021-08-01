#pragma once
#include "Pawn.h"
#include "characterID.h"
#include "../XML/RapidXml/rapidxml.hpp"
#include "../XML/RapidXml/rapidxml_utils.hpp"



class Player :
    public Pawn
{
public:
    Player(const Vector2Flt& pos,const Vector2& size,const Object_ID oID,int hp, TeamTag tag, std::shared_ptr<PlayerUI> ui, unsigned int reviveCnt,  InputType inputType = InputType::KEYBOARD);
    ~Player();
private:
    bool Init(InputType inputType);
    void Update(const double& delta, std::weak_ptr<MapData> mapData)override final;

    void InitAttackFunc(void)override final;

    std::vector<char> stateVec_;
    rapidxml::xml_node<>* stateNode_;
    rapidxml::xml_document<> stateDoc_;
    bool isRevive_;
    double deadTime_;
};

