//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[Edit.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"

#define NUM_EDIT (100)//���f���̎��
#define MAX_EDIT (100)//�ǂݍ��ރ��f���̍ő吔

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	int nType;//���
	int nIdxShadow;//�e�̃C���f�b�N�X
	int nEditMode;//�G�f�B�b�g������
	bool bUse;//�g�p���Ă��邩�ǂ���
}Edit;

typedef enum
{
	EDITTYPE_MODEL = 0,//���f���̔z�u���s��
	EDITTYPE_ENEMY,//�G�̔z�u���s��
	EDITTYPE_MAX,//�ő吔
}EDITTYPE;

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SetEdit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
Edit* GetEdit(void);//�G�f�B�b�g��Ԃ��擾����
#endif


