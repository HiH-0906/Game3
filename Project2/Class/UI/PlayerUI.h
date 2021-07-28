#pragma once
#include <list>
#include <memory>
#include "UIBase.h"
#include "../Object/TeamTag.h"

class Egg;

class PlayerUI :
    public UIBase
{
public:
	PlayerUI(const Vector2& pos, const Vector2& scrSize,const TeamTag& tag);
	virtual ~PlayerUI()=default;
	void SetList(const std::list<std::weak_ptr<Egg>>& eggList);
	void SetRevive(const double& time);
	virtual void UpDate(const double& delta);
	/// <summary>
	/// 自身のスクリーンへの描画
	/// </summary>
	virtual void UIDraw(const double& delta)override;
private:


	std::list<std::weak_ptr<Egg>> eggList_;

	int mask_;
	int col_;
};

