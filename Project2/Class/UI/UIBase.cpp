#include <DxLib.h>
#include "UIBase.h"

UIBase::UIBase(const Vector2& pos, const Vector2& scrSize):
	pos_(pos),scrSize_(scrSize)
{
	screen_ = MakeScreen(scrSize_.x, scrSize_.y,true);
	isAlive_ = true;
}

void UIBase::Draw(void)
{
	DrawGraph(pos_.x, pos_.y, screen_, true);
}

bool UIBase::isAlive(void)
{
	return isAlive_;
}
