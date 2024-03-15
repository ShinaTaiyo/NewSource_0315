#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����\����
typedef struct
{
	D3DXVECTOR3 PosV;//�x�_
	D3DXVECTOR3 targetPosV;//�ړI�̃J�����̎��_
	D3DXVECTOR3 PosR;//�����_
	D3DXVECTOR3 targetPosR;//�ړI�̃J�����̒����_
	D3DXVECTOR3 VecU;//������x�N�g��
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 Decayrot;//�J��������]������̂�x�点��
	float fXVaim;//X�����x�N�g��
	float fZVaim;//Z�����x�N�g��
	float fLength;//����
	int nMode;//�J�������[�h��ݒ肷��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
}Camera;

typedef enum
{
	CAMERAMODE_REVOLUTION = 0,//���]���[�h
	CAMERAMODE_ROTATION,//���]���[�h
	CAMERAMODE_MAX//�J�������[�h�ő吔
}CAMERAMODE;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void ControlCamera(void);//�J�����̓���
Camera* GetCamera(void);
void SetPosCamera(D3DXVECTOR3 PosR, D3DXVECTOR3 PosV);

#endif
