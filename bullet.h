//========================================================
//
//�P�P���P�R���F�R�c��ԂŒe�𔭎˂���[bullet.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

#define MAX_BULLET (5000)//�e�̍ő吔
#define NUM_BULLET (11)//�e�̎�ސ�

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	int nType;//���
	int nLife;//�̗�
	int nIdxShadow;//�e�̃C���f�b�N�X
	int nNumEnemy;//���Ԃ̓G�������Ă��Ă��邩
	float fRWidth;//���i���a�j
	float fRHeight;//�����i���a)
	float fLength;//����
	float fRotY;//Y��]
	bool bUse;//�g�p���Ă��邩�ǂ���
	bool bOneFlag;//��񂾂����������鏈���悤�t���O
	bool bChangeFlag;//�l���㉺�����鎞�Ɏg���t���O

	float fVXaim;//X�����x�N�g��
	float fVYaim;//Y�����x�N�g��
	float fVZaim;//Z�����x�N�g��
	float fVaim;//���������x�N�g��
}Bullet;

typedef enum
{
	BULLETTYPE_NORMAL = 0,//���ʂ̃o���b�g
	BULLETTYPE_ENEMY,//�G�̒e
	BULLETTYPE_SWING,//�X�C���O�e
	BULLETTYPE_RANDUM,//�����e
	BULLETTYPE_CURVE,//�J�[�u�e
	BULLETTYPE_WALL,//�ǒe
	BULLETTYPE_BOUND,//�o�E���h�e
	BULLETTYPE_RING,//�����O�e
	BULLETTYPE_CHAINRING,//�����O�Ɋ֘A���Ĉړ�����e
	BULLETTYPE_CHAOS,//�J�I�X�{�[��
	BULLETTYPE_FIRE,//�t�@�C�A�{�[��
	BULLETTYPE_MAX
}BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(int nType,int nLife, float fRWidth, float fRHeight, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,int nNumEnemy,float fLength);

Bullet* GetBullet(void);//�e�\���̂̏����Q�b�g����

#endif


