//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[MeshField.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "meshfield.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//�}�N����`
#define MAX_MESHFIELD (2)//���b�V���t�B�[���h�ő吔
#define MAX_VERTEX (9)
#define MAX_DIVISION (3)

//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;//���b�V���t�B�[���h�̈ʒu
D3DXVECTOR3 g_rotMeshField;//���b�V���t�B�[���h�̌���
D3DXMATRIX g_mtxWorldMeshField;//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X(float4*4)


#define MESHFIELDSCALE (100.0f)

//�^�C�g����ʂ̏���������
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ACT_Title.png",
		&g_pTextureMeshField);

	g_posMeshField = D3DXVECTOR3(0.0f, 5.0f, 0.0f);//�ʒu�̏�����
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
		//���_�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,//�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);


	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;

	//===================
	//���_����ݒ�
	//===================

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�����ʒu�j
	pVtx[0].pos = D3DXVECTOR3(-MESHFIELDSCALE, 0.0f, MESHFIELDSCALE);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, MESHFIELDSCALE);
	pVtx[2].pos = D3DXVECTOR3(MESHFIELDSCALE, 0.0f,MESHFIELDSCALE);
	pVtx[3].pos = D3DXVECTOR3(-MESHFIELDSCALE, 0.0f,0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f,100.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(MESHFIELDSCALE, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-MESHFIELDSCALE, 0.0f,-MESHFIELDSCALE);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -MESHFIELDSCALE);
	pVtx[8].pos = D3DXVECTOR3(MESHFIELDSCALE, 0.0f, -MESHFIELDSCALE);

	//nor�̐ݒ�i�����ݒ�j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);



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

	//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();
	
	//==========================================================================

	//==============================
	//�C���f�b�N�X���̐ݒ�
	//==============================

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	int nCnt = 0;//�C���f�b�N�X�̔ԍ����J�E���g����p

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

				for (int nCntZ = 0; nCntZ < MAX_DIVISION - 1; nCntZ++)
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
					}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();

	//===================================================================

}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitMeshField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateMeshField(void)
{

}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
}