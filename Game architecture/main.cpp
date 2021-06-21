#include <array>
#include <string>
#include <DxLib.h>
#include "Sorce/Geometry.h"

namespace
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
	constexpr int BlockSize = 32;
}

Position2 GetMousePosition()
{
	int x, y;
	DxLib::GetMousePoint(&x, &y);
	return Position2(x, y);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText("1916035_‹´–{‘å‹P");

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetAlwaysRunFlag(true);
	std::array<int, 6> runImage;

	Rect player(100, 100, 200, 200);

	std::string imgstr = "Image/Adventurer/Individual Sprites/adventurer-run-0";
	for (int num = 0; num < 6; num++)
	{
		std::string tmp = imgstr + std::to_string(num) + ".png";
		runImage[num] = LoadGraph(tmp.c_str(), true);
	}

	std::array<int, 5> attackImage;
	imgstr = "Image/Adventurer/Individual Sprites/adventurer-attack1-0";
	for (int num = 0; num < 5; num++)
	{
		std::string tmp = imgstr + std::to_string(num) + ".png";
		attackImage[num] = LoadGraph(tmp.c_str(), true);
	}
	int fCnt = 0;
	int speed = 5;
	bool tmp = false;
	bool isReverse = false;
	int groundH = LoadGraph("Image/Assets/Assets.png");
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		if(CheckHitKey(KEY_INPUT_W))
		{
			player.pos.y -= speed;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			player.pos.y += speed;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			player.pos.x -= speed;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			player.pos.x += speed;
		}
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && !tmp)
		{
			isReverse = !isReverse;
			tmp = true;
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
		{
			tmp = false;
		}
		int x = 0;
		int y = screenSizeY / 2 + static_cast<int>(100.0f * sin(static_cast<float>(fCnt) / 180.0f * DX_PI_F));
		Vector2 guroundPos(x, y);
		for (int i = 0; i < 720 / BlockSize; i++)
		{
			int nextX = i * BlockSize;
			int nextY = static_cast<int>(100.0f * sin(static_cast<float>(0.5f * nextX + fCnt) / 180.0f * DX_PI_F));

			Vector2 next = guroundPos + Vector2(BlockSize,nextY).Normalized() * BlockSize;

			//DrawLineAA(x, y, nextX, nextY, 0xffffff,5.0f);
			DrawRectModiGraph(guroundPos.x, guroundPos.y, next.x, next.y, next.x, next.y + BlockSize, guroundPos.x, guroundPos.y + BlockSize,48,0,16,16, groundH, true);
			/*x = nextX;
			y = nextY;*/
			guroundPos = next;
		}

		int centerX = 16;
		if (isReverse)
		{
			int w, h;
			GetGraphSize(attackImage[fCnt / 5 % 5], &w, &h);
			centerX = w - centerX;
		}

		int mx, my;
		GetMousePoint(&mx, &my);
		Vector2D dir = Vector2D(mx - player.pos.x, my - player.pos.y);

		double angle = atan2(dir.y, dir.x);
		DrawRotaGraph2(player.pos.x, player.pos.y, centerX, 35, 4.0, angle, attackImage[fCnt / 5 % 5], true, isReverse);

		fCnt++;
		ScreenFlip();
	}

	DxLib::DxLib_End();
	return 0;
}