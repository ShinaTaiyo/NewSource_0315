//========================================================
//
//�P�P���P�R���F�R�c��ԂŃG�t�F�N�g�𔭎˂���[Effect.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (50000)//�G�t�F�N�g�̍ő吔
#define NUM_EFFECT (1)//�G�t�F�N�g�̎�ސ�

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXCOLOR col;//�F
	int nType;//���
	int nLife;//�̗�
	int nIdxShadow;//�e�̃C���f�b�N�X
	float fRWidth;//���i���a�j
	float fRHeight;//�����i���a�j
	float fScale;//�G�t�F�N�g�̑傫��
	float fRedution;//�G�t�F�N�g�̑傫��������������X�s�[�h
	float fRotMove;//���������̐��l�����߂�ϐ�
	bool bUse;//�g�p���Ă��邩�ǂ���
}Effect;

typedef enum
{
	EFFECTTYPE_NORMAL = 0,//���ʂ̃G�t�F�N�g
	EFFECTTYPE_ROLING,//���邮��G�t�F�N�g
	EFFECTTYPE_MAX,
}EFFECTTYPE;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(int nType, int nLife, float fScale,float fRedution, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,float fRotMove);

#endif



