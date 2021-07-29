#include<DxLib.h>
#include<cmath>
#include"Geometry.h"
#include"homingShot.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Position2f& posA, float radiusA, const Position2f& posB,  float radiusB) {
	//当たり判定を実装してください
	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(true);
	SetMainWindowText("弾幕だよ～");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetAlwaysRunFlag(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	int arrowH = LoadGraph("image/arrow2.png");


	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;

	//適当に256個くらい作っとく
	Bullet bullets[256];
	HomingShot homingShots[8] = {};//playerhoming弾

	for (auto& shot: homingShots)
	{
		shot.trail_.SetHandle(arrowH);
	}

	Position2f enemypos(320,25);//敵座標
	Position2f playerpos(320, 400);//自機座標

	unsigned int frame = 0;//フレーム管理用

	char keystate[256] = {};
	char lastkeystate[256] = {};
	bool isDebugMode = false;
	bool isRightHoming = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;

	constexpr float homing_Shot_Speed = 10.0f;
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE)) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//背景
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//プレイヤー
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
		}

		if (keystate[KEY_INPUT_Z]&&!lastkeystate[KEY_INPUT_Z])
		{
			DrawString(100,100,"発射", 0xffffff);
			for (auto& hshot : homingShots)
			{
				if (!hshot.isActive)
				{
					hshot.isActive = true;
					hshot.pos = playerpos;
					hshot.vel = { isRightHoming ? homing_Shot_Speed : -homing_Shot_Speed,0.0f };
					isRightHoming = !isRightHoming;
					hshot.trail_.Reset();
					break;
				}
			}
		}

		// playerの弾描画
		for (auto& hshot:homingShots)
		{
			if (!hshot.isActive)
			{
				continue;
			}
			hshot.trail_.Update();
			hshot.pos += hshot.vel;
			hshot.trail_.Draw();
			// テキトーな尾
			/*for (int i = 0; i < 5; i++)
			{

				auto tailPos = hshot.pos - hshot.vel * 2.0f * static_cast<float>(i);
				auto thickness = static_cast<float>(6 - i);
				DrawLine(hshot.pos.x, hshot.pos.y, tailPos.x, tailPos.y, 0xff4444, thickness * 4.0f);
			}*/

			// 思ったより出来が良かった版sin,cos版と遜色ないならこっちでいい疑惑
			hshot.vel = (hshot.vel + (enemypos - hshot.pos).Normalized()).Normalized() * homing_Shot_Speed;

			// sin,cos版 @@なんかうまくいってない
			/*auto nVelocity = hshot.vel.Normalized();
			auto nToEnemy = (enemypos - hshot.pos).Normalized();
			auto dot = Dot(nVelocity, nToEnemy);
			auto angle = acos(dot);
			angle = std::fminf(angle, DX_PI_F / 24.0f);
			float sign = Cross(nVelocity, nToEnemy) > 0.0f ? 1.0f : -1.0f;
			angle = atan2(hshot.vel.y, hshot.vel.x) + sign * angle;
			hshot.vel += Vector2f(cos(angle), sin(angle)) * homing_Shot_Speed;*/


			DrawCircleAA(hshot.pos.x, hshot.pos.y, 8.0f, 16, 0xff4444);
			// 敵との当たり判定
			if ((enemypos - hshot.pos).SQMagnitude() < 900.0f)
			{
				hshot.isActive = false;
			}
			// 画面外判定
			if (hshot.pos.x + 16 < 0 || hshot.pos.x - 16 > 640 ||
				hshot.pos.y + 24 < 0 || hshot.pos.y - 24 > 480) 
			{
				hshot.isActive = false;
			}
		}

		DrawCircleAA(enemypos.x, enemypos.y, 30.0f, 16, 0x00ff00, false, 3.0f);

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//自機の本体(当たり判定)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//弾発射
		if (frame % 12 == 0) {
			for (auto& b : bullets) {
				if (!b.isActive) {
					//b.pos = enemypos;
					//b.vel = Vector2(0, 5);
					//b.isActive = true;
					break;
				}
			}
		}

		//弾の更新および表示
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//弾の現在座標に弾の現在速度を加算してください
			
			float angle = 0.0f;
			//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			
			DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//弾を殺す
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//当たった反応を書いてください。
			}
		}

		//敵の表示
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//敵の本体(当たり判定)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		//パフォーマンス計測
		auto dCoolCount = GetDrawCallCount();
		auto fps = GetFPS();
		DrawBox(5, 50, 150, 100, 0xffffff, true);
		DrawFormatString(10, 50, 0x000000, "DrawColl=%d", dCoolCount);
		DrawFormatString(10, 80, 0x000000, "fps=%lf", fps);

		ScreenFlip();
		std::copy(std::begin(keystate), std::end(keystate), std::begin(lastkeystate));
	}

	DxLib_End();

	return 0;
}