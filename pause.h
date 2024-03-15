//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[pause.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�}�N����`
#define MAX_PAUSE_TEX (4)

//�񋓌^��`
typedef enum
{
	PAUSE_MENU_INDICATE=0,
	PAUSE_MENU_CONTINUE,
	PAUSE_MENU_RETRY,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_MAX
}PAUSE_MENU;

//�\���̒�`
typedef struct
{
	int nPauseMenu;//�Ăяo���R�}���h�̎�ނ����߂�ϐ�
	D3DXVECTOR3 pos;//���S���W��\���B
	bool bChooseMenu;//�I�񂾃R�}���h�����邭�Ȃ�悤�ɂ���t���O
}Pause;


//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

void SetEnablePause(int nType);
#endif
