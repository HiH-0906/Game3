#pragma once
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
}
class Controller;
class Raycast;

// �R���g���[���[�̓��͂��󂯕t���A�A�j���[�V�������J�ڂ���N���X
// @@�A�C�e���Ƃ����̐��������Ȃ������牽�̂��߂ɐ��܂ꂽ�̂��킩��Ȃ��N���X
class Pawn :
    public Object
{
public:
    Pawn(const Vector2Flt& pos, const Vector2& size, const double& speed, const char_ID cID, unsigned int inputType = 0);
    virtual ~Pawn() = default;
    virtual void Draw(const double& delta)override;
private:
  
protected:
    // �A�j���[�V�����ύX
    void SetAnimation(Char_Anim_ID id);

    std::map<Char_Anim_ID, std::function<bool(Object& obj)>> update_;

    Char_Anim_ID animID_;
    int animCnt_;
    int animLoopCnt_;

    std::unique_ptr<Controller> controller_;
    std::map<std::string, INPUT_ID> input_IDkey_;
    std::unique_ptr<Raycast> raycast_;
    std::weak_ptr<MapData> mapData_;


    friend state::Move;
    friend state::CheckKeyTrg;
    friend state::CheckKeyNow;
    friend state::SetAnimation;
    friend state::CheckStopPos;
    friend state::CheckMoveRay;
    friend state::CheckGuround;
};

