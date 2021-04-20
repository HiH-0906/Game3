#include <DxLib.h>
#include "Shape.h"

void Shape::Draw(void)
{
	DrawBox(posX_ - (sizeX_ / 2), posY_ - (sizeY_ / 2), posX_ + (sizeX_ / 2), posY_ + (sizeY_ / 2), 0xffffff, true);
}

Shape::Shape() :posX_(320), posY_(240), sizeX_(50), sizeY_(50)
{
}
