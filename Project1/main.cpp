#include <Dxlib.h>

namespace {
	constexpr int screenSizeX = 800;
	constexpr int screenSizeY = 600;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(screenSizeX, screenSizeY, 16);
	ChangeWindowMode(true);
	SetWindowText(L"1916035_‹´–{‘å‹P");

	if (DxLib_Init())
	{
		return 0;
	}

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		ScreenFlip();
	}

	DxLib_End();

	return 1;
}