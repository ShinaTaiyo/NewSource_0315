//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[input.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

typedef enum
{
	JOYKEY_UP = 0,//�\���L�[�i��j
	JOYKEY_DOWN,//�\���L�[�i���j
	JOYKEY_LEFT,//�\���L�[�i���j
	JOYKEY_RIGHT,//�\���L�[�i�E�j
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_LPUSH,
	JOYKEY_RPUSH,
	JOYKEY_L1,//LT�{�^���i�\��j
	JOYKEY_R1,//RT�{�^���i�\��j
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,//A�{�^��
	JOYKEY_B,//B�{�^��
	JOYKEY_X,//X�{�^��
	JOYKEY_Y,//Y�{�^��
	JOYKEY_MAX
}JOYKEY;
//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);


void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);//�g���K�[����

HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool GetJoyPadTrigger(JOYKEY key);
#endif
