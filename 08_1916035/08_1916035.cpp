// 08_1916035.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <random>


int main()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand1000(0, 999);
	unsigned long long alNum = 0;

	auto kantotuFunc = [&]() {
		int cnt = 0;
		int juelCnt = 0;
		int tenzyoCnt = 0;

		while (cnt < 6)
		{
			for (int i = 0; i < 10; i++)
			{
				juelCnt += 150;
				if (rand1000(mt) < 5)
				{
					//std::cout << "メジロマックイーン当たり！！" << std::endl;
					cnt++;
				}
			}

			tenzyoCnt++;
			if (tenzyoCnt >= 20)
			{
				cnt++;
				tenzyoCnt = 0;
				//std::cout << "メジロマックイーン天井…" << std::endl;
			}
		}

		//std::cout << "メジロマックイーンを完凸までにかかったジュエル数は" << juelCnt << "です" << std::endl;
		return juelCnt;
	};

	for (int i = 0; i < 1000000; i++)
	{
		alNum += kantotuFunc();
	}

	std::cout << "メジロマックイーンを100万回完凸までにかかったジュエル平均数数は" << alNum / 1000000 << "です" << std::endl;

	system("pause");
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
