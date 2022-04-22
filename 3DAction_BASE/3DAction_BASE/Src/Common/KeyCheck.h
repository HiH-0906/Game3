//#pragma once

//��`
//---------------------------
enum KEY_LIST		//�Q�[�����ŗ��p����L�[���
{
	// �V�X�e�� �L�[���
	KEY_SYS_START			//0
	,KEY_SYS_TANK_START		//1

	// Player1 �L�[���
	, KEY_P1_UP				//2
	, KEY_P1_DOWN			//3
	, KEY_P1_LEFT			//4
	, KEY_P1_RIGHT			//5
	, KEY_P1_A				//6
	, KEY_P1_B				//7

	// Player2 �L�[���
	, KEY_P2_UP				//8
	, KEY_P2_DOWN			//9
	, KEY_P2_LEFT			//10
	, KEY_P2_RIGHT			//11
	, KEY_P2_A				//12
	, KEY_P2_B				//13

	, KEY_LIST_MAX			//14
};

//�ϐ��̌��J
//---------------------------
extern bool keyNew[KEY_LIST_MAX];		// ���t���[���̃L�[�̏��
extern bool keyTrgDown[KEY_LIST_MAX];	// KeyDown�̃g���K�[���
extern bool keyTrgUp[KEY_LIST_MAX];		// KeyUp�̃g���K�[���

//�v���g�^�C�v�錾
//---------------------------
void KeyInit(void);				// �L�[���̏�����
void CheckKeyList(void);		// �L�[���̍쐬
