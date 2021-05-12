#include <utility>
#include <memory>
#include <vector>
#include <chrono>
#include <Dxlib.h>
#include "Class/Square.h"
#include "Class/Circle.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

namespace 
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
	std::chrono::system_clock::time_point now;
	std::chrono::system_clock::time_point old;
}

/// <summary>
/// íÜêSÇ©ÇÁéwíËÇ≥ÇÍÇΩä‘äuÇ≈ï™äÑê¸Çï`Ç≠
/// </summary>
/// <param name="inter">ä‘äu</param>
void DrawLine(const int& inter, bool flg = true, unsigned int col = 0xffff00)
{
	Vector2 tmp = flg == true ? Vector2{ (screenSizeX / 2) % inter ,(screenSizeY / 2) % inter } : Vector2{};
	for (int x = 0; x <= screenSizeX; x += inter)
	{
		DrawLine(tmp.x + x, 0, tmp.x + x, screenSizeY, col);
	}
	for (int y = -0; y <= screenSizeY; y += inter)
	{
		DrawLine(0, tmp.y + y, screenSizeX, tmp.y + y, col);
	}

	DrawLine(screenSizeX / 2, 0, screenSizeX / 2, screenSizeY, 0xffffff);
	DrawLine(0, screenSizeY / 2, screenSizeX, screenSizeY / 2, 0xffffff);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText("1916035_ã¥ñ{ëÂãP");

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	

	std::vector<std::unique_ptr<Shape>> objList;

	objList.reserve(100);

	objList.emplace_back(std::make_unique<Circle>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 50.0f ,50.0f }, 0xff0000));
	objList.emplace_back(std::make_unique<Square>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 100.0f, 100.0f }, 0xffffff));
	objList.emplace_back(std::make_unique<Square>(Vector2Flt{ 100.0f, 300.0f }, Vector2Flt{ 100.0f, 100.0f }, 0x00ff00));

	now = std::chrono::system_clock().now();
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		old = now;
		now = std::chrono::system_clock().now();
		ClsDrawScreen();

		float delta = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - old).count() / 1000.0f);

		for (const auto& obj : objList)
		{
			obj->Update(delta);
		}

		DrawLine(50);

		for (const auto& obj : objList)
		{
			obj->Draw();
		}
		
		DrawFormatString(0,0,0xffffff,"deltaTime::%lf\n",delta);
		ScreenFlip();
	}

	DxLib_End();

	return 1;
}