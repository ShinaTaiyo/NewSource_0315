//========================================================
//
//�P�P���V���F���f���ǂݍ���[Edit.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "edit.h"
#include "model.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

//�O���[�o���ϐ�
int g_nNumEdit = 0;
#define Edit_SCALE (10.0f)
#define EDITSET "data\\TEXTFILE\\Edit.txt"
#define SAVEEDIT "data\\TEXTFILE\\SaveEdit.txt"
#define SAVEENEMY "data\\TEXTFILE\\SaveEnemy.txt"


LPD3DXMESH g_pMeshEdit[NUM_EDIT] = {};//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
LPD3DXBUFFER g_pBuffMatEdit[NUM_EDIT] = {};//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatEdit[NUM_EDIT] = {};//�}�e���A���̐�
LPDIRECT3DTEXTURE9 g_apTextureEdit[NUM_EDIT] = {};
D3DXVECTOR3 g_posEdit;//�ʒu
D3DXVECTOR3 g_rotEdit;//����
D3DXMATRIX g_mtxWorldEdit;//���[���h�}�g���b�N�X

Edit g_aEdit;//���f�����̍\����

int g_nGetNumModel = 0;//�擾�������f���̍ő吔��ۑ�����
int g_nSetNumModel = 0;//���f����ݒu���鎞�̃^�C�v�ԍ���ۑ�����
int g_nSaveSetModel = 0;//���f����ݒu��������ۑ�����
Edit g_aSaveEditModel[MAX_MODEL];

//int g_nldxShadow = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j

