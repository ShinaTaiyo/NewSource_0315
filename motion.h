//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[Motion.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

#define NUM_MOTION (100)//���f���̎��
#define MAX_MOTION (5)//�ݒ肷�郂�[�V�����̍ő吔
#define MAX_KEY (30)//�L�[�̍ő吔
#define MAX_KEYSET (50)//1�̃��[�V�����̍ő吔
#define MAX_MOTIONMODEL (20)//���[�V�������s�����f���̍ő吔
#define MOTIONSET "data\\TEXTFILE\\RealStarWarrior2.txt"

//typedef struct
//{
//	D3DXVECTOR3 pos;//�ʒu
//	D3DXVECTOR3 rot;//����
//	D3DXVECTOR3 vtxMinMotion;//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
//	D3DXVECTOR3 vtxMaxMotion;//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
//	int nNumVtx;//���_��
//	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
//	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
//	int nType;//���
//	int nIdxShadow;//�e�̃C���f�b�N�X
//	bool bUse;//�g�p���Ă��邩�ǂ���
//}Motion;

typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 Rot;//����
	D3DXVECTOR3 TargetPos;//�ړI�̈ʒu
	D3DXVECTOR3 TargetRot;//�ړI�̌����܂Ńp�[�c���񂷂��߂̌v�Z�p�̌���
	D3DXVECTOR3 SaveRot;//���[�V�������Ƃɐݒ肵�������l��ۑ�����
}Key;

typedef struct
{
	int nFrame;//���̃|�[�Y�Ɉȍ~����܂ł̃X�s�[�h
	Key aKey[MAX_KEY];//�L�[�̍ő吔
}keySet;

typedef struct
{
	bool bUse;//���[�V�������g�p���邩�ǂ���
	bool bLoop;//���[�v�����邩�ǂ���
	int nNumKey;//�L�[�̐�
	keySet aKeySet[MAX_KEYSET];//�P�̃��[�V�����ɑ΂���L�[�Z�b�g�̍ő吔
}MotionSet;
//
//typedef enum
//{
//	MotionTYPE_BILL = 0,//�r��
//	MotionTYPE_BRIDDGE,//��
//	MotionTYPE_MAX,//�ő吔
//}MOELTYPE;

//�v���g�^�C�v�錾
void InitMotion(void);
//void UninitMotion(void);
void UpdateMotion(void);
//void DrawMotion(void);
void SetMotion(void);
//int GetNumMotion(void);//�ǂݍ��ރ��f���̍ő吔���擾����
#endif


