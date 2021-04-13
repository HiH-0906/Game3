#include <DxLib.h>

#define SCREEN_SIZE_X 400
#define SCREEN_SIZE_Y 400

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("–â5_1916035_‹´–{‘å‹P");
	if (DxLib_Init() == -1)
	{
		return 0;
	}

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		DrawLine(SCREEN_SIZE_X / 2, 0, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0xffff);
		DrawLine(0, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X, SCREEN_SIZE_Y / 2, 0xffff);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
