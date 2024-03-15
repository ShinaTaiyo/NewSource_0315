//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Shadow.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "shadow.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "bullet.h"
#include "enemy.h"
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posShadow;//�ʒu
D3DXVECTOR3 g_rotShadow;//����
D3DXMATRIX g_mtxWorldShadow;//���[���h�}�g���b�N�X(float4*4)


Shadow g_aShadow[MAX_SHADOW];

int g_nIdxShadow = -1;//�e�̃C���f�b�N�X

#define SHADOW_SCALE (30.0f)

//�^�C�g����ʂ̏���������
void InitShadow(void)
{


	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu�̏�����
	g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏�����

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCnt].bUse = false;
		g_aShadow[nCnt].nNumBullet = -1;//�ǂݍ��񂾒e�̔ԍ�
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);


	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{

		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-SHADOW_SCALE, 1.0f, SHADOW_SCALE);
		pVtx[1].pos = D3DXVECTOR3(SHADOW_SCALE, 1.0f, SHADOW_SCALE);
		pVtx[2].pos = D3DXVECTOR3(-SHADOW_SCALE, 1.0f, -SHADOW_SCALE);
		pVtx[3].pos = D3DXVECTOR3(SHADOW_SCALE, 1.0f, -SHADOW_SCALE);

		//nor�̐ݒ�i�����ݒ�j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B


		//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateShadow(void)
{
	VERTEX_3D* pVtx;

	Bullet* pBullet = GetBullet();
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
		//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{

		if (g_aShadow[nCntShadow].bUse == true)
		{

			D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntShadow, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow(void)
{
	int nCntShadow = -1;
	


	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		//nCntShadow++;
		if (g_aShadow[nCnt].bUse == false)
		{
			g_aShadow[nCnt].bUse = true;
			nCntShadow = nCnt;
			break;
		}
	}


	return nCntShadow;
}

void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, int nNumBullet, int nNumEnemy, D3DXCOLOR col)
{
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	if (nldxShadow >= 0 && nldxShadow < MAX_SHADOW)
	{
		if (g_aShadow[nldxShadow].bUse == true)
		{
			//���_���W�̐ݒ�i�����ʒu�j
			pVtx[0].pos = D3DXVECTOR3(-SHADOW_SCALE, 1.0f, SHADOW_SCALE);
			pVtx[1].pos = D3DXVECTOR3(SHADOW_SCALE, 1.0f, SHADOW_SCALE);
			pVtx[2].pos = D3DXVECTOR3(-SHADOW_SCALE, 1.0f, -SHADOW_SCALE);
			pVtx[3].pos = D3DXVECTOR3(SHADOW_SCALE, 1.0f, -SHADOW_SCALE);
			g_aShadow[nldxShadow].pos = pos;

			g_aShadow[nldxShadow].pos.y = 0.0f;

			g_aShadow[nldxShadow].nNumBullet = nNumBullet;//�e�̔ԍ�


			//���_�J���[�̐ݒ�
			pVtx[0].col = col;//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[1].col = col;//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[2].col = col;//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[3].col = col;//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B

			/*Bullet* pBullet = GetBullet();
			for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pBullet++)
			{
				
				if (pBullet->bUse == false)
				{
					if (pBullet->nIdxShadow == nldxShadow)
					{
						g_aShadow[nldxShadow].bUse = false;
					}
				}
			}*/

			/*Enemy* pEnemy = GetEnemy();
			for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pEnemy++)
			{

				if (pEnemy->bUse == false)
				{
					if (pEnemy->nIdxShadow == nldxShadow)
					{
						g_aShadow[nldxShadow].bUse = false;
					}
				}
			}*/

		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

Shadow* GetShadow(void)
{
	return &g_aShadow[0];
}

void KillShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}

