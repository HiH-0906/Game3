// 08_1916035.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <DxLib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <random>

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetOutApplicationLogValidFlag(false);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText(L"問8_1916035_橋本大輝");
	if (DxLib_Init() == -1)
	{
		return 0;
	}

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand1000(0, 999);
	
	std::mutex lock_;
	std::mutex perlock_;
	std::mutex mlock_;

	std::thread thr1;
	std::thread thr2;
	std::thread thr3;
	std::thread thr4;
	std::thread thr5;

	int perCnt;
	int min;
	int max;
	int cnt;
	bool start;
	int startCnt;

	unsigned long long allNum = 0;

	auto kantotuFunc = [&]() {
		int cnt = 0;
		int juelCnt = 0;
		int tenzyoCnt = 0;

		while (cnt < 6)
		{
			for (int i = 0; i < 10; i++)
			{
				juelCnt += 150;
				{
					if (rand1000(mt) < 5)
					{
						cnt++;
					}
				}
			}

			tenzyoCnt++;
			if (tenzyoCnt >= 20)
			{
				cnt++;
				tenzyoCnt = 0;
			}
		}
		return juelCnt;
	};

	auto thrFunc = [&]() {
		unsigned long long tmpNum = 0;
		int tmpmin = INT_MAX;
		int tmpmax = 0;
		for (int r = 0; r < 20; r++)
		{
			for (int i = 0; i < 10000; i++)
			{
				auto tmp = kantotuFunc();
				if (tmpmin > tmp)
				{
					tmpmin = tmp;
				}
				if (tmpmax < tmp)
				{
					tmpmax = tmp;
				}
				tmpNum += tmp;
			}
			{
				std::lock_guard<std::mutex> lock(perlock_);
				perCnt++;
			}
			{
				std::lock_guard<std::mutex> lock(mlock_);
				if (min > tmpmin)
				{
					min = tmpmin;
				}
				if (max < tmpmax)
				{
					max = tmpmax;
				}
			}
		}
		{
			std::lock_guard<std::mutex> lock(lock_);
			allNum += tmpNum;
		}
	};
	auto InitThr = [&]()
	{
		thr1 = std::thread(thrFunc);
		thr2 = std::thread(thrFunc);
		thr3 = std::thread(thrFunc);
		thr4 = std::thread(thrFunc);
		thr5 = std::thread(thrFunc);
	};

	auto EndThr = [&]()
	{
		if (thr1.joinable())
		{
			thr1.join();
		}
		if (thr2.joinable())
		{
			thr2.join();
		}
		if (thr3.joinable())
		{
			thr3.join();
		}
		if (thr4.joinable())
		{
			thr4.join();
		}
		if (thr5.joinable())
		{
			thr5.join();
		}
	};
	auto RetryThr = [&]()
	{
		EndThr();
		InitThr();
	};
	perCnt = 0;
	min = INT_MAX;
	max = 0;
	cnt = 0;
	start = false;
	startCnt = 0;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		if (!start)
		{
			auto tmp = GetFontSize();
			SetFontSize(tmp * 3);
			DrawFormatString(155, 200, 0xffffff, L"ガチャシミュレーター");
			if (startCnt / 30 % 2 == 0)
			{
				SetFontSize(tmp * 2.5);
				DrawFormatString(250, 400, 0xffffff, L"EnterKeyで開始");
			}
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				start = true;
				InitThr();
			}
			SetFontSize(tmp);
			startCnt++;
		}
		else
		{
			DrawBox(200, 275, 600, 325, 0xffffff, false);
			if (perCnt >= 100)
			{
				DrawBox(100, 140, 710, 240, 0x880000, true);
				DrawFormatString(125, 150, 0xffffff, L"メジロマックイーン100万回完凸迄にかかったジュエルの平均は%d個！", allNum / 1000000);
				{
					std::lock_guard<std::mutex> lock(mlock_);
					DrawFormatString(200, 180, 0xffffff, L"メジロマックイーン完凸迄の最小ジュエルは%d個！", min);
					DrawFormatString(190, 210, 0xffffff, L"メジロマックイーン完凸迄の最大ジュエルは%d個！", max);
				}
				DrawBox(201, 276, 599, 324, 0x0000ff, true);
				if (cnt / 30 % 2 == 0)
				{
					auto tmp = GetFontSize();
					SetFontSize(tmp * 2);
					DrawFormatString(250, 400, 0xffffff, L"EnterKeyでもう一度");
					SetFontSize(tmp);
				}
				cnt++;
				if (CheckHitKey(KEY_INPUT_RETURN))
				{
					RetryThr();
					perCnt = 0;
					allNum = 0;
					min = INT_MAX;
					max = 0;
					cnt = 0;
				}
			}
			else
			{
				DrawFormatString(350, 250, 0xffffff, L"諭吉溶かし中！");
				{
					std::lock_guard<std::mutex> lock(perlock_);
					DrawBox(201, 276, 201 + 4 * (perCnt), 324, 0xff0000, true);
				}
			}
		}
		ScreenFlip();
	}

	EndThr();

	DxLib_End();
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
