//========================================================
//
//�P�P���P�R���F�R�c��ԂŒe�𔭎˂���[AttackBillBoard.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _ATTACKBILLBOARD_H_
#define _ATTACKBILLBOARD_H_

#include "main.h"

#define MAX_ATTACKBILLBOARD (5000)//�U���r���{�[�h�̍ő吔
#define NUM_ATTACKBILLBOARD (3)//�U���r���{�[�h�̎�ސ�

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 SavePos;//�ʒu��ۑ�����
	int nType;//���
	int nLife;//�̗�
	int nIdxShadow;//�e�̃C���f�b�N�X
	float fRWidth;//���i���a�j
	float fRHeight;//�����i���a�j
	float fLength;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	bool bOneFlag;//��x�������������鏈���p
	int nAnimationPattern;
	int nAnimationCnt;
}AttackBillBoard;

typedef enum
{
	A_BILLBOARDTYPE_THUNDER = 0,//�T���_�[
	A_BILLBOARDTYPE_SLASH,//�ʏ�U��1�u�X���b�V���v
	A_BILLBOARDTYPE_ATOMICSLASH,//��l���̕K�E�Z�u�A�g�~�b�N�X���b�V���v
	A_BILLBOARDTYPE_MAX
}A_BILLBOARDTYPE;

//�v���g�^�C�v�錾
void InitAttackBillBoard(void);
void UninitAttackBillBoard(void);
void UpdateAttackBillBoard(void);
void DrawAttackBillBoard(void);
void SetAttackBillBoard(int nType, int nLife, float fRWidth, float fRHeight, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);

AttackBillBoard* GetAttackBillBoard(void);//�e�\���̂̏����Q�b�g����

#endif



