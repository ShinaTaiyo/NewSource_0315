//========================================================
//
//�P�P���V���F���f���ǂݍ���[Summon.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "Summon.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include "model.h"
#include "score.h"
#include "bullet.h"
#include "combo.h"
#include "timer.h"
#include "enemy.h"
#include "game.h"
#include "editEnemy.h"
//�O���[�o���ϐ�
int g_nDelaySummon = 0;
float g_fRandumRot = 0;
float g_fRandumLength = 0;
float g_fRandumPos = 0;
int g_nType = 0;

int g_nMaxSummon;//��������G�̍ő吔

Summon g_aSummon[MAX_SUMMON];//�G�����\����
SummonModelInfo g_aSummonModelInfo[NUM_ENEMY];

//�^�C�g����ʂ̏���������
void InitSummon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾


	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	g_nDelaySummon = 0;
	g_fRandumRot = 0;
	g_fRandumLength = 0;
	g_fRandumPos = 0;
	g_nType = 0;
	g_nMaxSummon = 0;

	for (int nCntModelInfo = 0; nCntModelInfo < NUM_ENEMY; nCntModelInfo++)
	{
		g_aSummonModelInfo[nCntModelInfo].dwNumMat = {};
		g_aSummonModelInfo[nCntModelInfo].pBuffMat = {};
		g_aSummonModelInfo[nCntModelInfo].pMesh = {};
	}

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		g_aSummon[nCntSummon].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aSummon[nCntSummon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aSummon[nCntSummon].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aSummon[nCntSummon].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aSummon[nCntSummon].nType = 0;//��������G�̎��
		g_aSummon[nCntSummon].nSummonTime = 0;//�G���������鎞��
		g_aSummon[nCntSummon].mtxWorld;//�}�g���b�N�X���[���h
		g_aSummon[nCntSummon].nNumSetEdit = -1;//�G�f�B�^�[�ŃZ�b�g���ꂽ�G�̔ԍ�
		g_aSummon[nCntSummon].bRemote = false;//���u����̕ύX���󂯂邩�ǂ���

		for (int nCntModelInfo = 0; nCntModelInfo < NUM_ENEMY; nCntModelInfo++)
		{
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].dwNumMat = {};
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].pBuffMat = {};
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].pMesh = {};

			for (int nCntMat = 0; nCntMat < MAX_SUMMONMAT; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].Diffuse[nCntMat] = {};
			}
		}
	}



	for (int nCntType = 0; nCntType < NUM_ENEMY; nCntType++)
	{
		D3DXLoadMeshFromX(ENEMY_FILENAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aSummonModelInfo[nCntType].pBuffMat,//���f���ł́A������z��ɂ���
			NULL,
			&g_aSummonModelInfo[nCntType].dwNumMat,//���f���ł́A������z��ɂ���
			&g_aSummonModelInfo[nCntType].pMesh);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aSummonModelInfo[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_aSummonModelInfo[nCntType].dwNumMat; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nCntType].Diffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
				g_aSummon[nCntSummon].SummonModelInfo[nCntType].FormarDiffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;//���̐F����
			}
		}
	}
	


	char aString[100] = {};//�������ǂݍ��ނ��߂̕ϐ�
	int nMaxRoadEnemy = 0;//�ǂݍ��ރ��f���̍ő吔
	int nType = 0;//�ǂݍ��񂾃��f���̎��

	float fPosX = 0.0f;//���f���̈ʒuX
	float fPosY = 0.0f;//���f���̈ʒuY
	float fPosZ = 0.0f;//���f���̈ʒuZ

	float fRotX = 0.0f;//���f���̈ʒuX
	float fRotY = 0.0f;//���f���̈ʒuY
	float fRotZ = 0.0f;//���f���̈ʒuZ
	int nCnt = 0;//�ǂݍ��ރ��f���𐔂���p

	int nSummonTime = 0;//�������鎞�Ԃ�錾����
	FILE* pFile;//�t�@�C���|�C���^

	char aStringPass[100] = {};

	pFile = fopen(SUMMONSET, "r");
	
	if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);
			if (aString[0] == '#')
			{
				fgets(&aString[0], 100, pFile);
				continue;
			}
			if (strcmp(&aString[0], "ENDSCRIPT") == 0)
			{
				fclose(pFile);
				break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
			}
			else if (strcmp(&aString[0], "SUMMONSET") == 0)
			{
				g_nMaxSummon++;//�G����������ő吔���C���N�������g����
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);
					if (aString[0] == '#')
					{
						fgets(&aString[0], 100, pFile);
						continue;
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
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
					else if (strcmp(&aString[0], "TIME") == 0)
					{
						fscanf(pFile,"%d",&nSummonTime);//�������鎞�Ԃ�ǂݍ��ށB
					}
					else if (strcmp(&aString[0], "ENDSUMMONSET") == 0)
					{//�������ŃZ�b�g���ꂽ�f�[�^�́A���ɂ���f�[�^�Ȃ̂ŁA�G�f�B�^�̔z�u�ɂ̓J�E���g���Ȃ�
						SetSummon(nType,nSummonTime,-1,false,D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(fRotX, fRotY, fRotZ));
						break;
					}
				}
			}
		}
	}
}

