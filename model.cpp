//========================================================
//
//�P�P���V���F���f���ǂݍ���[Model.cpp]
//Author:ShinaTaiyo
//
//=========================================================

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
int g_nNumModel = 0;//�ǂݍ��ރ��f���̍ő吔�����߂�
#define Model_SCALE (10.0f)
//#define SAVEModel "data\\TEXTFILE\\SaveModel.txt"

#define MAX_TEXTURE (32)


typedef struct
{
	LPD3DXMESH pMeshModel;//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
	LPD3DXBUFFER pBuffMatModel;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMatModel;//�}�e���A���̐�
    LPDIRECT3DTEXTURE9 apTextureModel[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
}ModelMat;

D3DXVECTOR3 g_posModel;//�ʒu
D3DXVECTOR3 g_rotModel;//����
D3DXMATRIX g_mtxWorldModel;//���[���h�}�g���b�N�X

Model g_aModel[MAX_MODEL];//���f�����̍\����

ModelMat g_aModelMat[NUM_MODEL];//���f���̃}�e���A���Ⓒ�_�̍\����

int g_nldxShadow = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j
bool g_bIsLanding;//�n�ʂɂ��邩�ǂ���

//�^�C�g����ʂ̏���������
void InitModel(void)
{
	g_nNumModel = 0;
	g_nldxShadow = 0;//�Ώۂ̉e�̃C���f�b�N�X
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	g_bIsLanding = false;//�n�ʂɂ��邩�ǂ���

	for (int nCntMatModel = 0; nCntMatModel < NUM_MODEL; nCntMatModel++)
	{
		g_aModelMat[nCntMatModel].dwNumMatModel = {};
		g_aModelMat[nCntMatModel].pBuffMatModel = {};
		g_aModelMat[nCntMatModel].pMeshModel = {};
		for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
		{
			g_aModelMat[nCntMatModel].apTextureModel[nCntTexture] = {};//��̃��f���Ɋ֘A����e�N�X�`���̏�����
		}
	}


	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		g_aModel[nCnt].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aModel[nCnt].nIdxShadow = -1;
		g_aModel[nCnt].nType = -1;
		g_aModel[nCnt].vtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
		g_aModel[nCnt].vtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
		g_aModel[nCnt].nNumVtx = 0;//���_��
		g_aModel[nCnt].sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		g_aModel[nCnt].pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	}


	char aString[100] = {};//�������ǂݍ��ނ��߂̕ϐ�
	int nMaxRoadModel = 0;//�ǂݍ��ރ��f���̍ő吔
	int nType = 0;//�ǂݍ��񂾃��f���̎��

	float fPosX = 0.0f;//���f���̈ʒuX
	float fPosY = 0.0f;//���f���̈ʒuY
	float fPosZ = 0.0f;//���f���̈ʒuZ

	float fRotX = 0.0f;//���f���̈ʒuX
	float fRotY = 0.0f;//���f���̈ʒuY
	float fRotZ = 0.0f;//���f���̈ʒuZ
	int nCnt = 0;//�ǂݍ��ރ��f���𐔂���p
	FILE* pFile;//�t�@�C���|�C���^

	char aStringPass[100] = {};

	pFile = fopen(MODELSET, "r");
	char cData;
	if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	{
		while (1)
		{

			fscanf(pFile, "%s", &aString[0]);


			cData = fgetc(pFile);

			if (strcmp(&cData, "#") == 0)
			{
				continue;
			}

			if (strcmp(&aString[0], "ENDSCRIPT") == 0)
			{
				fclose(pFile);
				break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)//�ǂݍ��ރ��f���̎�ސ������߂�
			{
				fscanf(pFile, "%d", &g_nNumModel);

				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					fscanf(pFile, "%s", &aString[0]);
				}
				for (int nRoadModel = 0; nRoadModel < g_nNumModel; nRoadModel++)
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
							&g_aModelMat[nRoadModel].pBuffMatModel,//���f���ł́A������z��ɂ���
							NULL,
							&g_aModelMat[nRoadModel].dwNumMatModel,//���f���ł́A������z��ɂ���
							&g_aModelMat[nRoadModel].pMeshModel);
						fscanf(pFile, "%s", &aString[0]);
					}
				/*	nCnt++;
					if (nCnt == g_nNumModel)
					{
						break;
					}*/
				}
			}
			else if (strcmp(&aString[0], "MODELSET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);
					if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);//�E�H�[���̎�ނ����߂�
					}
					else if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%f%f%f", &fPosX, &fPosY, &fPosZ);//�ʒu����ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{
						fscanf(pFile, "%f%f%f", &fRotX, &fRotY, &fRotZ);//��������ǂݍ���
					}
					else if (strcmp(&aString[0], "ENDMODELSET") == 0)
					{
						SetModel(D3DXVECTOR3(fPosX,fPosY,fPosZ), D3DXVECTOR3(fRotX,fRotY,fRotZ),nType);
						break;
					}
				}
			}
		}
	}

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{//�S�Ẵ��f���Ɋ��蓖�Ă�
		for (int nCntMat = 0; nCntMat < g_nNumModel; nCntMat++)
		{//��ނ����蓖�Ă�for��
			if (g_aModel[nCntModel].nType == nCntMat)
			{//���f���̎�ނ���v

				//���_���̎擾
				g_aModel[nCntModel].nNumVtx = g_aModelMat[nCntMat].pMeshModel->GetNumVertices();

				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				g_aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_aModelMat[nCntMat].pMeshModel->GetFVF());

				//���_�o�b�t�@�̃��b�N
				g_aModelMat[nCntMat].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aModel[nCntModel].pVtxBuff);


				for (int nCntVtx = 0; nCntVtx < g_aModel[nCntModel].nNumVtx; nCntVtx++)
				{
					//���_���W�̑��
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aModel[nCntModel].pVtxBuff;

					//====================================================
					//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
					//====================================================
					if (vtx.x > g_aModel[nCntModel].vtxMaxModel.x)
					{
						g_aModel[nCntModel].vtxMaxModel.x = vtx.x;
					}
					else if (vtx.x < g_aModel[nCntModel].vtxMinModel.x)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aModel[nCntModel].vtxMinModel.x = vtx.x;
					}
					else if (vtx.y > g_aModel[nCntModel].vtxMaxModel.y)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aModel[nCntModel].vtxMaxModel.y = vtx.y;
					}
					else if (vtx.y < g_aModel[nCntModel].vtxMinModel.y)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aModel[nCntModel].vtxMinModel.y = vtx.y;
					}
					else if (vtx.z > g_aModel[nCntModel].vtxMaxModel.z)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aModel[nCntModel].vtxMaxModel.z = vtx.z;
					}
					else if (vtx.z < g_aModel[nCntModel].vtxMinModel.z)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aModel[nCntModel].vtxMinModel.z = vtx.z;
					}
					//========================================================================

					//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
					g_aModel[nCntModel].pVtxBuff += g_aModel[nCntModel].sizeFVF;

				}

				//���_�o�b�t�@�̃A�����b�N
				g_aModelMat[nCntMat].pMeshModel->UnlockVertexBuffer();

				//��ޓ��肵�����A�����^�C�v��for���񂷕K�v�Ȃ��̂ŁAbreak
				break;

			}
		}
	}
	//���_���̎擾

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	for (int nCntModelSet = 0; nCntModelSet < g_nNumModel; nCntModelSet++)
	{
		//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
		pMat = (D3DXMATERIAL*)g_aModelMat[nCntModelSet].pBuffMatModel->GetBufferPointer();
		int nNumTexture = 0;
		for (int nCntMat = 0; nCntMat < (int)g_aModelMat[nCntModelSet].dwNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���
					//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModelMat[nCntModelSet].apTextureModel[nNumTexture]);
				nNumTexture++;
			}
		}
	}

}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < g_nNumModel; nCnt++)
	{
		//���b�V���̔j��
		if (g_aModelMat[nCnt].pMeshModel != NULL)
		{
			g_aModelMat[nCnt].pMeshModel ->Release();
			g_aModelMat[nCnt].pMeshModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_aModelMat[nCnt].pBuffMatModel != NULL)
		{
			g_aModelMat[nCnt].pBuffMatModel->Release();
			g_aModelMat[nCnt].pBuffMatModel = NULL;
		}
	}
}
//============================
//���f���̍X�V����
//============================
void UpdateModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == true)
		{
		    //�e�̈ʒu��ݒ�
			SetPositionShadow(g_aModel[nCnt].nIdxShadow, g_aModel[nCnt].pos,-1,-1,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		}
	}
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);


				for (int nCntModelSet = 0; nCntModelSet < g_nNumModel; nCntModelSet++)
				{//�ǂݍ��ރ��f���̎�ސ���for�����񂵁A�����^�C�v�̃}�e���A���̃|�C���^��A�A
				//�p�[�c�̕`��A�}�e���A���̐ݒ������B
					if (g_aModel[nCntModel].nType == nCntModelSet)
					{
						//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
						pMat = (D3DXMATERIAL*)g_aModelMat[nCntModelSet].pBuffMatModel->GetBufferPointer();

						int nNumTexture = 0;
						//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
						for (int nCntMat = 0; nCntMat < (int)g_aModelMat[nCntModelSet].dwNumMatModel; nCntMat++)
						{
							//�}�e���A���̐ݒ�
							pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

							if (pMat[nCntMat].pTextureFilename != NULL)
							{
								//�e�N�X�`���̐ݒ�
								pDevice->SetTexture(0,g_aModelMat[nCntModelSet].apTextureModel[nNumTexture]);
								nNumTexture++;
							}
							else
							{
								//�e�N�X�`���̐ݒ�
								pDevice->SetTexture(0, g_aModelMat[nCntModelSet].apTextureModel[nNumTexture]);
								nNumTexture++;
							}
	                        //���f���i�p�[�c�j�̕`��
							g_aModelMat[nCntModelSet].pMeshModel->DrawSubset(nCntMat);
						}
						break;
					}
				}
			
		}
	}
	        //�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
}

