#pragma once
#include "Object.h"

class Controller;
// コントローラーの入力を受け付け、アニメーションが遷移するクラス
// @@アイテムとかこの先実装されなかったら何のために生まれたのかわからないクラス
class Pawn :
    public Object
{
public:
    Pawn(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    virtual ~Pawn() = default;
    virtual void Draw(const double& delta)override;
private:
  
protected:
    // アニメーション変更
    void SetAnimation(Char_Anim_ID id);

    std::map<Char_Anim_ID, std::function<bool(Object& obj)>> update_;

    Char_Anim_ID animID_;
    int animCnt_;
    int animLoopCnt_;

    std::unique_ptr<Controller> controller_;
};