void UninitSummon(void)
{
	for (int nCntSummon = 0; nCntSummon < NUM_ENEMY; nCntSummon++)
	{
		//���b�V���̔j��
		if (g_aSummonModelInfo[nCntSummon].pMesh != NULL)
		{
			g_aSummonModelInfo[nCntSummon].pMesh->Release();
			g_aSummonModelInfo[nCntSummon].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_aSummonModelInfo[nCntSummon].pBuffMat != NULL)
		{
			g_aSummonModelInfo[nCntSummon].pBuffMat->Release();
			g_aSummonModelInfo[nCntSummon].pBuffMat = NULL;
		}
	}
}

//============================
//���f���̍X�V����
//============================
void UpdateSummon(void)
{
	Player* pPlayer = GetPlayer();

	g_nDelaySummon++;

	g_fRandumRot = float(rand() % 200 + 1) / 100;
	int nGetTimer = GetTimer();//�c�莞�Ԃ̎擾
	int nLottery = rand() % 1001 + 1;//��������G�𒊑I����

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].bUse == true && g_aSummon[nCntSummon].nSummonTime == nGetTimer)//�g�p���Ă��邩�A�������Ԃ���v������
		{
			SetEnemy(g_aSummon[nCntSummon].pos, g_aSummon[nCntSummon].rot, g_aSummon[nCntSummon].nType);
			g_aSummon[nCntSummon].bUse = false;//��񏢊������̂ŗp�ς�
		}
	}
	

	if (150 <= nGetTimer && nGetTimer <= 180)//�J�n�R�O�b
	{
		if (g_nDelaySummon % 20 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu
			
			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//70%�̊m���ŁA��X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 950)
			{
				g_nType = ENEMY01_ANGRYSLIME;//7%�̊m���œ{��X���C�����o��
			}
			else if (951 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY03_HAMMERSLIME;//3%�̊m���Ńn���}�[�X���C�����o��
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (120 <= nGetTimer && nGetTimer <= 150)
	{
		if (g_nDelaySummon % 17 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 930)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (931 <= nLottery && nLottery <= 950)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (951 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (90 <= nGetTimer && nGetTimer <= 120)
	{
		if (g_nDelaySummon % 15 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (926 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (941 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (60 <= nGetTimer && nGetTimer <= 90)
	{
		if (g_nDelaySummon % 12 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 915)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (916 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (925 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (946 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (60 <= nGetTimer && nGetTimer <= 90)
	{
		if (g_nDelaySummon % 9 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 915)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (916 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (925 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (946 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (30 <= nGetTimer && nGetTimer <= 60)
	{
		if (g_nDelaySummon % 5 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 880)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (881 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (901 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (926 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (941 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (971 <= nLottery && nLottery <= 985)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (986 <= nLottery && nLottery <= 995)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (996 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (0 <= nGetTimer && nGetTimer <= 30)
	{
		if (g_nDelaySummon % 4 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//��������ʒu

			if (0 <= nLottery && nLottery <= 870)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%�̊m���ŁA��X���C�����o��
			}
			else if (871 <= nLottery && nLottery <= 875)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%�̊m���œ{��X���C�����o��
			}
			else if (876 <= nLottery && nLottery <= 880)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%�̊m���Ń\�[�h�X���C�����o��
			}
			else if (881 <= nLottery && nLottery <= 885)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%�̊m���Ńn���}�[�X���C�����o��
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%�̊m���ŃI�����W�X���C�����o��
			}
			else if (886 <= nLottery && nLottery <= 895)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (896 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (926 <= nLottery && nLottery <= 945)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (946 <= nLottery && nLottery <= 965)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (966 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY10_RAINBOWSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);
		}
	}
}

void DrawSummon(void)
{
	EnemyEditor* pEnemyEditor = GetEnemyEditor();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	bool bEditCheck = bGetEditCheck();

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].nSummonTime == pEnemyEditor->nSummonTime && g_aSummon[nCntSummon].bUse == true)
		{//�g�p��Ԃł��邩�A�������Ԃ��A�G�G�f�B�^�̏������Ԃƈ�v���Ă�����`����J�n

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aSummon[nCntSummon].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSummon[nCntSummon].rot.y, g_aSummon[nCntSummon].rot.x, g_aSummon[nCntSummon].rot.z);

			D3DXMatrixMultiply(&g_aSummon[nCntSummon].mtxWorld, &g_aSummon[nCntSummon].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aSummon[nCntSummon].pos.x, g_aSummon[nCntSummon].pos.y, g_aSummon[nCntSummon].pos.z);
			D3DXMatrixMultiply(&g_aSummon[nCntSummon].mtxWorld, &g_aSummon[nCntSummon].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSummon[nCntSummon].mtxWorld);


			//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
			pMat = (D3DXMATERIAL*)g_aSummonModelInfo[g_aSummon[nCntSummon].nType].pBuffMat->GetBufferPointer();

			int nNumTexture = 0;
			//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
			for (int nCntMat = 0; nCntMat < (int)g_aSummonModelInfo[g_aSummon[nCntSummon].nType].dwNumMat; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse = g_aSummon[nCntSummon].SummonModelInfo[g_aSummon[nCntSummon].nType].Diffuse[nCntMat];

				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		       //�e�N�X�`���̐ݒ�
		       pDevice->SetTexture(0,NULL);

				//���f���i�p�[�c�j�̕`��
				g_aSummonModelInfo[g_aSummon[nCntSummon].nType].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================
//��������G�̏��̃Z�b�g
//==============================
void SetSummon(int nType, int nTime, int nNumSetEdit, bool bRemote, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].bUse == false)
		{
			g_aSummon[nCntSummon].bUse = true;
			g_aSummon[nCntSummon].pos = pos;//�ʒu
			g_aSummon[nCntSummon].rot = rot;//����
			g_aSummon[nCntSummon].nType = nType;//��������G�̎��
			g_aSummon[nCntSummon].nSummonTime = nTime;//�G���������鎞��
			g_aSummon[nCntSummon].nNumSetEdit = nNumSetEdit;//�G�f�B�^�Ŕz�u���ꂽ�G�̔ԍ�	
			g_aSummon[nCntSummon].bRemote = bRemote;//���u����̕ύX���󂯂邩�ǂ���
			for (int nCntMat = 0; nCntMat < MAX_SUMMONMAT; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nType].Diffuse[nCntMat].a = 0.5f;//�F����
			}
			break;
		}
	}
}


//===================================
//�\���̂̏����擾
//===================================
Summon* GetSummon(void)
{
	return &g_aSummon[0];
}

//==============================================================================================================================


