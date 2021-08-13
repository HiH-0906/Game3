#include<DxLib.h>
#include<cmath>
#include"Geometry.h"
#include"homingShot.h"
#include"HomingShotMng.h"
#include"HomingLaser.h"

///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Position2f& posA, float radiusA, const Position2f& posB,  float radiusB) {
	//�����蔻����������Ă�������
	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrvInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	DxLib::SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetMainWindowText("1916035_���{��P");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetAlwaysRunFlag(true);
	SetDrawScreen(DX_SCREEN_BACK);

	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);


	//�e�̔��a
	float bulletRadius = 5.0f;

	//���@�̔��a
	float playerRadius = 10.0f;

	Position2f enemypos(320,25);//�G���W
	Position2f playerpos(320, 400);//���@���W

	std::unique_ptr<HomingShotMng> homingShotMng_(new HomingShotMng(enemypos));

	unsigned int frame = 0;//�t���[���Ǘ��p

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

		//�w�i
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//�v���C���[
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
			auto shot = std::make_shared<HomingShot>();
			shot->isActive = true;
			shot->pos = playerpos;
			shot->vel = { isRightHoming ? homing_Shot_Speed : -homing_Shot_Speed,0.0f };
			homingShotMng_->AddHoming(shot);
			shot->islaser = false;
			isRightHoming = !isRightHoming;
		}
		if (keystate[KEY_INPUT_X] && !lastkeystate[KEY_INPUT_X])
		{
			auto shot = std::make_shared<HomingLaser>(keystate[KEY_INPUT_X],playerpos);
			shot->isActive = true;
			shot->pos = playerpos;
			shot->islaser = true;
			shot->vel = { isRightHoming ? homing_Shot_Speed : -homing_Shot_Speed,0.0f };
			homingShotMng_->AddHoming(shot);
			isRightHoming = !isRightHoming;
		}

		DrawCircleAA(enemypos.x, enemypos.y, 30.0f, 16, 0x00ff00, false, 3.0f);

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//�G�̕\��
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		homingShotMng_->Update();
		homingShotMng_->Draw();
		//�p�t�H�[�}���X�v��
		auto dCoolCount = GetDrawCallCount();
		auto fps = GetFPS();
		DrawBox(5, 40, 190, 170, 0xffffff, true);
		DrawFormatString(10, 50, 0x000000, "DrawColl=%d", dCoolCount);
		DrawFormatString(10, 80, 0x000000, "fps=%lf", fps);
		DrawFormatString(10, 110, 0x000000, "Z�FHomingShot");
		DrawFormatString(10, 140, 0x000000, "X�������FHomingLaser");
		ScreenFlip();

		std::copy(std::begin(keystate), std::end(keystate), std::begin(lastkeystate));
	}

	DxLib_End();

	return 0;
}