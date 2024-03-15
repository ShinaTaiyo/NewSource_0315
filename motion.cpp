//========================================================
//
//�P�P���V���F���f���ǂݍ���[Motion.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "motion.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

//�O���[�o���ϐ�
int g_nNumMotion = 0;//�ǂݍ��ރ��f���̍ő吔�����߂�

int g_nUseMotion = 0;//���Ԃ̃��[�V�������g���Ă��邩

int g_nCntFrame = 0;//�t���[���̒����𑪂�
#define Motion_SCALE (10.0f)
//#define SAVEMotion "data\\TEXTFILE\\SaveMotion.txt"

#define MAX_TEXTURE (32)


typedef struct
{
	LPD3DXMESH pMeshMotion;//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
	LPD3DXBUFFER pBuffMatMotion;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMatMotion;//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 apTextureMotion[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
}MotionMat;

D3DXVECTOR3 g_posMotion;//�ʒu
D3DXVECTOR3 g_rotMotion;//����
D3DXMATRIX g_mtxWorldMotion;//���[���h�}�g���b�N�X

//Motion g_aMotion[MAX_MOTION];//���f�����̍\����

MotionMat g_aMotionMat[NUM_MOTION];//���f���̃}�e���A���Ⓒ�_�̍\����

int g_nCntKeySet;//�L�[�Z�b�g���J�E���g����

//int g_nldxShadow = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j
//bool g_bIsLanding;//�n�ʂɂ��邩�ǂ���

int g_nNowKey;//���݂̃L�[
int g_nNowMotion;//���݂̃��[�V����

//====================
//���[�V�����֘A����
//====================
MotionSet g_aMotionSet[MAX_MOTION];//���[�V�����ݒ菈��

//�^�C�g����ʂ̏���������
void InitMotion(void)
{
	//=======================
	//����������
	//=======================
	int g_nUseMotion = 0;//���Ԃ̃��[�V�������g���Ă��邩
	g_nCntKeySet = 0;//�L�[�Z�b�g���J�E���g����
	g_nCntFrame = 0;//�t���[���̒����𑪂�
	g_nNowKey = 0;
	g_nNowMotion = 0;
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		g_aMotionSet[nCntMotion].bLoop = false;//���[�v�����邩�ǂ����̃t���O
		g_aMotionSet[nCntMotion].nNumKey = 0;//�L�[�̐�
		g_aMotionSet[nCntMotion].bUse = false;//���[�V�������g�p���邩�ǂ���
		for (int nCntKeySet = 0; nCntKeySet < MAX_KEYSET; nCntKeySet++)
		{
			g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].nFrame = 0;//���̃|�[�Y�܂ł̎��Ԃ����߂�

			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
			{
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);//�ʒu
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);//����

			}
		}
	}
	//===========================================================================================================
	char aString[100];//�������ǂݍ��ނ��߂̕ϐ�
	int nMaxRoadMotion = 0;//�ǂݍ��ރ��f���̍ő吔
	int nType = 0;//�ǂݍ��񂾃��f���̎��

	float fPosX = 0.0f;//���f���̈ʒuX
	float fPosY = 0.0f;//���f���̈ʒuY
	float fPosZ = 0.0f;//���f���̈ʒuZ

	float fRotX = 0.0f;//���f���̈ʒuX
	float fRotY = 0.0f;//���f���̈ʒuY
	float fRotZ = 0.0f;//���f���̈ʒuZ
	int nCnt = 0;//�ǂݍ��ރ��f���𐔂���p
	int nIdx = 0;//�C���f�b�N�X
	int nCntMotionSet = 0;//�Z�b�g���郂�[�V�������̃J�E���g
	int nCntKeySet = 0;//�L�[�Z�b�g���̃J�E���g
	int nCntKey = 0;//�L�[���̃J�E���g
	int nRoadModel = 0;//�ǂݍ��ރ��f���̍ő吔
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾


	FILE* pFile;//�t�@�C���|�C���^
	pFile = fopen(MOTIONSET, "r");
	char aStringPass[100] = {};
	Player* pPlayer = GetPlayer();
	if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	{
		while (1)
		{

			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
			}
			else if (aString[0] == '#')
			{
				fgets(&aString[0], 100, pFile);
				continue;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)//�ǂݍ��ރ��f���̎�ސ������߂�
			{
		       fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &g_nNumMotion);
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{
				while (1)
				{
					int nLoop = 0;
					fscanf(pFile, "%s", &aString[0]);
					if (aString[0] == '#')
					{
						fgets(&aString[0], 100, pFile);
						continue;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);// =
						fscanf(pFile, "%d", &nLoop);//���[�v�����邩�ǂ����𐔒l�Ő錾����

						if (nLoop == 0)
						{
							g_aMotionSet[nCntMotionSet].bLoop = false;//���[�v���Ȃ�
						}
						else if (nLoop == 1)
						{
							g_aMotionSet[nCntMotionSet].bLoop = true;//���[�v����
						}
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//�L�[��
					{
						int nData = ~0;
						fscanf(pFile, "%s %d", &aString[0], &nData);// =
						g_aMotionSet[nCntMotionSet].nNumKey = nData;
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);// =
							if (aString[0] == '#')
							{
								fgets(&aString[0], 100, pFile);
								continue;
							}
							if (strcmp(&aString[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s %d", &aString[0], &g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].nFrame);//=,�t���[���̒l
							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (aString[0] == '#')
									{
										fgets(&aString[0], 100, pFile);//���̍s��S�����ǂݎ��A���S�ɏI��点��
										continue;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &aString[0],
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.x,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.y,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.z);
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &aString[0],
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.x,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.y,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.z);
									}
									else if (strcmp(&aString[0], "END_KEY") == 0)
									{
										nCntKey++;
										break;
									}

								}
							}
							else if (strcmp(&aString[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								break;
							}
						}

					}
					else if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{
						nCntKeySet = 0;
						nCntMotionSet++;
						break;
					}
				}
			}
		}
	}
}