//�^�C�g����ʂ̏���������
void InitEdit(void)
{

	g_nGetNumModel = GetNumModel();//�擾�������f���̍ő吔��ۑ�����

    g_nSetNumModel = 0;//���f����ݒu���鎞�̃^�C�v�ԍ���ۑ�����

	g_nSaveSetModel = 0;//���f����ݒu��������ۑ�����

	//for (int nCntEdit = 0; nCntEdit < NUM_EDIT; nCntEdit++)
	//{
	//	g_dwNumMatEdit[nCntEdit] = 0;//�}�e���A���̐�
	//}
	//g_nldxShadow = 0;//�Ώۂ̉e�̃C���f�b�N�X

	g_nNumEdit = 2;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	g_posEdit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotEdit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nNumEdit = 0;

	for (int nCntEditModel = 0; nCntEditModel < MAX_MODEL; nCntEditModel++)
	{
		g_aSaveEditModel[nCntEditModel].bUse = false;
		g_aSaveEditModel[nCntEditModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSaveEditModel[nCntEditModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSaveEditModel[nCntEditModel].nType = 0;
	}
	////���f���̓ǂݍ���
	//D3DXLoadMeshFromX("data\\Edit\\bill.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEdit,
	//	NULL,
	//	&g_dwNumMatEdit,
	//	&g_pMeshEdit[EditTYPE_BILL]);

	//D3DXLoadMeshFromX("data\\Edit\\BigBriddge.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatEdit,
	//	NULL,
	//	&g_dwNumMatEdit,
	//	&g_pMeshEdit[EditTYPE_BRIDDGE]);




	/*for (int nCnt = 0; nCnt < MAX_EDIT; nCnt++)
	{*/
		g_aEdit.bUse = false;//�g�p���Ă��邩�ǂ���
		g_aEdit.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aEdit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aEdit.nIdxShadow = -1;
		g_aEdit.nType = -1;
		g_aEdit.nEditMode = 0;
	//}

	g_aEdit.bUse = true;


	char aString[100] = {};//�������ǂݍ��ނ��߂̕ϐ�
	int nMaxRoadEdit = 0;//�ǂݍ��ރ��f���̍ő吔
	int nType = 0;//�ǂݍ��񂾃��f���̎��

	float fPosX = 0;//���f���̈ʒuX
	float fPosY = 0;//���f���̈ʒuY
	float fPosZ = 0;//���f���̈ʒuZ

	float fRotX = 0;//���f���̈ʒuX
	float fRotY = 0;//���f���̈ʒuY
	float fRotZ = 0;//���f���̈ʒuZ
	int nCnt = 0;//�ǂݍ��ރ��f���𐔂���p
	FILE* pFile;//�t�@�C���|�C���^

	char aStringPass[100] = {};

	pFile = fopen(MODELSET, "r");

	if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	{
		while (1)
		{

			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "ENDSCRIPT") == 0)
			{
				break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)//�ǂݍ��ރ��f���̎�ސ������߂�
			{
				fscanf(pFile, "%d", &g_nNumEdit);

				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					fscanf(pFile, "%s", &aString[0]);
				}
				for (int nRoadEdit = 0; nRoadEdit < g_nNumEdit; nRoadEdit++)
				{
					/*	while (1)
						{*/
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &aStringPass[0]);
						//���f���̓ǂݍ���
						D3DXLoadMeshFromX(&aStringPass[0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_pBuffMatEdit[nRoadEdit],//���f���ł́A������z��ɂ���
							NULL,
							&g_dwNumMatEdit[nRoadEdit],//���f���ł́A������z��ɂ���
							&g_pMeshEdit[nRoadEdit]);
						fscanf(pFile, "%s", &aString[0]);
					}
					/*	nCnt++;
						if (nCnt == g_nNumEdit)
						{
							break;
						}*/
				}
			}
			
		}
		fclose(pFile);
	}
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitEdit(void)
{
	for (int nCnt = 0; nCnt < NUM_EDIT; nCnt++)
	{
		//���b�V���̔j��
		if (g_pMeshEdit[nCnt] != NULL)
		{
			g_pMeshEdit[nCnt]->Release();
			g_pMeshEdit[nCnt] = NULL;
		}
		//�}�e���A���̔j��
		if (g_pBuffMatEdit[nCnt] != NULL)
		{
			g_pBuffMatEdit[nCnt]->Release();
			g_pBuffMatEdit[nCnt] = NULL;
		}
	}
}
//============================
//���f���̍X�V����
//============================
void UpdateEdit(void)
{
	Player* pPlayer = GetPlayer();


//=========================
//�G�f�B�b�g��Ԃ�ς���
//=========================
	if (GetKeyboardTrigger(DIK_F3) == true)
	{
		g_aEdit.nEditMode++;

		if (g_aEdit.nEditMode == 2)
		{
			g_aEdit.nEditMode = 0;
		}
	}
	//==================================================

	if (g_aEdit.nEditMode == EDITTYPE_MODEL)
	{//�G�f�B�b�g�̃��[�h�����߂鏈���ŁA���[�h���u���f���v��������...
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			g_aEdit.nType++;
		}
		else if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_aEdit.nType--;
		}

		if (g_aEdit.nType <= -1)
		{
			g_aEdit.nType = g_nNumEdit;
		}
		else if (g_aEdit.nType > g_nNumEdit)
		{
			g_aEdit.nType = 0;
		}




		if (g_aEdit.nEditMode == EDITTYPE_MODEL)
		{
			g_aEdit.pos = pPlayer->pos;
			g_aEdit.rot = pPlayer->rot;
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				SetEdit(g_aEdit.pos, g_aEdit.rot, g_aEdit.nType);
			}

			if (GetKeyboardTrigger(DIK_F10) == true)
			{

				FILE* pFile;//�t�@�C���|�C���^��錾
				pFile = fopen(SAVEEDIT, "w");//�t�@�C���ɍ���z�u�������f�����������o��

				if (pFile != NULL)//�t�@�C�����J���Ă�����
				{
					for (int nCntSaveModel = 0; nCntSaveModel < g_nSaveSetModel - 1; nCntSaveModel++)
					{
						fprintf(pFile, "MODELSET\n");
						fprintf(pFile, "TYPE %d\n", g_aSaveEditModel[nCntSaveModel].nType);//�ݒu�������f���̎�ނ������o��
						fprintf(pFile, "POS %.3f  %.3f  %.3f\n", g_aSaveEditModel[nCntSaveModel].pos.x
							, g_aSaveEditModel[nCntSaveModel].pos.y, g_aSaveEditModel[nCntSaveModel].pos.z);//�ݒu�������f���̈ʒu�������o��
						fprintf(pFile, "ROT %.3f  %.3f  %.3f\n", g_aSaveEditModel[nCntSaveModel].rot.x
							, g_aSaveEditModel[nCntSaveModel].rot.y, g_aSaveEditModel[nCntSaveModel].rot.z);//�ݒu�������f���̌����������o��
						fprintf(pFile, "ENDMODELSET\n");
						fprintf(pFile, "\n");
					}
					fclose(pFile);
				}
			}
		}//�G�̔z�u��EditEnemy.cpp�ōs��
	}


}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾


	//for (int nCntEdit = 0; nCntEdit < MAX_EDIT; nCntEdit++)
	//{
	/*	if (g_aEdit.bUse == true)
		{*/
			D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEdit);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEdit.rot.y, g_aEdit.rot.x, g_aEdit.rot.z);

			D3DXMatrixMultiply(&g_mtxWorldEdit, &g_mtxWorldEdit, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEdit.pos.x, g_aEdit.pos.y, g_aEdit.pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEdit, &g_mtxWorldEdit, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEdit);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			for (int nCntEDITSET = 0; nCntEDITSET < g_nNumEdit; nCntEDITSET++)
			{//�ǂݍ��ރ��f���̎�ސ���for�����񂵁A�����^�C�v�̃}�e���A���̃|�C���^��A�A
			//�p�[�c�̕`��A�}�e���A���̐ݒ������B
				if (g_aEdit.nType == nCntEDITSET)
				{
					//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
					pMat = (D3DXMATERIAL*)g_pBuffMatEdit[nCntEDITSET]->GetBufferPointer();

					//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
					for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEdit[nCntEDITSET]; nCntMat++)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, NULL);

						//���f���i�p�[�c�j�̕`��
						g_pMeshEdit[nCntEDITSET]->DrawSubset(nCntMat);
					}
					break;
				}
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		//}
	//}
}

