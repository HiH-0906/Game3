#include <Dxlib.h>
#include "Vector2.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

Vector2 pointA;
Vector2 pointB;
Vector2 pointC;
int drawScreen_;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText(L"–â6_1916035_‹´–{‘å‹P");
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	drawScreen_ = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y, true);
	pointA = {200,190};
	pointB = {600,190};
	pointC = {400,520};

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		int x = 0;
		int y = 0;
		GetMousePoint(&x, &y);
		SetDrawScreen(drawScreen_);
		ClsDrawScreen();
		DrawLine(pointA.x, pointA.y, pointB.x, pointB.y, 0xffff);
		DrawLine(pointB.x, pointB.y, pointC.x, pointC.y, 0xffff);
		DrawLine(pointC.x, pointC.y, pointA.x, pointA.y, 0xffff);
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		DrawRotaGraph(x, y, 1.0, 0.0, drawScreen_, true);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}