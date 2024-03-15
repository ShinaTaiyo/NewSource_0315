//========================================================
//
//�P�P���V���F���f���ǂݍ���[EditEnemy.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "editEnemy.h"
#include "model.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include "enemy.h"
#include "edit.h"
#include "timer.h"
#include "summon.h"
#include "camera.h"
#include "debugproc.h"
//�O���[�o���ϐ�
#define ENEMYEDITOR_SPEED (5.0f)//�G�G�f�B�^�̑���
#define EditEnemy_SCALE (10.0f)
#define EditEnemySET "data\\TEXTFILE\\EditEnemy.txt"
#define SAVEEditEnemy "data\\TEXTFILE\\SaveEditEnemy.txt"
#define SAVEENEMY "data\\TEXTFILE\\SaveEnemy.txt"


EnemyEditor g_aEnemyEditor;
EnemyEditorModelInfo g_aEnemyEditorModelInfo;
EditEnemy g_aEditEnemy[MAX_ENEMY];//�Z�b�g�����G�̏��
int g_nEditTime;//�������鎞�Ԃ��G�f�B�b�g����B

//�^�C�g����ʂ̏���������
void InitEnemyEditor(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	g_aEnemyEditorModelInfo.dwNumMat = {};
	g_aEnemyEditorModelInfo.pBuffMat = {};
	g_aEnemyEditorModelInfo.pMesh = {};

	//==============================
	//���f�����̎擾
	//==============================
	D3DXLoadMeshFromX("data\\MODEL\\Cube_000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aEnemyEditorModelInfo.pBuffMat,
		NULL,
		&g_aEnemyEditorModelInfo.dwNumMat,
		&g_aEnemyEditorModelInfo.pMesh);

	//=================================================================================

	//===========================
	//������
	//===========================
	g_aEnemyEditor.bUse = true;//�g�p���
	g_aEnemyEditor.mtxWorld = {};//�}�g���b�N�X���[���h
	g_aEnemyEditor.nIdxShadow = -1;//�e�̃C���f�b�N�X
	g_aEnemyEditor.nSummonTime = 180;//�������鎞��
	g_aEnemyEditor.nType = 0;//�Z�b�g����G�̎��
	g_aEnemyEditor.pos = NULL_VECTOR3;//�ʒu
	g_aEnemyEditor.rot = NULL_VECTOR3;//����
	g_aEnemyEditor.nNumSetEnemy = -1;//���Ԗڂ̓G���Z�b�g���Ă��邩
	g_aEnemyEditor.targetrot = NULL_VECTOR3;
	//==================================================

	//=======================================
	//�Z�b�g�����G�̏��̏�����
	//=======================================

	for (int nCntEdit = 0; nCntEdit < MAX_EDITENEMY; nCntEdit++)
	{
		g_aEditEnemy[nCntEdit].bUse = false;//�g�p���
		g_aEditEnemy[nCntEdit].mtxWorld = {};//�}�g���b�N�X���[���h
		g_aEditEnemy[nCntEdit].nIdxShadow = -1;//�e�̃C���f�b�N�X
		g_aEditEnemy[nCntEdit].nSummonTime = 0;//�������鎞��
		g_aEditEnemy[nCntEdit].nType = 0;//�Z�b�g����G�̎��
		g_aEditEnemy[nCntEdit].pos = NULL_VECTOR3;//�ʒu
		g_aEditEnemy[nCntEdit].rot = NULL_VECTOR3;//����
		g_aEditEnemy[nCntEdit].nNumEnemy = 0;//���Ԗڂ̃Z�b�g���ꂽ�G��
	}
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitEnemyEditor(void)
{

	//���b�V���̔j��
	if (g_aEnemyEditorModelInfo.pMesh != NULL)
	{
		g_aEnemyEditorModelInfo.pMesh->Release();
		g_aEnemyEditorModelInfo.pMesh = NULL;
	}
	//�}�e���A���̔j��
	if (g_aEnemyEditorModelInfo.pBuffMat != NULL)
	{
		g_aEnemyEditorModelInfo.pBuffMat->Release();
		g_aEnemyEditorModelInfo.pBuffMat = NULL;
	}
	
}
//============================
//���f���̍X�V����
//============================
void UpdateEnemyEditor(void)
{
	Player* pPlayer = GetPlayer();
	Edit* pEdit = GetEdit();
	Camera* pCamera = GetCamera();
	
	//=================================
	//��������G�̎�ނ����߂�
	//=================================

		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			g_aEnemyEditor.nType++;
		}
		else if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_aEnemyEditor.nType--;
		}

		if (g_aEnemyEditor.nType <= -1)
		{
			g_aEnemyEditor.nType = NUM_ENEMY - 1;
		}
		else if (g_aEnemyEditor.nType >= NUM_ENEMY)
		{
			g_aEnemyEditor.nType = 0;
		}

		//==================================
		//�������鎞�Ԃ�錾����B
		//==================================

		if (GetKeyboardTrigger(DIK_6) == true)
		{
			g_aEnemyEditor.nSummonTime--;
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			if (GetKeyboardTrigger(DIK_6) == true)
			{
				g_aEnemyEditor.nSummonTime -= 5;
			}
		}
		if (GetKeyboardTrigger(DIK_7) == true)
		{
			g_aEnemyEditor.nSummonTime++;
		}
		else if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			if (GetKeyboardTrigger(DIK_6) == true)
			{
				g_aEnemyEditor.nSummonTime += 5;
			}
		}


		//=====================================================================================================================================


		//===========================================
		//�ړ�����
		//===========================================

		bool bMove = false;

		float X = 0.0f;
		float Z = 0.0f;
		if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{
			Z = 1.0f;
			bMove = true;
		}
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{
			Z = -1.0f;
			bMove = true;
		}

		if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			X = 1.0f;
			bMove = true;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{
			X = -1.0f;
			bMove = true;
		}
	
		if (bMove == true)
		{
			g_aEnemyEditor.pos.x += sinf(atan2f(X, Z) + pCamera->rot.y) * ENEMYEDITOR_SPEED;
			g_aEnemyEditor.pos.z += cosf(atan2f(X, Z) + pCamera->rot.y) * ENEMYEDITOR_SPEED;


			g_aEnemyEditor.targetrot.y = atan2f(X, Z) + pCamera->rot.y + D3DX_PI;


		}

		g_aEnemyEditor.rot.y += ((g_aEnemyEditor.targetrot.y) - g_aEnemyEditor.rot.y) * 0.5f;

		//======================================================================================================================


		//=======================================
		//�G���Z�b�g����
		//=======================================
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetEditEnemy(g_aEnemyEditor.pos, g_aEnemyEditor.rot, g_aEnemyEditor.nType,g_aEnemyEditor.nSummonTime);//�G�G�f�B�^�Ŕz�u�����ʒu��ۑ�
		}

		//=======================================
		//�Z�b�g�����G��j������
		//=======================================
		if (GetKeyboardTrigger(DIK_DELETE) == true)
		{
			g_aEditEnemy[g_aEnemyEditor.nNumSetEnemy].bUse = true;//�g�p���
			g_aEditEnemy[g_aEnemyEditor.nNumSetEnemy].nType = -1;//���
			g_aEditEnemy[g_aEnemyEditor.nNumSetEnemy].pos = NULL_VECTOR3;//�ʒu
			g_aEditEnemy[g_aEnemyEditor.nNumSetEnemy].rot = NULL_VECTOR3;//����

			Summon* pSummon = GetSummon();

			for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++, pSummon++)
			{
				if (pSummon->bUse == true && pSummon->nNumSetEdit == g_aEnemyEditor.nNumSetEnemy)
				{//���������G������
					pSummon->bUse = false;
			        g_aEnemyEditor.nNumSetEnemy--;
					break;
				}

			}
		}


		//==============================================================================================================================


		//=================================================
		//�e�L�X�g�t�@�C���ɏ�����������ۑ�
		//=================================================
		if (GetKeyboardTrigger(DIK_F10) == true)
		{

			FILE* pFile;//�t�@�C���|�C���^��錾
			pFile = fopen(SAVEEditEnemy, "w");//�t�@�C���ɍ���z�u�������f�����������o��

			if (pFile != NULL)//�t�@�C�����J���Ă�����
			{//���Z�b�g���̓G�̑O�̔ԍ��܂ł�ۑ�
				for (int nCntSaveModel = 0; nCntSaveModel < g_aEnemyEditor.nNumSetEnemy; nCntSaveModel++)
				{
					fprintf(pFile, "SUMMONSET\n");
					fprintf(pFile, "TYPE %d\n", g_aEditEnemy[nCntSaveModel].nType);//�ݒu�������f���̎�ނ������o��
					fprintf(pFile, "POS %.3f  %.3f  %.3f\n", g_aEditEnemy[nCntSaveModel].pos.x
						, g_aEditEnemy[nCntSaveModel].pos.y, g_aEditEnemy[nCntSaveModel].pos.z);//�ݒu�������f���̈ʒu�������o��
					fprintf(pFile, "ROT %.3f  %.3f  %.3f\n", g_aEditEnemy[nCntSaveModel].rot.x
						, g_aEditEnemy[nCntSaveModel].rot.y, g_aEditEnemy[nCntSaveModel].rot.z);//�ݒu�������f���̌����������o��
					fprintf(pFile, "TIME %d\n",g_aEditEnemy[nCntSaveModel].nSummonTime);//�������Ԃ������o���B
					fprintf(pFile, "ENDSUMMONSET\n");
					fprintf(pFile, "\n");
				}
				fclose(pFile);
			}


			//=====================================================
			//�ۑ����I������̂ŁA���������G��ҏW�s�ɂ���
			//=====================================================

			Summon* pSummon = GetSummon();
			for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++, pSummon++)
			{
				if (pSummon->bRemote == true)
				{
					if (pSummon->nNumSetEdit >= 0 && pSummon->nNumSetEdit <= g_aEnemyEditor.nNumSetEnemy)
					{
						pSummon->nNumSetEdit = -1;
						pSummon->bRemote = false;
					}
				}
			}

			//======================================================================================================

			g_aEnemyEditor.nNumSetEnemy = -1;//�Z�b�g���I������̂ŁA�Z�b�g���Ă���ԍ����[�P�ɖ߂��B
		}

		//================================================================================================================================
     

		if (g_aEnemyEditor.nNumSetEnemy <= -2)
		{
			g_aEnemyEditor.nNumSetEnemy = -1;
		}

		//==============================
		//�G�f�B�^�[�̏��
		//==============================
		PrintDebugProc("//==================================\n");
		PrintDebugProc("//�G�G�f�B�^�̑�����@\n");
		PrintDebugProc("//==================================\n");
		PrintDebugProc("�ړ��FWASD\n");
		PrintDebugProc("�z�u����G�̎�ނ�ς���F���@��\n");
		PrintDebugProc("�������鎞�Ԃ��P�b�ς���iSHIFT�������Ȃ��炾��5�b)�F�U�@�V\n");
		PrintDebugProc("�z�u�����G�̏���ۑ�����:F10\n");
		PrintDebugProc("//====================================================================\n\n");


		PrintDebugProc("//==================================\n");
		PrintDebugProc("//�G�G�f�B�^�̏��\n");
		PrintDebugProc("//==================================\n");
		PrintDebugProc("�G�G�f�B�^�̈ʒu�F%f %f %f\n", g_aEnemyEditor.pos.x, g_aEnemyEditor.pos.y, g_aEnemyEditor.pos.z);
		PrintDebugProc("�G�G�f�B�^�̌����F%f %f %f\n", g_aEnemyEditor.rot.x, g_aEnemyEditor.rot.y, g_aEnemyEditor.rot.z);
		PrintDebugProc("�Z�b�g����G�̎�ށF%d\n", g_aEnemyEditor.nType);
		PrintDebugProc("�G���������鎞�ԁF%d\n", g_aEnemyEditor.nSummonTime);
		PrintDebugProc("���Ԗڂ̓G���Z�b�g���Ă��邩�F%d\n\n", g_aEnemyEditor.nNumSetEnemy);
		PrintDebugProc("//====================================================================\n");

		//====================================================================================================================

}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawEnemyEditor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^


	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (g_aEnemyEditor.bUse == true)
	{

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aEnemyEditor.mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemyEditor.rot.y, g_aEnemyEditor.rot.x, g_aEnemyEditor.rot.z);

		D3DXMatrixMultiply(&g_aEnemyEditor.mtxWorld, &g_aEnemyEditor.mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aEnemyEditor.pos.x, g_aEnemyEditor.pos.y, g_aEnemyEditor.pos.z);
		D3DXMatrixMultiply(&g_aEnemyEditor.mtxWorld, &g_aEnemyEditor.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyEditor.mtxWorld);


		//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
		pMat = (D3DXMATERIAL*)g_aEnemyEditorModelInfo.pBuffMat->GetBufferPointer();

		int nNumTexture = 0;
		//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
		for (int nCntMat = 0; nCntMat < (int)g_aEnemyEditorModelInfo.dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,NULL);
			nNumTexture++;
			
			//���f���i�p�[�c�j�̕`��
			g_aEnemyEditorModelInfo.pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
	
}

