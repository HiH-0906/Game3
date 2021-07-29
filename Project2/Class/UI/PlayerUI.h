#pragma once
#include <list>
#include <memory>
#include "UIBase.h"
#include "../Object/TeamTag.h"

class Pawn;
class Object;

class PlayerUI :
    public UIBase,public std::enable_shared_from_this<PlayerUI>
{
public:
	PlayerUI(const Vector2& pos, const Vector2& scrSize,const TeamTag& tag, std::list<std::shared_ptr<Object>>& list);
	virtual ~PlayerUI()=default;
	void SetRevive(const double& time);
	void SetOwner(std::weak_ptr<Pawn> owner);
	void InstancePlayer(void);
	virtual void UpDate(const double& delta);
	/// <summary>
	/// 自身のスクリーンへの描画
	/// </summary>
	virtual void UIDraw(const double& delta)override;
private:

	std::list<std::shared_ptr<Object>>& objList_;

	int mask_;
	int col_;
	std::weak_ptr<Pawn> owner_;
};

