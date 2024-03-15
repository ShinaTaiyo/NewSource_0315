//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Camera.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "camera.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
//�O���[�o���ϐ�
//PDIRECT3DVERTEXBUFFER9 g_pVtxBuffCamera = NULL;//���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureCamera = NULL;//�e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posCamera;//�ʒu
//D3DXVECTOR3 g_rotCamera;//����
//D3DXMATRIX g_mtxWorldCamera;//���[���h�}�g���b�N�X(float4*4)

Camera g_Camera;//�J�����̏��

float g_fCameraPosVX;//�J������X�̎x�_�̈ʒu��ς���
float g_fCameraPosVY;//�J������Y�̎x�_�̈ʒu��ς���
float g_fCameraPosVZ;//�J������Z�̎x�_�̈ʒu��ς���

float g_fLength;//�J�����ƃv���C���[�̋���
float g_fAngle;//�J�����ƃv���C���[�̊p�x

//�^�C�g����ʂ̏���������
void InitCamera(void)
{
	Player* pPlayer = GetPlayer();

	g_fLength = 0.0f;
	g_fAngle = 0.0f;
	g_fCameraPosVX = 0.0f;//�J������X�̎x�_�̈ʒu��ς���
	g_fCameraPosVY = 350.0f;//�J������Y�̎x�_�̈ʒu��ς���
	g_fCameraPosVZ = 0.0f;//�J������Z�̎x�_�̈ʒu��ς���

	g_Camera.PosV = D3DXVECTOR3(pPlayer->pos.x, 200.0f,400.0f);//�x�_
	g_Camera.PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����_
	g_Camera.targetPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�̃J�����̎��_
	g_Camera.targetPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړI�̃J�����̒����_
	g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//�@��
	g_Camera.Decayrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fXVaim = 0.0f;
	g_Camera.fZVaim = 0.0f;
	//posV.y��posV.z�������_����̋����ɂȂ邽�߁i�J�����͒��~�_�̌�납�猩�邩��j�AposV.y��posV.z��sqrtf����,�����Ƃ������������߂�B
	g_Camera.fLength = 550.0f /*sqrtf(g_Camera.PosV.y * g_Camera.PosV.y + g_Camera.PosV.z * g_Camera.PosV.z) / 2*/;
	g_Camera.nMode = CAMERAMODE_REVOLUTION;//���]���[�h�ɏ���������
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitCamera(void)
{
	
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateCamera(void)
{
	//==================================
	//�擾���Ă�����
	//==================================
	Player* pPlayer = GetPlayer();

	//============================================================

	//========================
	//�J�����̑���
	//========================
	ControlCamera();

	//============================================================

	g_Camera.Decayrot.y += (0.0f - g_Camera.Decayrot.y) * 0.5f;

	g_Camera.rot.y += g_Camera.Decayrot.y;

	//==============================================
	//�ʏ�J�������[�h
	//==============================================
	if (g_Camera.nMode == CAMERAMODE_REVOLUTION)
	{
		g_Camera.targetPosR = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);//�����_
		g_Camera.targetPosV = D3DXVECTOR3(sinf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosR.x,
			200.0f + g_Camera.PosR.y + g_fCameraPosVY,
			cosf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosR.z);//���_

		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��

        //=============
		//�����ړ�����
		//===============
		g_Camera.PosR += (g_Camera.targetPosR - g_Camera.PosR) * 0.1f;
		g_Camera.PosV += (g_Camera.targetPosV - g_Camera.PosV) * 0.1f;

		//==========================================================================
	}

	//=============================================================================================================================
	
	//================================================
	//��]�J�������[�h
	//================================================
	if (g_Camera.nMode == CAMERAMODE_ROTATION)
	{
		g_Camera.PosR = D3DXVECTOR3(sinf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosV.x,
		    0.0f,
			cosf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosV.z);
		g_Camera.PosV = g_Camera.PosV;
		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��
	}

	//===========================================================================================================
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		4500.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&g_Camera.PosV,
		&g_Camera.PosR,
		&g_Camera.VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

void ControlCamera(void)
{

	if (GetKeyboardPress(DIK_O) == true)
	{//��ֈړ�
		g_fCameraPosVY += 5.0f;
	}
	if (GetKeyboardPress(DIK_L) == true)
	{//���ֈړ�
		g_fCameraPosVY -= 5.0f;
	}
	if (GetKeyboardPress(DIK_U) == true || GetJoypadPress(JOYKEY_R1) == true)
	{//�J�������E�ɉ�]
		g_Camera.Decayrot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_J) == true || GetJoypadPress(JOYKEY_L1) == true)
	{//�J���������ɉ�]
		g_Camera.Decayrot.y += -0.1f;
	}
	if (GetKeyboardTrigger(DIK_C) == true)
	{//�J�������[�h�ύX
		g_Camera.nMode++;

		if (g_Camera.nMode == 2)
		{
			g_Camera.nMode = 0;
		}
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{//�����_�Ƃ̋�������������
		g_Camera.fLength += 10.0f;
	}
	if (GetKeyboardPress(DIK_X) == true)
	{//�����_�̋�����Z������
		g_Camera.fLength -= 10.0f;
	}
}

//====================
//�J�������̎擾
//====================
Camera* GetCamera(void)
{
	return &g_Camera;
}