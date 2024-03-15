//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Player.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "Player.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "emitter.h"
#include "block.h"
#include <stdio.h>
#include <string.h>
#include "model.h"
#include "motion.h"
#include "AttackModel.h"
#include "SkillGage.h"
#include "SkillName.h"
#include "AttackBillBoard.h"
#include "combo.h"
//�O���[�o���ϐ�
LPD3DXMESH g_pMeshPlayer = NULL;//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;//�}�e���A���̐�
D3DXVECTOR3 g_posPlayer;//�ʒu
D3DXVECTOR3 g_rotPlayer;//����
D3DXMATRIX g_mtxWorldPlayer;//���[���h�}�g���b�N�X
#define Player_SCALE (10.0f)

#define PLAYER_SPEED (7.0f)//�v���C���[�̑��x

#define PLAYERSET "data\\TEXTFILE\\PlayerSet.txt"//�v���C���[��ݒ肷��

Player g_aPlayer;//�v���C���[�̏��
ModelParts g_aModelParts[MAX_PLAYERPARTS]; // �e�p�[�c�̏��
MatPlayer g_aMatPlayer[NUM_PLAYERPARTS];
int g_nDelay = 0;//�f�B���C�J�E���g


int g_nNumPlayerModel = 0;//�ǂݍ��ރv���C���[�̃p�[�c�̍ő吔