//=================================
//�z�u����G�̏����Z�b�g����
//=================================
void SetEditEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nTime)
{
	Player* pPlayer = GetPlayer();

	for (int nCntEdit = 0; nCntEdit < MAX_EDITENEMY; nCntEdit++)
	{
		if (g_aEditEnemy[nCntEdit].bUse == false)
		{
			g_aEnemyEditor.nNumSetEnemy++;//���̖ڂɃZ�b�g������
			SetSummon(g_aEnemyEditor.nType, g_aEnemyEditor.nSummonTime, g_aEnemyEditor.nNumSetEnemy,true,g_aEnemyEditor.pos, g_aEnemyEditor.rot);//�G��������ݒ�

			g_aEditEnemy[nCntEdit].bUse = true;//�g�p���
			g_aEditEnemy[nCntEdit].nType = nType;//���
			g_aEditEnemy[nCntEdit].pos = pos;//�ʒu
			g_aEditEnemy[nCntEdit].rot = rot;//����
			g_aEditEnemy[nCntEdit].nSummonTime = nTime;//�������鎞��
			break;
		}
	}	
}

int GetEditTime(void)//�G�̏������Ԃ����߂�ϐ����擾����B
{
	return g_nEditTime;
}

//==================================
//�\���̂̏����擾
//==================================
EnemyEditor* GetEnemyEditor(void)
{
	return &g_aEnemyEditor;
}
//========================================================
