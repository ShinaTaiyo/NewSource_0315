//========================================================
//
//�P�P���V���F���f���ǂݍ���[Block.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "Block.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
//�O���[�o���ϐ�
LPD3DXMESH g_pMeshBlock[NUM_BLOCK] = {};//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBlock = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatBlock = 0;//�}�e���A���̐�
D3DXVECTOR3 g_posBlock;//�ʒu
D3DXVECTOR3 g_rotBlock;//����
D3DXMATRIX g_mtxWorldBlock;//���[���h�}�g���b�N�X
#define Block_SCALE (10.0f)

Block g_aBlock[MAX_BLOCK];//���f�����̍\����

//int g_nldxShadow = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j

//�^�C�g����ʂ̏���������
void InitBlock(void)
{

	//g_nldxShadow = 0;//�Ώۂ̉e�̃C���f�b�N�X

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	g_posBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���f���̓ǂݍ���
	D3DXLoadMeshFromX("data\\Model\\Block_Red.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock[BLOCKTYPE_RED]);

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		g_aBlock[nCnt].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aBlock[nCnt].nIdxShadow = -1;
	}




	SetBlock(D3DXVECTOR3(0.0f, 20.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCKTYPE_RED);
	/*SetBlock(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BlockTYPE_BILL);
	SetBlock(D3DXVECTOR3(10.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BlockTYPE_BILL);
	SetBlock(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BlockTYPE_BILL);*/





}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		//���b�V���̔j��
		if (g_pMeshBlock != NULL)
		{
			g_pMeshBlock[nCnt]->Release();
			g_pMeshBlock[nCnt] = NULL;
		}
	}
	//�}�e���A���̔j��
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}
}
//============================
//���f���̍X�V����
//============================
void UpdateBlock(void)
{
	float fLength = 0.0f;
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{
			Player* pPlayer = GetPlayer();

			fLength = sqrtf((g_aBlock[nCnt].pos.x - pPlayer->pos.x) * (g_aBlock[nCnt].pos.x - pPlayer->pos.x) +
				(g_aBlock[nCnt].pos.z - pPlayer->pos.z) * (g_aBlock[nCnt].pos.z - pPlayer->pos.z) +
				(g_aBlock[nCnt].pos.y - pPlayer->pos.y) * (g_aBlock[nCnt].pos.y - pPlayer->pos.y)) / 3;

		/*	if (fLength <= 20.0f)
			{
				pPlayer->pos = pPlayer->posOld;
			}*/

		/*	if (pPlayer->pos.x >= g_aBlock[nCnt].pos.x - 20.0f &&
				pPlayer->pos.x <= g_aBlock[nCnt].pos.x + 20.0f &&
				pPlayer->pos.y >= g_aBlock[nCnt].pos.y - 20.0f &&
				pPlayer->pos.y <= g_aBlock[nCnt].pos.y + 20.0f &&
				pPlayer->pos.z >= g_aBlock[nCnt].pos.z - 20.0f &&
				pPlayer->pos.z <= g_aBlock[nCnt].pos.z + 20.0f)
			{
				pPlayer->move.y = 0.0f;
				pPlayer->pos = pPlayer->posOld;
			}*/

			//�e�̈ʒu��ݒ�
	/*		SetPositionShadow(g_aBlock[nCnt].nIdxShadow, g_aBlock[nCnt].pos, -1);*/
		}
	}
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾


	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBlock);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBlock[nCntBlock].rot.y, g_aBlock[nCntBlock].rot.x, g_aBlock[nCntBlock].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, g_aBlock[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				//���f���i�p�[�c�j�̕`��
				if (g_aBlock->nType == BLOCKTYPE_RED)
				{
					g_pMeshBlock[BLOCKTYPE_RED]->DrawSubset(nCntMat);
				}
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aBlock[nCntBlock].pos = pos;//�ʒu
			g_aBlock[nCntBlock].rot = rot;//����
			//g_aBlock[nCntBlock].nIdxShadow = SetShadow();//�e�̃C���f�b�N�X��ݒ�
			break;
		}
	}
}

Block* GetBlock(void)
{
	return &g_aBlock[0];
}
