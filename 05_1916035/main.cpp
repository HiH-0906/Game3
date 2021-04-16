#include <DxLib.h>
#include <string>
#include <fstream>

#define SCREEN_SIZE_X 400
#define SCREEN_SIZE_Y 400
#define DIVISION_NUM 8
#define DIVISION_X (SCREEN_SIZE_X / DIVISION_NUM)
#define DIVISION_Y (SCREEN_SIZE_Y / DIVISION_NUM)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	auto ReedFile = [](const std::string filename,std::string& str) {
		std::fstream file(filename);
		if (!file.is_open())
		{
			return false;
		}
		std::getline(file, str);
		return true;
	};

	auto CheckStr = [](const std::string str)
	{
		return str.find_first_not_of("0123456789yx+-*/=") == std::string::npos;
	};


	SetOutApplicationLogValidFlag(false);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("–â5_1916035_‹´–{‘å‹P");
	if (DxLib_Init() == -1)
	{
		return 0;
	}

	int a = 1;
	int b = 0;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		std::string filename = "number5.txt";
		std::string str = "";
		if (!ReedFile(filename, str) || !CheckStr(str))
		{
			break;
		}

		for (int tmp = 0; tmp < 8; tmp++)
		{
			DrawLine(DIVISION_X * tmp, 0, DIVISION_X * tmp, SCREEN_SIZE_Y, 0x888888);
			DrawLine(0, DIVISION_Y * tmp, SCREEN_SIZE_X, DIVISION_Y * tmp, 0x888888);
		}
		DrawLine(SCREEN_SIZE_X / 2, 0, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0xffff);
		DrawLine(0, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X, SCREEN_SIZE_Y / 2, 0xffff);

		for (int x = 0; x < SCREEN_SIZE_X; x++)
		{
			DrawPixel(SCREEN_SIZE_X - x, a * (x - SCREEN_SIZE_X / 2) + (b * -DIVISION_X) + SCREEN_SIZE_X / 2, 0xff0000);
		}

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
