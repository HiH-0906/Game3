#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Common/GameCommon.h"
#include "Common/KeyCheck.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Application.h"

bool Application::Init(void)
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	// システム処理
	SetWindowText("1916035_橋本大輝");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib の初期化失敗");
		return false;
	}

	KeyInit();
	mSceneManager.Init();

	// デバッグ
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	return true;

}

void Application::Run(void)
{
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		_dbgStartDraw();

		CheckKeyList();

		mSceneManager.Update();

		_dbgAddDraw();

		ScreenFlip();

	}
}

bool Application::Release(void)
{
	mSceneManager.Release();

	Effkseer_End();
	DxLib_End();

	return true;
}
