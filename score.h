//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[score.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);//pos�́u���ˈʒu�v�Amove�́u�ړ��ʁv
void AddScore(int nValue);
int GetScore(void);

#endif