//void SetEdit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
//{
//	for (int nCntEdit = 0; nCntEdit < MAX_EDIT; nCntEdit++)
//	{
//		if (g_aEdit.bUse == false)
//		{
//			g_aEdit.bUse = true;//�g�p���Ă��邩�ǂ���
//			g_aEdit.pos = pos;//�ʒu
//			g_aEdit.rot = rot;//����
//			g_aEdit.nType = nType;//���
//			g_aEdit.nIdxShadow = SetShadow();//�e�̃C���f�b�N�X��ݒ�
//			break;
//		}
//	}
//}

void SetEdit(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	/*for (int nCntEdit = 0; nCntEdit < MAX_EDIT; nCntEdit++)
	{
		if (g_aEdit.bUse == false)
		{*/
			Player* pPlayer = GetPlayer();
			//g_aEdit.bUse = true;//�g�p���Ă��邩�ǂ���
	/*		g_aEdit.nType = nType;
			g_aEdit.pos = pos;
			g_aEdit.rot = rot;*/

			g_aSaveEditModel[g_nSaveSetModel].nType = nType;
			g_aSaveEditModel[g_nSaveSetModel].pos = pos;
			g_aSaveEditModel[g_nSaveSetModel].rot = rot;
			SetModel(g_aEdit.pos, g_aEdit.rot, g_aEdit.nType);
			
			g_nSaveSetModel++;//�ݒu�������f���̍ő吔���C���N�������g����
			/*while (1)
			{
				g_aEdit.pos = pPlayer->pos;
				g_aEdit.rot = pPlayer->rot;

				if (GetKeyboardTrigger(DIK_RIGHT) == true)
				{
					g_aEdit.nType++;
				}
				else if (GetKeyboardTrigger(DIK_LEFT) == true)
				{
					g_aEdit.nType--;
				}

				if (g_aEdit.nType <= -1)
				{
					g_aEdit.nType = g_nNumEdit;
				}
				else if (g_aEdit.nType > g_nNumEdit)
				{
					g_aEdit.nType = 0;
				}

				if (GetKeyboardTrigger(DIK_F10) == true)
				{
					SetModel(g_aEdit.pos, g_aEdit.rot, g_aEdit.nType);
					break;
				}
			}
			break;*/
	//	}
	//}
}

Edit* GetEdit(void)
{
	return &g_aEdit;//�G�f�B�b�g��Ԃ��擾
}

