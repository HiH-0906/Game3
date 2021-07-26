#pragma once
#include "../common/Vector2.h"

class UIBase
{
public:
	UIBase(const Vector2& pos, const Vector2& scrSize);
	virtual ~UIBase() = default;
	virtual void UpDate(const double& delta) = 0;
	/// <summary>
	/// 自身のスクリーンへの描画
	/// </summary>
	virtual void UIDraw(void) = 0;
	virtual void Draw(void);
	bool isAlive(void);
protected:
	Vector2 pos_;
	Vector2 scrSize_;
	int screen_;
	bool isAlive_;
};

