#pragma once
#include "Object.h"

class PlayerUI;

class Egg :
    public Object
{
public:
    Egg(const Vector2Flt& pos, const Vector2& size, const Object_ID oID, TeamTag tag, InputType type,std::shared_ptr<PlayerUI> owner,std::list<std::shared_ptr<Object>>& list);
    ~Egg() = default;
    void SetActive(const double& time);
private:
    void Update(const double& delta, std::weak_ptr<MapData> mapData)override final;
    void InstancePlayer(void);
    bool isActive_;
    double time_;
    InputType type_;
    std::list<std::shared_ptr<Object>>& objList_;
    std::weak_ptr<PlayerUI> owner_;
};

