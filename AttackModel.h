//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[AttackModel.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _ATTACKMODEL_H_
#define _ATTACKMODEL_H_

#include "main.h"

#define NUM_ATTACKMODEL (3)//���f���̎��
#define MAX_ATTACKMODEL (1024)//�ǂݍ��ރ��f���̍ő吔
#define ATTACKMODELSET "data\\TEXTFILE\\AttackModel.txt"

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 vtxMinAttackModel;//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
	D3DXVECTOR3 vtxMaxAttackModel;//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	int nType;//���
	int nIdxShadow;//�e�̃C���f�b�N�X
	int nLife;//�̗�
	bool bUse;//�g�p���Ă��邩�ǂ���
	bool bOneFlag;//��񂾂������𔭓�������t���O
}AttackModel;

typedef enum
{
	ATTACKMODELTYPE_FIRETORNADO = 0,//��l���̋Z�F�t�@�C�A�g���l�[�h
	ATTACKMODELTYPE_METEOBALL,//��l���̋Z�F���e�I�{�[��
	ATTACKMODELTYPE_KILLNEEDLE,//��l���̋Z�F�L���j�[�h��
	ATTACKMODELTYPE_MAX,//�ő吔
}ATTACKMODELTYPE;

//�v���g�^�C�v�錾
void InitAttackModel(void);
void UninitAttackModel(void);
void UpdateAttackModel(void);
void DrawAttackModel(void);
void SetAttackModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move, int nType,int nLife);
int GetNumAttackModel(void);//�ǂݍ��ރ��f���̍ő吔���擾����
AttackModel* GetAttackModel(void);//�\���̂̏����擾����
#endif


