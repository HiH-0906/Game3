#include<DxLib.h>
#include<cmath>
#include"Geometry.h"

///“–‚½‚è”»’èŠÖ”
///@param posA A‚ÌÀ•W
///@param radiusA A‚Ì”¼Œa
///@param posB B‚ÌÀ•W
///@param radiusB B‚Ì”¼Œa
bool IsHit(const Position2f& posA, float radiusA, const Position2f& posB,  float radiusB) {
	//“–‚½‚è”»’è‚ğÀ‘•‚µ‚Ä‚­‚¾‚³‚¢
	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(true);
	SetMainWindowText("’e–‹‚¾‚æ`");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetAlwaysRunFlag(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//”wŒi—p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Position2f pos;//À•W
		Vector2f vel;//‘¬“x
		bool isActive = false;//¶‚«‚Ä‚é‚©`H
	};

	//’e‚Ì”¼Œa
	float bulletRadius = 5.0f;

	//©‹@‚Ì”¼Œa
	float playerRadius = 10.0f;

	//“K“–‚É256ŒÂ‚­‚ç‚¢ì‚Á‚Æ‚­
	Bullet bullets[256];
	Bullet homingShots[2] = {};//playerhoming’e

	Position2f enemypos(320,25);//“GÀ•W
	Position2f playerpos(320, 400);//©‹@À•W

	unsigned int frame = 0;//ƒtƒŒ[ƒ€ŠÇ——p

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

		//”wŒi
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//ƒvƒŒƒCƒ„[
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
			DrawString(100,100,"”­Ë", 0xffffff);
			for (auto& hshot : homingShots)
			{
				if (!hshot.isActive)
				{
					hshot.isActive = true;
					hshot.pos = playerpos;
					hshot.vel = { isRightHoming ? homing_Shot_Speed : -homing_Shot_Speed,0.0f };
					isRightHoming = !isRightHoming;
					break;
				}
			}
		}

		// player‚Ì’e•`‰æ
		for (auto& hshot:homingShots)
		{
			if (!hshot.isActive)
			{
				continue;
			}
			hshot.pos += hshot.vel;
			for (int i = 0; i < 5; i++)
			{

				auto tailPos = hshot.pos - hshot.vel * 2.0f * static_cast<float>(i);
				auto thickness = static_cast<float>(6 - i);
				DrawLine(hshot.pos.x, hshot.pos.y, tailPos.x, tailPos.y, 0xff4444, thickness * 4.0f);
			}

			//hshot.vel = (hshot.vel + (enemypos - hshot.pos).Normalized()).Normalized() * homing_Shot_Speed;
			hshot.vel = (hshot.vel + (enemypos - hshot.pos).Normalized()).Normalized() * homing_Shot_Speed;
			DrawCircleAA(hshot.pos.x, hshot.pos.y, 8.0f, 16, 0xff4444);
			// “G‚Æ‚Ì“–‚½‚è”»’è
			if ((enemypos - hshot.pos).SQMagnitude() < 900.0f)
			{
				hshot.isActive = false;
			}
			// ‰æ–ÊŠO”»’è
			if (hshot.pos.x + 16 < 0 || hshot.pos.x - 16 > 640 ||
				hshot.pos.y + 24 < 0 || hshot.pos.y - 24 > 480) {
				hshot.isActive = false;
			}
		}

		DrawCircleAA(enemypos.x, enemypos.y, 30.0f, 16, 0x00ff00, false, 3.0f);

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//©‹@‚Ì–{‘Ì(“–‚½‚è”»’è)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//’e”­Ë
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

		//’e‚ÌXV‚¨‚æ‚Ñ•\¦
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//’e‚ÌŒ»İÀ•W‚É’e‚ÌŒ»İ‘¬“x‚ğ‰ÁZ‚µ‚Ä‚­‚¾‚³‚¢
			
			float angle = 0.0f;
			//’e‚ÌŠp“x‚ğatan2‚ÅŒvZ‚µ‚Ä‚­‚¾‚³‚¢Bangle‚É’l‚ğ“ü‚ê‚é‚ñ‚¾‚æƒIƒD
			
			DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//’e‚Ì–{‘Ì(“–‚½‚è”»’è)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//’e‚ğE‚·
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//‚ ‚½‚èI
			//«‚ÌIsHit‚ÍÀ‘•‚ğ‘‚¢‚Ä‚Ü‚¹‚ñB©•ª‚Å‘‚¢‚Ä‚­‚¾‚³‚¢B
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//“–‚½‚Á‚½”½‰‚ğ‘‚¢‚Ä‚­‚¾‚³‚¢B
			}
		}

		//“G‚Ì•\¦
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//“G‚Ì–{‘Ì(“–‚½‚è”»’è)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();
		std::copy(std::begin(keystate), std::end(keystate), std::begin(lastkeystate));
	}

	DxLib_End();

	return 0;
}