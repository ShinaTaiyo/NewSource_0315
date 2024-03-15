//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[EDITENEMY.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _EDITENEMY_H_
#define _EDITENEMY_H_

#include "main.h"

#define NUM_EDITENEMY (128)//���f���̎��
#define MAX_EDITENEMY (1024)//�ǂݍ��ރ��f���̍ő吔
#define MAX_EDITEMAT (100)//�}�e���A���̍ő吔
typedef struct
{
	LPD3DXMESH pMesh;//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;//�}�e���A���̐�
}EnemyEditorModelInfo;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 targetrot;//�ړI�̌���

	D3DXMATRIX mtxWorld;//�}�g���b�N�X���[���h
	D3DCOLORVALUE Diffuse[MAX_EDITEMAT];//�F����

	int nType;//�I��ł�����
	int nSummonTime;//�I��ł���G���������鎞��
	int nIdxShadow;//�e�̃C���f�b�N�X
	int nNumSetEnemy;//���Ԗڂ̓G���Z�b�g���Ă��邩
	bool bUse;//�g�p���Ă��邩�ǂ���

}EnemyEditor;

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXMATRIX mtxWorld;//�}�g���b�N�X���[���h
	D3DCOLORVALUE Diffuse[MAX_EDITEMAT];//�F����

	int nType;//�I��ł�����
	int nSummonTime;//�I��ł���G���������鎞��
	int nIdxShadow;//�e�̃C���f�b�N�X
	int nNumEnemy;//���Ԗڂ̓G���Z�b�g���Ă��邩
	bool bUse;//�g�p���Ă��邩�ǂ���

}EditEnemy;//�ݒ肵���G�̏��


typedef enum
{
	EDITENEMYTYPE_BILL = 0,//�r��
	EDITENEMYTYPE_BRIDDGE,//��
	EDITENEMYTYPE_MAX,//�ő吔
}EDITENEMYTYPE;

//�v���g�^�C�v�錾

//============================
//�G�G�f�B�^
//============================
void InitEnemyEditor(void);
void UninitEnemyEditor(void);
void UpdateEnemyEditor(void);
void DrawEnemyEditor(void);
//==========================================



void SetEditEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType,int nTime);

int GetEditTime(void);//�G�̏������Ԃ����߂�ϐ����擾����B

EnemyEditor* GetEnemyEditor(void);//�\���̂̏����擾
#endif


#pragma once
