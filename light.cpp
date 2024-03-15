//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Light.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "light.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
//�O���[�o���ϐ�
//PDIRECT3DVERTEXBUFFER9 g_pVtxBuffLight = NULL;//���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureLight = NULL;//�e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posLight;//�ʒu
//D3DXVECTOR3 g_rotLight;//����
//D3DXMATRIX g_mtxWorldLight;//���[���h�}�g���b�N�X(float4*4)

#define MAX_LIGHT (3) //���C�g�̍ő吔

D3DLIGHT9 g_light[MAX_LIGHT];//���C�g�̏��


//�^�C�g����ʂ̏���������
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

	

		switch (nCntLight)
		{
	
		case 0:
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			break;
		case 1:
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.65f,0.65f,0.65f,1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.18f, 0.88f,-0.44f);
			break;
		case 2:
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.15f,0.15f,0.15f,1.0f);
			//���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			break;
		}
		
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);//�x�N�g���𐳋K������i������1�ɂ���j
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//���C�g��ݒ肷��i�ݒu�j
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

	//���C�g��L���ɂ���i�X�C�b�`���I���ɂ���j
	pDevice->LightEnable(nCntLight, TRUE);
	}
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitLight(void)
{
	
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateLight(void)
{

}