//============================
//���[�V�����̍X�V����
//============================
void UpdateMotion(void)
{
	Player* pPlayer = GetPlayer();

	bool bUse = true;
	//==============================
	//�g�p���郂�[�V���������߂�
	//==============================
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		g_aMotionSet[nCntMotion].bUse = false;
	}
	g_nUseMotion = pPlayer->nState;
	g_nCntFrame++;
	if (g_nCntFrame >= g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].nFrame)
	{
		g_nCntFrame = 0;
		g_nCntKeySet++;
		if (g_nCntKeySet >= g_aMotionSet[g_nUseMotion].nNumKey)
		{
			g_nCntKeySet = 0;
			if (g_aMotionSet[g_nUseMotion].bLoop == false)
			{
				pPlayer->nState = PLAYERSTATE_NUTORAL;
				pPlayer->bMotionFlag = false;
			}
		}
		for (int nCntKey = 0; nCntKey < g_nNumMotion; nCntKey++)
		{
		//�@�^�[�Q�b�g�@���@(���݌Ăяo���Ă��郂�[�V�����̃L�[�@- (���݂̃v���C���[�̃p�[�c�̌����@- �v���C���[�̃p�[�c�̏����ݒ�j) / �t���[���� 
			g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].TargetRot = (g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].Rot - (pPlayer->aModel[nCntKey].rot - pPlayer->aModel[nCntKey].SaveRot)) /
				(float)(g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].nFrame);	    
		}
	}

	for (int nCntKey = 0; nCntKey < g_nNumMotion; nCntKey++)
	{
		pPlayer->aModel[nCntKey].rot += g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].TargetRot;
	}
}

void SetMotion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, char aPath)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		if (g_aMotionSet[nCntMotion].bUse == false)
		{
			g_aMotionSet[nCntMotion].bUse = true;//�g�p���Ă��邩�ǂ���
		
			

			break;
		}
	}
}