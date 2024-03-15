//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[MeshCylinder.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "MeshCylinder.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//�}�N����`
#define MAX_MESHCYLINDER (2)//���b�V���t�B�[���h�ő吔
#define MAX_VERTEX (9)
#define MAX_DIVISION (3)

//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshCylinder;//���b�V���t�B�[���h�̈ʒu
D3DXVECTOR3 g_rotMeshCylinder;//���b�V���t�B�[���h�̌���
D3DXMATRIX g_mtxWorldMeshCylinder;//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X(float4*4)


#define MESHCYLINDERSCALE (100.0f)

//�^�C�g����ʂ̏���������
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ACT_Title.png",
		&g_pTextureMeshCylinder);

	g_posMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 100.0f);//�ʒu�̏�����
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 16,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
		//���_�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,//�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);


	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;

	//===================
	//���_����ݒ�
	//===================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�����ʒu�j
	pVtx[0].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.0f) * MESHCYLINDERSCALE,100.0f, cosf(-D3DX_PI * 1.0f) * MESHCYLINDERSCALE);
	pVtx[1].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.25f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 1.25f) * MESHCYLINDERSCALE);
	pVtx[2].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.5f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 1.5f) * MESHCYLINDERSCALE);
	pVtx[3].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.75f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 1.75f) * MESHCYLINDERSCALE);
	pVtx[4].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.0f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 0.0f) * MESHCYLINDERSCALE);
	pVtx[5].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 0.25f) * MESHCYLINDERSCALE);
	pVtx[6].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 0.5f) * MESHCYLINDERSCALE);
	pVtx[7].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * MESHCYLINDERSCALE, 100.0f, cosf(-D3DX_PI * 0.75f) * MESHCYLINDERSCALE);
	pVtx[8].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.0f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 1.0f) * MESHCYLINDERSCALE);
	pVtx[9].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.25f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 1.25f) * MESHCYLINDERSCALE);
	pVtx[10].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.5f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 1.5f) * MESHCYLINDERSCALE);
	pVtx[11].pos = D3DXVECTOR3(sinf(-D3DX_PI * 1.75f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 1.75f) * MESHCYLINDERSCALE);
	pVtx[12].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.0f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 0.0f) * MESHCYLINDERSCALE);
	pVtx[13].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.25f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 0.25f) * MESHCYLINDERSCALE);
	pVtx[14].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.5f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 0.5f) * MESHCYLINDERSCALE);
	pVtx[15].pos = D3DXVECTOR3(sinf(-D3DX_PI * 0.75f) * MESHCYLINDERSCALE,0.0f, cosf(-D3DX_PI * 0.75f) * MESHCYLINDERSCALE);


	//D3DXVec3Normalize = (0.0f, 0.0f, -1.0f);
	//nor�̐ݒ�i�����ݒ�j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);
	pVtx[15].nor = D3DXVECTOR3(0.0f,0.0f, -1.0f);


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f,0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.375f,0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.5f,0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.625f,0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f,0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.875f,0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(0.125f,1.0f);
	pVtx[10].tex = D3DXVECTOR2(0.25f,1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.375f,1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(0.625f,1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.75f,1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.875f,1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//==========================================================================

	//==============================
	//�C���f�b�N�X���̐ݒ�
	//==============================

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	int nCnt = 0;//�C���f�b�N�X�̔ԍ����J�E���g����p



		//�e�N�X�`�����W�̐ݒ�i�����ݒ�j(��U�ۗ��j
	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 3;
	pIdx[4] = 4;
	pIdx[5] = 5;
	pIdx[6] = 6;
	pIdx[7] = 7;
	pIdx[8] = 0;
	pIdx[9] = 8;
	pIdx[10] = 9;
	pIdx[11] = 10;
	pIdx[12] = 11;
	pIdx[13] = 12;
	pIdx[14] = 13;
	pIdx[15] = 14;
	pIdx[16] = 15;
	pIdx[17] = 8;

	//�C���f�b�N�X�̐ݒ�i�P�S�j

	/*		pIdx[0] = 3;
			pIdx[1] = 0;
			pIdx[2] = 4;
			pIdx[3] = 1;
			pIdx[4] = 5;
			pIdx[5] = 2;
			pIdx[6] = 2;
			pIdx[7] = 6;
			pIdx[8] = 6;
			pIdx[9] = 3;
			pIdx[10] = 7;
			pIdx[11] = 4;
			pIdx[12] = 8;
			pIdx[13] = 5;*/

			//�C���f�b�N�X�̐ݒ�
				/*	for (int nCntZ = 0; nCntZ < 2; nCntZ++)
					{
						for (int nCntX = 0; nCntX < 3; nCntX++)
						{
							pIdx[nCnt] = (3 + (3 * nCntZ) + nCntX);
							nCnt++;
							pIdx[nCnt] = (3 * nCntZ) + nCntX;
							nCnt++;
						}
						if (nCntZ != 1)
						{
							pIdx[nCnt] = pIdx[nCnt - 1];
							nCnt++;
							pIdx[nCnt] = 3 * (nCntZ + 2);
							nCnt++;
						}
					}*/

	/*for (int nCntZ = 0; nCntZ < MAX_DIVISION - 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MAX_DIVISION; nCntX++)
		{
			pIdx[nCnt] = (MAX_DIVISION + (MAX_DIVISION * nCntZ) + nCntX);
			nCnt++;
			pIdx[nCnt] = (MAX_DIVISION * nCntZ) + nCntX;
			nCnt++;
		}
		if (nCntZ != 1)
		{
			pIdx[nCnt] = pIdx[nCnt - 1];
			nCnt++;
			pIdx[nCnt] = MAX_DIVISION * (nCntZ + 2);
			nCnt++;
		}
	}*/

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();

	//===================================================================

}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateMeshCylinder(void)
{

}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, 16, 0, 18);
}