void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
			g_aModel[nCntModel].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aModel[nCntModel].pos = pos;//�ʒu
			g_aModel[nCntModel].rot = rot;//����
			g_aModel[nCntModel].nType = nType;//���
			g_aModel[nCntModel].nIdxShadow = SetShadow();//�e�̃C���f�b�N�X��ݒ�
			break;
		}
	}
}

int GetNumModel(void)
{
	return g_nNumModel;//�ǂݍ��ރ��f���̍ő吔���擾����
}

bool bCollisionModel(D3DXVECTOR3* pPos,
	D3DXVECTOR3* pPosOld,
	D3DXVECTOR3* pMove,
	D3DXVECTOR3 Size
)
{
	Player* pPlayer = GetPlayer();
	g_bIsLanding = false;//���n���Ă��邩�ǂ���
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{//���f�����g���Ă��邩�ǂ���
		if (pPos->x + Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x
			&& pPos->x - Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
			&& pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
			&& pPosOld->y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
			&& pPos->z + Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z
			&& pPos->z - Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z)
		{//�Ώۂ̉��[�����f����+Y�ɓ����������̏���
			pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y;
			g_bIsLanding = true;
		}
		else if (pPos->x + Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x
			&& pPos->x - Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
			&& pPos->y + Size.y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y
			&& pPosOld->y + Size.y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y
			&& pPos->z + Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z
			&& pPos->z - Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z)
		{//�Ώۂ̉��[�����f����+Y�ɓ����������̏���
			pPos->y = g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y - Size.y;
		}
		else if (pPos->x + Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x//�Ώۂ̍ő�X���W���A���f���̍ŏ�X���W����
				&& pPosOld->x + Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x//�Ώۂ�1F�O�̍ő�X���W���A���f���̍ŏ�X���W��艺
				&& pPos->y + Size.y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y//�Ώۂ̍ő�Y���W�����f���̍ŏ�Y���W����
				&& pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
				&& pPos->z + Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z//�Ώۂ̍ő�X���W���A���f���̍ŏ�X���W����
				&& pPos->z - Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z)//�Ώۂ�1F�O�̍ő�X���W���A���f���̍ŏ�X���W��艺)//�Ώۂ̍ŏ�Y���W�����f���̍ő�Y���W��艺
			{//�Ώۂ��u���b�N��-X�ɓ����������̏���
				pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x - Size.x / 2;
			}
			else if (pPos->x - Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
				&& pPosOld->x - Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
				&& pPos->y + Size.y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y
				&& pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
				&& pPos->z + Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z
				&& pPos->z - Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z)
			{//�Ώۂ��u���b�N��+X�ɓ����������̏���
				pPos->x = g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x + Size.x / 2;
			}
			else if (pPos->x + Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x
				&& pPos->x - Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
				&& pPos->y + Size.y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y
				&& pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
				&& pPos->z + Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z
				&& pPosOld->z + Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z)
			{//�Ώۂ��u���b�N��+X�ɓ����������̏���
				pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMinModel.z - Size.z / 2;
			}
			else if (pPos->x + Size.x / 2 >= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMinModel.x
				&& pPos->x - Size.x / 2 <= g_aModel[nCntModel].pos.x + g_aModel[nCntModel].vtxMaxModel.x
				&& pPos->y + Size.y >= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMinModel.y
				&& pPos->y <= g_aModel[nCntModel].pos.y + g_aModel[nCntModel].vtxMaxModel.y
				&& pPos->z - Size.z / 2 <= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z
				&& pPosOld->z - Size.z / 2 >= g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z)
			{//�Ώۂ��u���b�N��+X�ɓ����������̏���
				pPos->z = g_aModel[nCntModel].pos.z + g_aModel[nCntModel].vtxMaxModel.z + Size.z / 2;
			}

		}
	}
	return g_bIsLanding;

}
