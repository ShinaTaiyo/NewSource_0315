//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[title.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

#define MAX_WALL (5)//�ǂ̍ő喇��

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	float fWidth;//X�����̑傫��
	float fHeight;//Y�����̑傫��
	bool bUse;//�g�p���Ă��邩�ǂ���
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeiht);
Wall* GetWall(void);
#endif
