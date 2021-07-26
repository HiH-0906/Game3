#pragma once
#include <array>
#include <list>
#include <string>
#include <map>
#include <functional>
#include "../Input/INPUT_ID.h"
#include "Object.h"

namespace state
{
    struct Move;
    struct CheckKeyTrg;
    struct CheckKeyNow;
    struct SetAnimation;
    struct CheckStopPos;
    struct CheckMoveRay;
    struct CheckGuround;
    struct ModuleNode;
    struct Fall;
    struct Jump;
    struct CheckAnim;
    struct Attack;
    struct CheckCmmand;
    struct CheckAlive;
    struct Revive;
    struct SetReviveTime;
}

class Controller;
class Raycast;
class Bullet;
class UIBase;

struct CommandData
{
    std::string name_;
    struct command
    {
        CMD_ID id;
        int time;
    };
    std::list<command> command_;
    unsigned int allTime_ = 0;
};


// コントローラーの入力を受け付け、アニメーションが遷移するクラス
// @@アイテムとかこの先実装されなかったら何のために生まれたのかわからないクラス
class Pawn :
    public Object
{
public:
    Pawn(const Vector2Flt& pos, const Vector2& size,const Object_ID oID,int hp, TeamTag tag, InputType inputType = InputType::KEYBOARD);
    virtual ~Pawn() = default;
    virtual void Draw(const double& delta)override;
    virtual void AddDamage(int damage)override;

private:
    virtual void InitAttackFunc(void) = 0;
protected:
    // アニメーション変更
    void SetAnimation(Char_Anim_ID id);

    std::map<Char_Anim_ID, std::function<bool(Object& obj)>> update_;

    Char_Anim_ID animID_;
    int animCnt_;
    int animLoopCnt_;

    int hp_;
    int reviveCnt_;

    float defJunpPower_;
    float yaddPower_;

    std::unique_ptr<Controller> controller_;
    std::unique_ptr<Raycast> raycast_;
    std::shared_ptr<Bullet> bullet_;
    std::weak_ptr<MapData> mapData_;
    std::shared_ptr<UIBase> ui_;

 

    std::list<CommandData> commandList_;

    std::unique_ptr<state::ModuleNode> moduleNode_;

    std::function<void(void)> attackFunc_;
    std::map<std::string, std::function<void(void)>> attackFuncMap_;

    static int PlayerUICnt_;

    friend state::Move;
    friend state::CheckKeyTrg;
    friend state::CheckKeyNow;
    friend state::SetAnimation;
    friend state::CheckStopPos;
    friend state::CheckMoveRay;
    friend state::CheckGuround;
    friend state::Fall;
    friend state::Jump;
    friend state::CheckAnim;
    friend state::Attack;
    friend state::CheckCmmand;
    friend state::CheckAlive;
    friend state::Revive;
    friend state::SetReviveTime;
};

