//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[game.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE=0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ��ԁi�Q�[���i�s���j
	GAMESTATE_END,//�I����ԁi�G�S�ŁA�v���C���[���ŁA�^�C���I�[�o�[�Ȃǁj
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);//�����Q�b�g����B
bool bGetEditCheck(void);

#endif

