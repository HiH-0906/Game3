#pragma once
#include <array>
#include <list>
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
}

class Controller;
class Raycast;
class Bullet;

constexpr size_t BUF_NUM_MAX = 30;

// コントローラーの入力を受け付け、アニメーションが遷移するクラス
// @@アイテムとかこの先実装されなかったら何のために生まれたのかわからないクラス
class Pawn :
    public Object
{
public:
    Pawn(const Vector2Flt& pos, const Vector2& size,const Object_ID oID, unsigned int inputType = 0);
    virtual ~Pawn() = default;
    virtual void Draw(const double& delta)override;
private:
  
protected:
    // アニメーション変更
    void SetAnimation(Char_Anim_ID id);
    void UpdateInputBuf(void);

    std::map<Char_Anim_ID, std::function<bool(Object& obj)>> update_;

    Char_Anim_ID animID_;
    int animCnt_;
    int animLoopCnt_;

    float defJunpPower_;
    float yaddPower_;

    std::unique_ptr<Controller> controller_;
    std::unique_ptr<Raycast> raycast_;
    std::unique_ptr<Bullet> bullet_;
    std::weak_ptr<MapData> mapData_;

    std::list<std::pair<INPUT_ID, unsigned int>> commandList_;
    // @@とりあえず保存
    std::array<std::map<INPUT_ID, bool>, BUF_NUM_MAX> inputBuf_;
    unsigned int nowBufCnt_;

    std::unique_ptr<state::ModuleNode> moduleNode_;

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
};

