//#pragma once

//定義
//---------------------------
enum KEY_LIST		//ゲーム内で利用するキー情報
{
	// システム キー情報
	KEY_SYS_START			//0
	,KEY_SYS_TANK_START		//1

	// Player1 キー情報
	, KEY_P1_UP				//2
	, KEY_P1_DOWN			//3
	, KEY_P1_LEFT			//4
	, KEY_P1_RIGHT			//5
	, KEY_P1_A				//6
	, KEY_P1_B				//7

	// Player2 キー情報
	, KEY_P2_UP				//8
	, KEY_P2_DOWN			//9
	, KEY_P2_LEFT			//10
	, KEY_P2_RIGHT			//11
	, KEY_P2_A				//12
	, KEY_P2_B				//13

	, KEY_LIST_MAX			//14
};

//変数の公開
//---------------------------
extern bool keyNew[KEY_LIST_MAX];		// 現フレームのキーの状態
extern bool keyTrgDown[KEY_LIST_MAX];	// KeyDownのトリガー状態
extern bool keyTrgUp[KEY_LIST_MAX];		// KeyUpのトリガー状態

//プロトタイプ宣言
//---------------------------
void KeyInit(void);				// キー情報の初期化
void CheckKeyList(void);		// キー情報の作成
