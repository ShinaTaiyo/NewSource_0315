//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[Block.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

#define NUM_BLOCK (1)//���f���̎��
#define MAX_BLOCK (100)//�ǂݍ��ރ��f���̍ő吔

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	int nType;//���
	int nIdxShadow;//�e�̃C���f�b�N�X
	float fWidth;//X�����̑傫��
	float fHeight;//Y�����̑傫��
	bool bUse;//�g�p���Ă��邩�ǂ���
}Block;

typedef enum
{
	BLOCKTYPE_RED = 0,//�ԃu���b�N
	BLOCKTYPE_BRUE,//�u���b�N
	BLOCKTYPE_MAX
}BLOCKTYPE;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
Block* GetBlock(void);

#endif


