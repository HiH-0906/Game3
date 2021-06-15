#pragma once
#include <vector>
#include "BaseScene.h"

class MapData;
class Object;

class GameScene :
    public BaseScene
{
public:
    GameScene();
    ~GameScene();   
private:
    bool Init(void)override final;

    const SceneID GetSceneID(void)const override final;

    std::unique_ptr<BaseScene> Update(const double& delta, std::unique_ptr<BaseScene> ownScene)override final;

    void DrawOwnScreen(const double& delta)override final;

    std::unique_ptr<MapData> mapData_;
    std::vector<std::unique_ptr<Object>> objList_;
};

