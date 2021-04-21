#include <Dxlib.h>
#include "Class/Square.h"
#include "_debug/_DebugDispOut.h"

namespace {
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

	Shape* shape1;
	shape1 = new Shape(screenSizeX / 4, screenSizeY / 4, 50, 50);

	Shape* shape2;
	shape2 = new Square(screenSizeX / 2, screenSizeY / 2, 50, 50);

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		ClsDrawScreen();
		shape1->Draw();
		_dbgDraw();
		ScreenFlip();
	}

	DxLib_End();

	return 1;
}