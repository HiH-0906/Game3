#include <utility>
#include <memory>
#include <vector>
#include <Dxlib.h>
#include "Class/Square.h"
#include "_debug/_DebugDispOut.h"

namespace 
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(screenSizeX, screenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText("1916035_‹´–{‘å‹P");

	if (DxLib_Init() == -1)
	{
		return 0;
	}
	
	_dbgSetup(screenSizeX, screenSizeY, 255);

	std::unique_ptr<Shape> shape1 = std::make_unique<Square>(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 100.0f,100.0f }, 0xff0000);
	std::unique_ptr<Shape> shape2(new Square(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 100.0f, 100.0f }, 0xffffff));
	std::unique_ptr<Shape> shape3;

	shape3.reset(new Square(Vector2Flt{ screenSizeX / 2.0f, screenSizeY / 2.0f }, Vector2Flt{ 100.0f, 100.0f }, 0x00ff00));

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		ClsDrawScreen();

		DrawLine(screenSizeX / 2, 0, screenSizeX / 2, screenSizeY, 0xffffff);
		DrawLine(0, screenSizeY / 2, screenSizeX, screenSizeY / 2, 0xffffff);

		shape3->Draw(2.0f, { 0,0 });
		shape1->Draw(1.5f, { 50,50 });
		shape2->Draw(1.0f, { 0,0 });


		_dbgDraw();
		ScreenFlip();
	}

	DxLib_End();

	return 1;
}