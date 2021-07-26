#pragma once
#include <memory>
#include "UIBase.h"
#include "../Object/TeamTag.h"

class Object;

class PlayerUI :
    public UIBase
{
public:
	PlayerUI(const Vector2& pos, const Vector2& scrSize,const TeamTag& tag);
	virtual ~PlayerUI()=default;
private:
	virtual void UpDate(const double& delta);
	/// <summary>
	/// 自身のスクリーンへの描画
	/// </summary>
	virtual void UIDraw(void);

	int mask_;
	int col_;

	std::weak_ptr<Object> player_;
};

