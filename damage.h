//========================================================
//
//�X���P�P���F�G�t�F�N�g������񌩒���[score.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _DAMAGE_H_
#define _DAMAGE_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;//�F
    int nLife;//�����i�ǂ̂��炢�_���[�W�\�L�����邩�j
	bool bUse;//�_���[�W�\�L���g�p���Ă��邩�ǂ���
	float fDamageWrite;//�\�L����_���[�W��
	int nDamagePosTexU;//�_���[�W�\�L�����邽�߂̃e�N�X�`���̈ʒu
	float a_col;//�J���[�̃A���t�@�l�ɂȂ�l����������
	float fRadius;//���S�_���甼�a���Ƃ��ă|���S����z�u�B
}Damage;


//�v���g�^�C�v�錾
void InitDamage(void);
void UninitDamage(void);
void UpdateDamage(void);
void DrawDamage(void);
void SetDamage(int nDamage,int nLife,D3DXVECTOR3 pos,float fRadius,D3DXCOLOR col);//pos�́u���ˈʒu�v�Amove�́u�ړ��ʁv
Damage *GetDamage(void);

#endif

