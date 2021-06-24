#include <array>
#include <string>
#include <DxLib.h>
#include "Sorce/Geometry.h"

namespace
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
	constexpr float BlockSize = 32.0f;
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
	int row = LoadGraph("Image/arrow2.png");
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
		int y = screenSizeY / 2;
		Vector2f currentPos(x, y);
		Vector2f lastPos = Vector2f::ZERO;
		Vector2f lastDeltaVec[2] = { Vector2f::ZERO,Vector2f::ZERO };
		for (int i = 0; i < 1080 / BlockSize; i++)
		{
			float nextX = i * BlockSize;
			float nextY = (BlockSize * 2.0f * sinf(0.5f * static_cast<float>((nextX + fCnt * 3)) * DX_PI_F / 180.0f));

			Vector2f deltaVec =  Vector2f(BlockSize, nextY).Normalized() * BlockSize;

			Vector2f next = currentPos +deltaVec;
			
			auto middleVecTmp = deltaVec;
			auto middleVecR = deltaVec.Rotated90();
			// ‚Ð‚Æ‚Â‘O
			if (!(lastDeltaVec[0] == Vector2f::ZERO))
			{
				middleVecR = (middleVecR + lastDeltaVec[0]).Normalized() * BlockSize;
			}
			auto middleVecL = lastDeltaVec[0];
			// “ñ‚Â‘O
			if (!(lastDeltaVec[1] == Vector2f::ZERO))
			{
				middleVecL = (middleVecL + lastDeltaVec[1]).Normalized() * BlockSize;
			}
			lastDeltaVec[1] = lastDeltaVec[0];
			lastDeltaVec[0] = deltaVec.Rotated90();


			auto middlePosL = currentPos + middleVecL;
			auto middlePosR = next + middleVecR;

			
			if (lastPos != Vector2f::ZERO)
			{
				auto rightPos = currentPos + middleVecR;
				auto leftPos = lastPos + middleVecL;
				DrawRectModiGraph(lastPos.x, lastPos.y, currentPos.x, currentPos.y, rightPos.x, rightPos.y, leftPos.x, leftPos.y, 48, 0, 16, 16, groundH, true);
			}

			/*DrawLineAA(lastPos.x, lastPos.y, currentPos.x, currentPos.y, 0xffffff, 2.0f);
			DrawLineAA(currentPos.x, currentPos.y, rightPos.x, rightPos.y, 0x88ff88, 2.0f);
			DrawLineAA(lastPos.x, lastPos.y, leftPos.x, leftPos.y, 0x8888ff, 2.0f);
			DrawCircle(lastPos.x, lastPos.y, 5, 0xff8888);*/

			lastPos = currentPos;
			currentPos = next;
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