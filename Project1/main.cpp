#include <vector>
#include <Dxlib.h>
#include "Class/Square.h"
#include "_debug/_DebugDispOut.h"

namespace 
{
	constexpr int screenSizeX = 640;
	constexpr int screenSizeY = 480;
	int mx = 0;
	int my = 0;
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
	shape1 = new Square(screenSizeX / 2, screenSizeY / 2, 100, 100);
	
	Shape* shape2;
	shape2 = new Shape(screenSizeX / 2, screenSizeY / 2, 100, 100);
	//
	//Shape* shape3;
	//shape3 = new Square((screenSizeX / 4) * 3, screenSizeY / 2, 50, 50);


	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		ClsDrawScreen();
		shape1->Draw(2.0f, Vector2{ 25,25 });
		shape2->Shape::Draw(2.0f, Vector2{ 0,0 });
		/*shape2->Draw();
		shape3->Shape::Draw();*/

		_dbgDraw();
		ScreenFlip();
	}
	delete shape1;
	DxLib_End();

	return 1;
}