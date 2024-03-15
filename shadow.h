//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[title.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _SHADOW_H
#define _SHADOW_H_

#include "main.h"


#define MAX_SHADOW (10000)

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	int nNumBullet;//�ǂݍ��񂾒e�̔ԍ�
	bool bUse;//�g�p���Ă��邩�ǂ���
}Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(void);
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, int nNumBullet, int nNumEnemy, D3DXCOLOR col);
Shadow* GetShadow(void);
void KillShadow(int nIdxShadow);

#endif

