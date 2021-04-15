#include <Dxlib.h>
#include <math.h>
#include "Vector2.h"

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

Vector2 pointA;
Vector2 pointB;
Vector2 pointC;
int drawScreen_;

int clickCnt;
int cnt;
double rad;
bool leftold;
bool leftnow;
bool rightold;
bool rightnow;

void kochDraw(const Vector2& vecA, const Vector2& vecB, int num)
{
	if (num <= 0)
	{
		DrawLine(vecA.x, vecA.y, vecB.x, vecB.y, 0xffff);
		return;
	}
	Vector2 vecC = { (2 * vecA.x + vecB.x) / 3 ,(2 * vecA.y + vecB.y) / 3 };
	Vector2 vecD = { (vecA.x + 2 * vecB.x) / 3 ,(vecA.y + 2 * vecB.y) / 3 };
	Vector2 vecE = {};
	int x = vecB.x - vecA.x;
	int y = -(vecB.y - vecA.y);

	double distance = sqrt(x * x + y * y) / sqrt(3);
	double angle = 0.0;

	if (x >= 0)
	{
		angle = atan2(static_cast<double>(y),static_cast<double>(x)) + DX_PI / 6;
		vecE.x = vecA.x + static_cast<int>(distance * cos(angle));
		vecE.y = vecA.y - static_cast<int>(distance * sin(angle));
	}
	else
	{
		angle = atan2(static_cast<double>(y), static_cast<double>(x)) - DX_PI / 6;
		vecE.x = vecB.x - static_cast<int>(distance * cos(angle));
		vecE.y = vecB.y + static_cast<int>(distance * sin(angle));
	}

	{
		kochDraw(vecA, vecC, num - 1);
		kochDraw(vecC, vecE, num - 1);
		kochDraw(vecE, vecD, num - 1);
		kochDraw(vecD, vecB, num - 1);
	}

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText(L"問6_1916035_橋本大輝");
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	drawScreen_ = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y, true);
	pointA = {200,177};
	pointB = {600,177};
	pointC = {400,523};

	cnt = 0;
	clickCnt = 0;
	rad = DX_PI / 300;
	leftold = false;
	leftnow = false;
	rightold = false;
	rightnow = false;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		auto mouseInput = GetMouseInput();

		leftold = leftnow;
		leftnow = mouseInput & MOUSE_INPUT_LEFT;
		rightold = rightnow;
		rightnow = mouseInput & MOUSE_INPUT_RIGHT;

		if (!leftold && leftnow)
		{
			clickCnt++;
		}
		if (!rightold && rightnow)
		{
			clickCnt--;
			if (clickCnt < 0)
			{
				clickCnt = 0;
			}
		}
		int x = 0;
		int y = 0;
		GetMousePoint(&x, &y);
		SetDrawScreen(drawScreen_);
		ClsDrawScreen();

		kochDraw(pointA, pointB, clickCnt);
		kochDraw(pointB, pointC, clickCnt);
		kochDraw(pointC, pointA, clickCnt);

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		DrawRotaGraph(x, y, 1.0, rad * static_cast<double>(cnt), drawScreen_, true);
		DrawFormatString(0, 0, 0xffffff, L"現在の再帰回数：%d", clickCnt);
		DrawFormatString(0, 32, 0xffffff, L"左クリック：再帰回数を1回増やす");
		DrawFormatString(0, 64, 0xffffff, L"右クリック：再帰回数を1回減らす");
		ScreenFlip();
		cnt++;
	}
	DxLib_End();
	return 0;
}