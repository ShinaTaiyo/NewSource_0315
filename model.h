//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[model.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

#define NUM_MODEL (100)//���f���̎��
#define MAX_MODEL (1024)//�ǂݍ��ރ��f���̍ő吔
#define MODELSET "data\\TEXTFILE\\model.txt"

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 vtxMinModel;//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	int nType;//���
	int nIdxShadow;//�e�̃C���f�b�N�X
	bool bUse;//�g�p���Ă��邩�ǂ���
}Model;

typedef enum
{
	MODELTYPE_BILL = 0,//�r��
	MODELTYPE_BRIDDGE,//��
	MODELTYPE_MAX,//�ő吔
}MOELTYPE;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
int GetNumModel(void);//�ǂݍ��ރ��f���̍ő吔���擾����
bool bCollisionModel(D3DXVECTOR3* pPos,
	D3DXVECTOR3* pPosOld,
	D3DXVECTOR3* pMove,
	D3DXVECTOR3 Size
	);

#endif

