//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[ExModel.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _EXMODEL_H_
#define _EXMODEL_H_

#include "main.h"

#define NUM_EXMODEL (1)//���f���̎��
#define MAX_EXMODEL (100)//�ǂݍ��ރ��f���̍ő吔

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	int nType;//���
	float fWidth;//X�����̑傫��
	float fHeight;//Y�����̑傫��
	bool bUse;//�g�p���Ă��邩�ǂ���
}ExModel;


//�v���g�^�C�v�錾
void InitExModel(void);
void UninitExModel(void);
void UpdateExModel(void);
void DrawExModel(void);

#endif