//�^�C�g����ʂ̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	g_nNumPlayerModel = 0;
	//============================
	//���f���p�[�c�̏��̏�����
	//============================
	for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYERPARTS; nCntPlayerParts++)
	{
		g_aPlayer.aModel[nCntPlayerParts].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aPlayer.aModel[nCntPlayerParts].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aPlayer.aModel[nCntPlayerParts].pMesh = NULL;
		g_aPlayer.aModel[nCntPlayerParts].pBuffMat = NULL;
		g_aPlayer.aModel[nCntPlayerParts].dwNumMatPlayer = 0;
		g_aPlayer.aModel[nCntPlayerParts].mtxWorld;
		g_aPlayer.aModel[nCntPlayerParts].nIdxModelParent = 0;
		g_aPlayer.aModel[nCntPlayerParts].bUse = 0;
		g_aPlayer.aModel[nCntPlayerParts].nType = 0;
		g_aPlayer.aModel[nCntPlayerParts].nNumVtx = 0;//���_��
		g_aPlayer.aModel[nCntPlayerParts].vtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���_�̍ŏ��l
		g_aPlayer.aModel[nCntPlayerParts].vtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���_�̍ő�l
		g_aPlayer.aModel[nCntPlayerParts].sizeFVF;
		g_aPlayer.aModel[nCntPlayerParts].SaveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������ۑ�����
		g_aPlayer.aModel[nCntPlayerParts].SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����ʒu��ۑ�����

	}
	//===========================
	//�v���C���[���̏�����
	//===========================
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.targetrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.nIdxShadow = -1;//�e�̃C���f�b�N�X
	g_aPlayer.fWidth = 5.0f;
	g_aPlayer.fHeight = 10.0f;
	g_aPlayer.bIsLanding = false;//�n�ʂɂ��邩�ǂ���
	g_aPlayer.nState = PLAYERSTATE_NUTORAL;//�v���C���[�̏�Ԃ�\���ϐ�
	g_aPlayer.Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�v���C���[�S�̂̑傫��
	g_aPlayer.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�v���C���[�S�̂̍ő咸�_�l
	g_aPlayer.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�v���C���[�S�̂̍ŏ����_�l
	g_aPlayer.nMode = 0;//���[�h�̎��
	g_aPlayer.nCntMotionTime = 0;//���[�V�������g�p���Ă��鎞��
	g_aPlayer.bMotionFlag = false;//���[�V�������g�p��Ԃɂ���
	g_aPlayer.bLandingFlag = false;//���n���[�V�������g��������
	g_aPlayer.nHp = 1500;
	g_aPlayer.nSpecialAttackCount = 0;//�X�y�V�����A�^�b�N�������Ԃ��J�E���g����
	g_aPlayer.bSpecialAttackFlag = false;//�X�y�V�����A�^�b�N�𔭓������邩�ǂ���
	g_aPlayer.nIdxShadow = SetShadow();

	g_nDelay = 0;//�f�B���C�J�E���g

	char aString[100] = {};//�������ǂݍ��ނ��߂̕ϐ�
	int nMaxRoadModel = 0;//�ǂݍ��ރ��f���̍ő吔
	int nIdx = 0;//�ǂݍ��񂾃��f���̔ԍ��i�C���f�b�N�X�j
	int nType = 0;//�ǂݍ��ރ��f���̎��

	float fPosX = 0.0f;//���f���̈ʒuX
	float fPosY = 0.0f;//���f���̈ʒuY
	float fPosZ = 0.0f;//���f���̈ʒuZ

	float fRotX = 0.0f;//���f���̈ʒuX
	float fRotY = 0.0f;//���f���̈ʒuY
	float fRotZ = 0.0f;//���f���̈ʒuZ
	int nCnt = 0;//�ǂݍ��ރ��f���𐔂���p
	FILE* pFile;//�t�@�C���|�C���^

	char aStringPass[100] = {};

	pFile = fopen(PLAYERSET, "r");

	if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	{
		while (1)
		{

			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "ENDSCRIPT") == 0)
			{
				fclose(pFile);
				break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)//�ǂݍ��ރ��f���̎�ސ������߂�
			{
				fscanf(pFile, "%d", &g_nNumPlayerModel);

				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					fscanf(pFile, "%s", &aString[0]);
				}
				for (int nRoadModel = 0; nRoadModel < g_nNumPlayerModel; nRoadModel++)
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
							&g_aPlayer.aModel[nRoadModel].pBuffMat,//���f���ł́A������z��ɂ���
							NULL,
							&g_aPlayer.aModel[nRoadModel].dwNumMatPlayer,//���f���ł́A������z��ɂ���
							&g_aPlayer.aModel[nRoadModel].pMesh);
						fscanf(pFile, "%s", &aString[0]);
					}
				}
			}
			else if (strcmp(&aString[0], "MODELSET") == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);
				    if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);//�C���f�b�N�X�̎�ނ����߂�
					}
					else if (strcmp(&aString[0], "IDX") == 0)
					{
						fscanf(pFile, "%d", &nIdx);//�C���f�b�N�X�̎�ނ����߂�
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
						SetPlayerParts(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(fRotX, fRotY, fRotZ), nIdx,nType);
						break;
					}
				}
			}
		}
	}
	g_aPlayer.nIdxShadow = SetShadow();

	for (int nCntModel = 0; nCntModel < g_nNumPlayerModel; nCntModel++)
	{//�S�Ẵ��f���Ɋ��蓖�Ă�

		//���_���̎擾
		g_aPlayer.aModel[nCntModel].nNumVtx = g_aPlayer.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		g_aPlayer.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_aPlayer.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_aPlayer.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aPlayer.aModel[nCntModel].pVtxBuff);


		for (int nCntVtx = 0; nCntVtx < g_aPlayer.aModel[nCntModel].nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aPlayer.aModel[nCntModel].pVtxBuff;

			//====================================================
			//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
			//====================================================
			if (vtx.x > g_aPlayer.aModel[nCntModel].vtxMaxModel.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
		    else if (vtx.x < g_aPlayer.aModel[nCntModel].vtxMinModel.x)
			{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
				g_aPlayer.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (vtx.y > g_aPlayer.aModel[nCntModel].vtxMaxModel.y)
			{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
				g_aPlayer.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}
			else if (vtx.y < g_aPlayer.aModel[nCntModel].vtxMinModel.y)
			{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
				g_aPlayer.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}
			if (vtx.z > g_aPlayer.aModel[nCntModel].vtxMaxModel.z)
			{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
				g_aPlayer.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			else if (vtx.z < g_aPlayer.aModel[nCntModel].vtxMinModel.z)
			{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
				g_aPlayer.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}
			//========================================================================

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			g_aPlayer.aModel[nCntModel].pVtxBuff += g_aPlayer.aModel[nCntModel].sizeFVF;

		}

		//���_�o�b�t�@�̃A�����b�N
		g_aPlayer.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	//========================================
	//�v���C���[�S�̂̍ő�ŏ��l�����߂�
	//========================================
	for (int nCntModel = 0; nCntModel < g_nNumPlayerModel; nCntModel++)
	{
		if (g_aPlayer.vtxMax.x < g_aPlayer.aModel[nCntModel].vtxMaxModel.x)
		{
			g_aPlayer.vtxMax.x = g_aPlayer.aModel[nCntModel].vtxMaxModel.x;
		}
		else if (g_aPlayer.vtxMin.x > g_aPlayer.aModel[nCntModel].vtxMinModel.x)
		{
			g_aPlayer.vtxMin.x = g_aPlayer.aModel[nCntModel].vtxMaxModel.x;
		}

		if (g_aPlayer.vtxMax.y < g_aPlayer.aModel[nCntModel].vtxMaxModel.y)
		{
			g_aPlayer.vtxMax.y = g_aPlayer.aModel[nCntModel].vtxMaxModel.y;
		}
		else if (g_aPlayer.vtxMin.y > g_aPlayer.aModel[nCntModel].vtxMinModel.y)
		{
			g_aPlayer.vtxMin.y = g_aPlayer.aModel[nCntModel].vtxMaxModel.y;
		}

		if (g_aPlayer.vtxMax.z < g_aPlayer.aModel[nCntModel].vtxMaxModel.z)
		{
			g_aPlayer.vtxMax.z = g_aPlayer.aModel[nCntModel].vtxMaxModel.z;
		}
		else if (g_aPlayer.vtxMin.z > g_aPlayer.aModel[nCntModel].vtxMinModel.z)
		{
			g_aPlayer.vtxMin.x = g_aPlayer.aModel[nCntModel].vtxMaxModel.z;
		}
	}
	//==================================================================================

	//==============================
	//�v���C���[�̃T�C�Y�����߂�
	//==============================

	g_aPlayer.Size = g_aPlayer.vtxMax - g_aPlayer.vtxMin;

}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_nNumPlayerModel; nCnt++)
	{
		//���b�V���̔j��
		if (g_aPlayer.aModel[nCnt].pMesh != NULL)
		{
			g_aPlayer.aModel[nCnt].pMesh->Release();
			g_aPlayer.aModel[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_aPlayer.aModel[nCnt].pBuffMat != NULL)
		{
			g_aPlayer.aModel[nCnt].pBuffMat->Release();
			g_aPlayer.aModel[nCnt].pBuffMat = NULL;
		}
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdatePlayer(void)
{
	g_nDelay++;//�f�B���C�J�E���g
	g_aPlayer.bIsLanding = false;
	g_aPlayer.nState = PLAYERSTATE_NUTORAL;//�������Ă��Ȃ��ꍇ�A�����I�Ƀj���[�g������ԂɂȂ�B

	//=======================================
	//�n�ʂƂ̔���
	//=======================================

	//���f��
	g_aPlayer.bIsLanding = bCollisionModel(&g_aPlayer.pos, &g_aPlayer.posOld, &g_aPlayer.move,g_aPlayer.Size);

	//�n��
	if (g_aPlayer.pos.y <= 0.0f)
	{
		g_aPlayer.bIsLanding = true;
		g_aPlayer.pos.y = 0.0f;
	}
	//================================================================================================================================================

	//=======================================
	//�d�͂̏���
	//=======================================
	if (g_aPlayer.bIsLanding == false)
	{//�n�ʂɂ��Ȃ�������
		g_aPlayer.move.y += -1.2f;
	}
	else
	{//�n�ʂɂ�����
		g_aPlayer.move.y = 0.0f;
	}

	//================================================================================================================================================

	//�v���C���[��i�ړ�����
	ControlPlayer();

	//�v���C���[�̍U������
	AttackPlayer();

	if (g_aPlayer.bMotionFlag == true)
	{//���[�V���������t���O���I���ɂȂ�����
		g_aPlayer.nState = PLAYERSTATE_ATTACK;
	}

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_aPlayer.nIdxShadow, g_aPlayer.pos,-1,-1,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.rot.y, g_aPlayer.rot.x, g_aPlayer.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aPlayer.pos.x, g_aPlayer.pos.y, g_aPlayer.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//=========================================
	//���f���p�[�c�̕`�揈��
	//=========================================
	for (int nCntPlayerParts = 0; nCntPlayerParts < g_nNumPlayerModel; nCntPlayerParts++)
	{
		if (g_aPlayer.aModel[nCntPlayerParts].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aPlayer.aModel[nCntPlayerParts].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.aModel[nCntPlayerParts].rot.y, g_aPlayer.aModel[nCntPlayerParts].rot.x, g_aPlayer.aModel[nCntPlayerParts].rot.z);

			D3DXMatrixMultiply(&g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer.aModel[nCntPlayerParts].pos.x, g_aPlayer.aModel[nCntPlayerParts].pos.y, g_aPlayer.aModel[nCntPlayerParts].pos.z);
			D3DXMatrixMultiply(&g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &mtxTrans);

			//===================================================
			//�����̃��f���̃}�g���b�N�X�Ƃ̊|���Z
			//===================================================
			D3DXMATRIX mtxParent;

			//D3DXMatrixMultiply(&g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &mtxTrans);

			if (g_aPlayer.aModel[nCntPlayerParts].nIdxModelParent == -1)
			{
				mtxParent = g_mtxWorldPlayer;//�e���N�_�Ƃ��ē����̂ŁA�}�g���b�N�X�̓v���C���[
			}
			else
			{//mtxParent�����̃��f���̐e�̃}�g���b�N�X���[���h�ɂ���
				int nData = g_aPlayer.aModel[nCntPlayerParts].nIdxModelParent;
			    
         		mtxParent = g_aPlayer.aModel[nData].mtxWorld;
			}

			D3DXMatrixMultiply(&g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &g_aPlayer.aModel[nCntPlayerParts].mtxWorld, &mtxParent);


			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aPlayer.aModel[nCntPlayerParts].mtxWorld);

		    //===============================================================================================================================


			pDevice->GetMaterial(&matDef);

			//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
			pMat = (D3DXMATERIAL*)g_aPlayer.aModel[nCntPlayerParts].pBuffMat->GetBufferPointer();

			//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
			for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aModel[nCntPlayerParts].dwNumMatPlayer; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL/*g_aPlayerPartsMat[nCntPlayerPartsSet].apTexturePlayerParts*/);

				//���f���i�p�[�c�j�̕`��
				g_aPlayer.aModel[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}


//======================================
//�v���C���[�̑���
//======================================
void ControlPlayer(void)
{
	//==================================
	//�擾�������
	//==================================
	Camera* pCamera = GetCamera();

	//=============================================================================
	//�ʏ�J�������[�h�ł̃v���C���[�̓�����
	//=============================================================================
	if (pCamera->nMode == CAMERAMODE_REVOLUTION)
	{
		float fMoveX = 0.0f; //X�����̓���
		float fMoveZ = 0.0f; //Y�����̓���
		bool bMove = false;  //�����Ă��邩
		if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_UP))
		{
			fMoveZ = 1.0f;
		}
		else if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_DOWN))
		{
			fMoveZ = -1.0f;
		}

		if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
		{
			fMoveX = 1.0f;
		}
		else if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
		{
			fMoveX = -1.0f;
		}

		//============================
		// �ړ��{�^���������Ă�����
		//============================
		if (fMoveX != 0.0f || fMoveZ != 0.0f)
		{
			bMove = true;//�ړ����
		}
		else
		{
			bMove = false;//�ҋ@���
		}

		//=====================================================================================================================


		//============================================
		//�ړ��ʂ̔��f
		//============================================

		if (bMove == true)
		{
			g_aPlayer.move.x = sinf(atan2f(fMoveX, fMoveZ) + pCamera->rot.y) * PLAYER_SPEED;
			g_aPlayer.move.z = cosf(atan2f(fMoveX, fMoveZ) + pCamera->rot.y) * PLAYER_SPEED;
		}
		if (g_aPlayer.bIsLanding == true)
		{//�n�ʂɗ����Ă�����W�����v����
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadTrigger(JOYKEY_A) == true)
			{
				g_aPlayer.move.y = 20.0f;
			}
		}

		//============================
		//�ړ��ʂ̌���
		//============================
		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * 0.5f;
		g_aPlayer.move.z += (0.0f - g_aPlayer.move.z) * 0.5f;
		g_aPlayer.posOld = g_aPlayer.pos;
		g_aPlayer.pos += g_aPlayer.move;


		//============================
        //�����̔��f
		//============================
		g_aPlayer.targetrot.y = atan2f(fMoveX, fMoveZ) + pCamera->rot.y + D3DX_PI;

		g_aPlayer.rot.y += ((g_aPlayer.targetrot.y) - g_aPlayer.rot.y) * 0.5f;

		//===================================================================================================================================
	}
}

