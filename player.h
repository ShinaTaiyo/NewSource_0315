//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[Player.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _Player_H_
#define _Player_H_

#include "main.h"

#define MAX_PLAYERPARTS (100)//�v���C���[�̃p�[�c�̍ő吔
#define NUM_PLAYERPARTS (100)//�v���C���[�̃p�[�c�̎��
typedef struct
{
	//LPD3DXMESH pMesh;//���b�V���i���_���j�ւ̃|�C���^
	//LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	//DWORD dwNumMatPlayer;//�}�e���A���̐�
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 vtxMinModel;//�ʒu�̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;//�ʒu�̍ő�l
	D3DXVECTOR3 SaveRot;//������ۑ�����
	D3DXVECTOR3 SavePos;//�����ʒu��ۑ�����
	int nNumVtx;//���_��
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nIdxModelParent;//�e���f���̃C���f�b�N�X
	int nType;//�ǂݍ��ރ��f���̎��
	bool bUse;//�g�p���Ă��邩�ǂ���
	LPD3DXMESH pMesh;//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMatPlayer;//�}�e���A���̐�
}ModelParts;//�p�[�c���Ƃ̓���


typedef enum
{
	PLAYERSTATE_NUTORAL = 0,//�j���[�g�������
    PLAYERSTATE_MOVE,//�����Ă�����
    PLAYERSTATE_ATTACK,//�U�����
	PLAYERSTATE_JUMP,//�W�����v������
	PLAYERSTATE_LANDING,//���n����
}PLAYERSTATE;

typedef struct
{

}MatPlayer;

typedef enum
{
	PLAYERMODE_NORMAL = 0,//���ʃ��[�h
	PLAYERMODE_EDIT//�G�f�B�b�g���[�h
}PLAYERMODE;


typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 posOld;//�O�̈ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 targetrot;//�ړI�̌���
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 vtxMax;//�v���C���[�S�̂̍ő咸�_�l
	D3DXVECTOR3 vtxMin;//�v���C���[�S�̂̍ŏ����_�l
	bool bMotionFlag;//���[�V���������t���O
	bool bLandingFlag;//���n���[�V�����ƃj���[�g�������[�V�������g��������
	int nMode;//���[�h�̎��
	ModelParts aModel[MAX_PLAYERPARTS];
	MatPlayer aModelMat[NUM_PLAYERPARTS];
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nIdxShadow;//�e�̃C���f�b�N�X
	float fWidth;//�v���C���[�̕�
	float fHeight;//�v���C���[�̍���
	bool bIsLanding;//�n�ʂɂ��邩�ǂ���
	int nState;//�v���C���[�̏�Ԃ�\��
	int nCntMotionTime;//���[�V�������g�p���Ă��鎞�Ԃ�錾����
	D3DXVECTOR3 Size;//�v���C���[�S�̂̑傫��
	int nHp;//�v���C���[�̗̑�

	bool bSpecialAttackFlag;//�X�y�V�����A�^�b�N��������
	int nSpecialAttackCount;//�X�y�V�����A�^�b�N�������Ԃ��J�E���g���鏈��
}Player;//�p�[�c�S�́i�v���C���[�̓����j


//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void ControlPlayer(void);//�v���C���[�̑���
void AttackPlayer(void); //�v���C���[�̍U������
Player* GetPlayer(void);
void SetDamagePlayer(int nDamage);

void SetPlayerParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx,int nType);

bool bPlayerDeath(void);//�v���C���[�����񂾂��ǂ����̔����Ԃ�

#endif