//=======================================================================================================================================================


//===================================
//�v���C���[�̍U������
//===================================
void AttackPlayer(void)
{
	//============================
	//�ʏ�U��
	//============================

	if (GetKeyboardPress(DIK_K) == true || GetJoypadPress(JOYKEY_X) == true)
	{//�o���b�g�U��
		SetBullet(0, 200, 20.0f, 20.0f,
			D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + 20.0f, g_aPlayer.pos.z), D3DXVECTOR3(sinf(g_aPlayer.rot.y + D3DX_PI) * 10.0f, 0.0f, cosf(g_aPlayer.rot.y + D3DX_PI) * 10.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, -1.0f);
	}

	if (GetKeyboardTrigger(DIK_K) == true || GetJoyPadTrigger(JOYKEY_X) == true)
	{//�X���b�V���U��
		PlaySound(SOUND_LABEL_SE_SLASH_000);
		SetAttackBillBoard(A_BILLBOARDTYPE_SLASH, 30, 50, 20, 
			D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + g_aPlayer.Size.y / 2, g_aPlayer.pos.z), 
			NULL_VECTOR3, 
			NULL_VECTOR3);
	}

	//=========================================================================================================================================================================================================================

	//============================
	//�X�L���U��
	//============================

	SkillGage* pSKillGage = GetSkillGage(); //�X�L���Q�[�W�̍\���̂��擾
	Skill* pSkill = GetSkill();             //�X�L���̍\���̂̏����擾

	if (pSKillGage->fSkillGage >= 50.0f && pSkill->nSkillType == SKILLTYPE_FIRETORNADO)
	{//�X�L���O�F�t�@�C�A�g���l�[�h
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_008);//���ʉ�
			g_aPlayer.bMotionFlag = true;            //���[�V����
			pSKillGage->fSkillGage -= 50.0f;         //�X�L���Q�[�W�����
			SetAttackModel(g_aPlayer.pos, g_aPlayer.rot, D3DXVECTOR3(sinf(g_aPlayer.rot.y + D3DX_PI) * 10.0f, 0.0f, cosf(g_aPlayer.rot.y + D3DX_PI) * 10.0f), ATTACKMODELTYPE_FIRETORNADO, 300);
		}
	}
	else if (pSKillGage->fSkillGage >= 100.0f && pSkill->nSkillType == SKILLTYPE_THUNDERBURST)
	{//�X�L���P�F�T���_�[�o�[�X�g
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_THUNDER);//���ʉ�
			g_aPlayer.bMotionFlag = true;     //���[�V����
			pSKillGage->fSkillGage -= 100.0f; //�X�L���Q�[�W�����
			SetAttackBillBoard(A_BILLBOARDTYPE_THUNDER, 500, 50.0f, 500.0f, D3DXVECTOR3(g_aPlayer.pos.x + sinf(g_aPlayer.rot.y + D3DX_PI) * 200.0f, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf(g_aPlayer.rot.y + D3DX_PI) * 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAttackBillBoard(A_BILLBOARDTYPE_THUNDER, 500, 50.0f, 500.0f, D3DXVECTOR3(g_aPlayer.pos.x + sinf(g_aPlayer.rot.y + D3DX_PI + D3DX_PI * 0.5f) * 200.0f, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf(g_aPlayer.rot.y + D3DX_PI + D3DX_PI * 0.5f) * 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAttackBillBoard(A_BILLBOARDTYPE_THUNDER, 500, 50.0f, 500.0f, D3DXVECTOR3(g_aPlayer.pos.x + sinf(g_aPlayer.rot.y) * 200.0f, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf(g_aPlayer.rot.y) * 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAttackBillBoard(A_BILLBOARDTYPE_THUNDER, 500, 50.0f, 500.0f, D3DXVECTOR3(g_aPlayer.pos.x + sinf(g_aPlayer.rot.y + D3DX_PI - D3DX_PI * 0.5f) * 200.0f, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf(g_aPlayer.rot.y + D3DX_PI - D3DX_PI * 0.5f) * 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	else if (pSKillGage->fSkillGage >= 200.0f && pSkill->nSkillType == SKILLTYPE_METEOBALL)
	{//�X�L���Q�F���e�I�{�[��
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_EXPLOSION_ENEMY_000);//���ʉ�
			g_aPlayer.bMotionFlag = true;                 //���[�V����
			pSKillGage->fSkillGage -= 200.0f;             //�X�L���Q�[�W�����
			SetAttackModel(D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + 500.0f, g_aPlayer.pos.z - 200.0f), g_aPlayer.rot, D3DXVECTOR3(sinf(g_aPlayer.rot.y + D3DX_PI) * 10.0f, -10.0f, cosf(g_aPlayer.rot.y + D3DX_PI) * 10.0f), ATTACKMODELTYPE_METEOBALL, 500);
		}
	}
	else if (pSKillGage->fSkillGage >= 150.0f && pSkill->nSkillType == SKILLTYPE_KILLNEEDLE)
	{//�X�L���R�F�L���j�[�h��
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_ICICLECLAW);//���ʉ�
			g_aPlayer.bMotionFlag = true;        //���[�V����
			pSKillGage->fSkillGage -= 150.0f;    //�X�L���Q�[�W�����
			for (int nCnt = 0; nCnt < 16; nCnt++)
			{
				float fRot = (2.0f / 16) * nCnt;
				SetAttackModel(D3DXVECTOR3(g_aPlayer.pos.x + sinf(g_aPlayer.rot.y + D3DX_PI * fRot) * 200.0f, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf(g_aPlayer.rot.y + D3DX_PI * fRot) * 200.0f), g_aPlayer.rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ATTACKMODELTYPE_KILLNEEDLE, 900);
			}
		}
	}
	else if (pSKillGage->fSkillGage >= 300.0f && pSkill->nSkillType == SKILLTYPE_CHAINFIRE)
	{//�X�L���S�F�`�F�C���t�@�C�A
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_PUNCH);  //���ʉ�
			g_aPlayer.bMotionFlag = true;     //���[�V����
			pSKillGage->fSkillGage -= 300.0f; //�X�L���Q�[�W�����
			for (int nCnt = 0; nCnt < 9; nCnt++)
			{
				SetBullet(BULLETTYPE_FIRE, 300, 15.0f, 15.0f,
					D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + g_aPlayer.Size.y / 2, g_aPlayer.pos.z), D3DXVECTOR3(sinf(g_aPlayer.rot.y + D3DX_PI - 0.4f + (nCnt * 0.1f)) * 12.0f, 0.0f, cosf(g_aPlayer.rot.y + D3DX_PI - 0.3f + (nCnt * 0.1f)) * 12.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, -1.0f);
			}
		}
	}
	else if (pSKillGage->fSkillGage >= 1000.0f && pSkill->nSkillType == SKILLTYPE_ATOMICSLASH)
	{//�X�L���T�F�A�g�~�b�N�X���b�V��
		if (GetKeyboardTrigger(DIK_M) == true || GetJoyPadTrigger(JOYKEY_B) == true)
		{
			PlaySound(SOUND_LABEL_SE_FLASHBLADE); //���ʉ�
			g_aPlayer.bMotionFlag = true;         //���[�V����
			pSKillGage->fSkillGage -= 1000.0f;    //�X�L���Q�[�W�����

			g_aPlayer.bSpecialAttackFlag = true;//�X�y�V�����A�^�b�N�𔭓�����B
		}
	}

	//====================================
	//�X�y�V�����A�^�b�N��������
	//====================================
	if (g_aPlayer.bSpecialAttackFlag == true)
	{
		g_aPlayer.nSpecialAttackCount++;//�X�y�V�����A�^�b�N�g�p���Ԃ��J�E���g����
		float fRandumRot = float(rand() % 200 + 1) / 100;
		float fRandumSpeed = float(rand() % 100 + 30) / 10;
		float fRandumMove = float(rand() % 21 - 10);
		float fRandumLength = float(rand() % 500);
		float fRandumPos = float(rand() % 1000 - 500);


		SetAttackBillBoard(A_BILLBOARDTYPE_ATOMICSLASH, 120, 100.0f, 35.0f,
			D3DXVECTOR3(g_aPlayer.pos.x + sinf(-D3DX_PI * fRandumRot) * fRandumLength, g_aPlayer.pos.y + fRandumPos, g_aPlayer.pos.z + cosf(-D3DX_PI * fRandumRot) * fRandumLength),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		if (g_aPlayer.nSpecialAttackCount == 900)
		{
			g_aPlayer.nSpecialAttackCount = 0;
			g_aPlayer.bSpecialAttackFlag = false;
		}
	}
	//===============================================================================================================================================

}

//=======================================================================================================================================================


Player* GetPlayer(void)
{
	return &g_aPlayer;
}


void SetPlayerParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx, int nType)
{
	for (int nCntPlayerParts = 0; nCntPlayerParts < MAX_PLAYERPARTS; nCntPlayerParts++)
	{
		if (g_aPlayer.aModel[nCntPlayerParts].bUse == false)
		{
			g_aPlayer.aModel[nCntPlayerParts].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aPlayer.aModel[nCntPlayerParts].pos = pos;//�ʒu
			g_aPlayer.aModel[nCntPlayerParts].SavePos = pos;//�ʒu
			g_aPlayer.aModel[nCntPlayerParts].rot = rot;//����
			g_aPlayer.aModel[nCntPlayerParts].SaveRot = rot;//����
			g_aPlayer.aModel[nCntPlayerParts].nIdxModelParent = nIdx;
			g_aPlayer.aModel[nCntPlayerParts].nType = nType;
			break;
		}
	}
}

void SetDamagePlayer(int nDamage)
{
	PlaySound(SOUND_LABEL_SE_DAMAGE_000);
	g_aPlayer.nHp -= nDamage;
	ResetCombo();
}

bool bPlayerDeath(void)//�v���C���[�����񂾂��ǂ����̔����Ԃ�
{
	bool bDeath = false;

	if (g_aPlayer.nHp <= 0)
	{
		bDeath = true;
		g_aPlayer.bUse = false;
	}
	return bDeath;
}


