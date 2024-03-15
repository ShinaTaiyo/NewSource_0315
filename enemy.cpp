//========================================================
//
//�P�P���V���F���f���ǂݍ���[Enemy.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "enemy.h"
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
#include"particle.h"
#define ENEMY_SCALE (10.0f)
#define MAX_DELAY (50)//�S�̓I�ɍU�����x��������


//�O���[�o���ϐ�
int g_nDelayEnemy = 0;
int g_nldxShadowEnemy = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j
Enemy g_aEnemy[MAX_ENEMY];//���f�����̍\����
EnemyModelInfo g_aEnemyModelInfo[NUM_ENEMY];//���f���̃}�e���A���Ⓒ�_�̍\����


//=================================
//�^�C�g����ʂ̏���������
//=================================
void InitEnemy(void)
{
	g_nDelayEnemy = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾


	//================================
    //���f�����̏�����
    //================================
	for (int nCntMatEnemy = 0; nCntMatEnemy < NUM_ENEMY; nCntMatEnemy++)
	{
		g_aEnemyModelInfo[nCntMatEnemy].dwNumMat = {};
		g_aEnemyModelInfo[nCntMatEnemy].pBuffMat = {};
		g_aEnemyModelInfo[nCntMatEnemy].pMesh = {};
		
	}

	for (int nCntType = 0; nCntType < NUM_ENEMY; nCntType++)
	{
		D3DXLoadMeshFromX(ENEMY_FILENAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aEnemyModelInfo[nCntType].pBuffMat,
			NULL,
			&g_aEnemyModelInfo[nCntType].dwNumMat,
			&g_aEnemyModelInfo[nCntType].pMesh);
	}

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_aEnemy[nCnt].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aEnemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aEnemy[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//1F�O�̈ʒu

		g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aEnemy[nCnt].nIdxShadow = -1;
		g_aEnemy[nCnt].nType = -1;
		g_aEnemy[nCnt].vtxMinEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
		g_aEnemy[nCnt].vtxMaxEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
		g_aEnemy[nCnt].nNumVtx = 0;//���_��
		g_aEnemy[nCnt].sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		g_aEnemy[nCnt].pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
		g_aEnemy[nCnt].Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�G�̑傫��
		g_aEnemy[nCnt].bIsLanding = false;//�n�ʂɂ��Ă��邩�ǂ���
		g_aEnemy[nCnt].fVaimY1 = 0.0f;//��������Y�����̃x�N�g��
		g_aEnemy[nCnt].fVaimY2 = 0.0f;//��������Y�����̃x�N�g��
		g_aEnemy[nCnt].fVaim3 = 0.0f;

		g_aEnemy[nCnt].fVXaim = 0.0f;
		g_aEnemy[nCnt].fVYaim = 0.0f;
		g_aEnemy[nCnt].fVZaim = 0.0f;
		g_aEnemy[nCnt].fVaim = 0.0f;

		g_aEnemy[nCnt].fPenduram = 0.0f;//�U��q�̂悤�ɒe�𔭎˂����鏈��
		g_aEnemy[nCnt].bPenduramFlag = false;

		//�X�e�[�^�X�ݒ�
		g_aEnemy[nCnt].nHp = 0;//�̗�
		g_aEnemy[nCnt].nAttack = 0;//�U����
		g_aEnemy[nCnt].nDefeatScore = 0;//�|�����Ƃ��ɂ��炦��X�R�A
		g_aEnemy[nCnt].fSpeed = 0.0f;//�G�̑���
	}
						
				
	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	for (int nCntENEMYSET = 0; nCntENEMYSET < NUM_ENEMY; nCntENEMYSET++)
	{
		//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
		pMat = (D3DXMATERIAL*)g_aEnemyModelInfo[nCntENEMYSET].pBuffMat->GetBufferPointer();
		int nNumTexture = 0;
		for (int nCntMat = 0; nCntMat < (int)g_aEnemyModelInfo[nCntENEMYSET].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���
					//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aEnemyModelInfo[nCntENEMYSET].apTextureEnemy[nNumTexture]);
				nNumTexture++;
			}
		}
	}
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY09_DARKSLIME);
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitEnemy(void)
{
	for (int nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		//���b�V���̔j��
		if (g_aEnemyModelInfo[nCnt].pMesh != NULL)
		{
			g_aEnemyModelInfo[nCnt].pMesh->Release();
			g_aEnemyModelInfo[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_aEnemyModelInfo[nCnt].pBuffMat != NULL)
		{
			g_aEnemyModelInfo[nCnt].pBuffMat->Release();
			g_aEnemyModelInfo[nCnt].pBuffMat = NULL;
		}
	}
}
//============================
//���f���̍X�V����
//============================
void UpdateEnemy(void)
{
	Player* pPlayer = GetPlayer();

	g_nDelayEnemy++;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].bIsLanding = bCollisionModel(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posOld, &g_aEnemy[nCntEnemy].move, g_aEnemy[nCntEnemy].Size);

			g_aEnemy[nCntEnemy].fVXaim = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
			g_aEnemy[nCntEnemy].fVYaim = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;
			g_aEnemy[nCntEnemy].fVZaim = pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z;

			g_aEnemy[nCntEnemy].fVaim = atan2f(g_aEnemy[nCntEnemy].fVXaim, g_aEnemy[nCntEnemy].fVZaim);//X��Z�̃x�N�g�����o���B
			g_aEnemy[nCntEnemy].fVaimY1 = atan2f(g_aEnemy[nCntEnemy].fVYaim, g_aEnemy[nCntEnemy].fVZaim);//Y��Z�̃x�N�g�����o���B

			if (g_aEnemy[nCntEnemy].bIsLanding == false)
			{
				g_aEnemy[nCntEnemy].move.y = -2.0f;//�d�͏���
			}

			if (g_aEnemy[nCntEnemy].pos.y <= 0.0f)
			{
				g_aEnemy[nCntEnemy].pos.y = 0.0f;
				g_aEnemy[nCntEnemy].move.y = 0.0f;
			}

			switch (g_aEnemy[nCntEnemy].nType)
			{
			case ENEMY00_NOOBSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;

				break;
			case ENEMY01_ANGRYSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
					if (g_nDelayEnemy % (110 + MAX_DELAY) == 0)
					{
						PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_000);
						float fRandumRot = float(rand() % 100 + 1) / 100;
						for (int nCnt = 0; nCnt < 8; nCnt++)
						{
							float fRot = (2.0f / 8) * nCnt;
							
							SetBullet(BULLETTYPE_ENEMY, 300, 10.0f, 10.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z), D3DXVECTOR3(sinf(D3DX_PI * fRot + fRandumRot) * 5.0f, 0.0f, cosf(D3DX_PI * fRot + fRandumRot) * 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),-1,-1.0f);
						}
					}
					break;
			case ENEMY02_SWORDSLIME:
				if (g_nDelayEnemy % (200) == 0)
				{
					PlaySound(SOUND_LABEL_SE_ARROWSHOT_000);

					for (int nCnt = 0; nCnt < 8; nCnt++)
					{
						SetBullet(BULLETTYPE_SWING, 200, 10.0f, 10.0f,
							D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + 10.0f, g_aEnemy[nCntEnemy].pos.z),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nCntEnemy, 20.0f * nCnt);
					}
				}
				break;
			case ENEMY03_HAMMERSLIME:
				if (g_nDelayEnemy % (102) == 0)
				{
					PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_001);
					float fRandumRot = float(rand() % 200 + 1) / 100;
					float fRandumSpeed = float(rand() % 100 + 30) / 10;
					float fRandumMove = float(rand() % 21 - 10);
						SetBullet(BULLETTYPE_RANDUM, 420, 15.0f, 15.0f,
							D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z),
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed,0.0f, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nCntEnemy,-1.0f);
				}
				break;
			case ENEMY04_ORANGESLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;

				if (g_aEnemy[nCntEnemy].bPenduramFlag == false)
				{
					g_aEnemy[nCntEnemy].fPenduram += 0.03f;
				}
				else if (g_aEnemy[nCntEnemy].bPenduramFlag == true)
				{
					g_aEnemy[nCntEnemy].fPenduram -= 0.03f;
				}

				if (g_aEnemy[nCntEnemy].fPenduram >= 1.0f)
				{
					g_aEnemy[nCntEnemy].bPenduramFlag = true;
				}
				else if (g_aEnemy[nCntEnemy].fPenduram <= -1.0f)
				{
					g_aEnemy[nCntEnemy].bPenduramFlag = false;
				}
				if (g_nDelayEnemy % (87) == 0)
				{
				PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_004);
					float fRandumRot = float(rand() % 200 + 1) / 100;
					float fRandumSpeed = float(rand() % 100 + 30) / 10;
					float fRandumMove = float(rand() % 21 - 10);

					SetBullet(BULLETTYPE_ENEMY, 180, 15.0f, 15.0f,
						D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z),
						D3DXVECTOR3(sinf(g_aEnemy[nCntEnemy].fVaim + g_aEnemy[nCntEnemy].fPenduram) * 7.0f,0.0f, cosf(g_aEnemy[nCntEnemy].fVaim + g_aEnemy[nCntEnemy].fPenduram) * 7.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), nCntEnemy, -1.0f);
				}
				break;
			case ENEMY05_GREENSLIME:
				if (g_nDelayEnemy % (90 + MAX_DELAY) == 0)
				{
				PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_006);
					float fRandumRot = float(rand() % 200 + 1) / 100;
					float fRandumSpeed = float(rand() % 100 + 30) / 10;
					float fRandumMove = float(rand() % 21 - 10);

					for (int nCnt = 0; nCnt < 6; nCnt++)
					{
						float fRot = (2.0f / 6) * nCnt;
						SetBullet(BULLETTYPE_CURVE, 300, 15.0f, 15.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z),
							D3DXVECTOR3(sinf(D3DX_PI * fRot + fRandumRot) * 5.0f, 0.0f, cosf(D3DX_PI * fRot + fRandumRot) * 5.0f), 
							D3DXVECTOR3(0.0f,fRot, 0.0f), -1, -1.0f);
					}
				}
				break;
			case ENEMY06_WHITESLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
				if (g_nDelayEnemy % (120) == 0)
				{
				PlaySound(SOUND_LABEL_SE_FALLINGBLOCK);
					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						SetBullet(BULLETTYPE_WALL, 300, 10.0f, 10.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + (30.0f * nCnt), g_aEnemy[nCntEnemy].pos.z), D3DXVECTOR3(sinf(g_aEnemy[nCntEnemy].fVaim) * 5.0f, 0.0f, cosf(g_aEnemy[nCntEnemy].fVaim) * 5.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].fVaim, 0.0f), -1, -1.0f);
					}
				}
				break;
			case ENEMY07_TURQUOISSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
				if (g_nDelayEnemy % (100 + MAX_DELAY) == 0)
				{
				    PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_007);
					float fRandumRot = float(rand() % 100 + 1) / 100;

					for (int nCnt = 0; nCnt < 10; nCnt++)
					{
						float fRot = (2.0f / 10) * nCnt;
						SetBullet(BULLETTYPE_BOUND, 360, 10.0f, 10.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z), D3DXVECTOR3(sinf(D3DX_PI * fRot + fRandumRot) * 4.0f, 0.0f, cosf(D3DX_PI * fRot + fRandumRot) * 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, -1.0f);
					}
				}
				break;
			case ENEMY08_ENGELSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
				if (g_nDelayEnemy % (82 + MAX_DELAY) == 0)
				{
				PlaySound(SOUND_LABEL_SE_ICICLECLAW);
					//float fRandumRot = float(rand() % 100 + 1) / 100;

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRot = (2.0f / 20) * nCnt;
						SetBullet(BULLETTYPE_ENEMY, 300, 20.0f, 20.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z), 
							D3DXVECTOR3(sinf(g_aEnemy[nCntEnemy].fVaim) *( 2.0f + 2.0f * (float)(nCnt)), sinf(g_aEnemy[nCntEnemy].fVaimY1)* (2.0f + 2.0f * (float)(nCnt)), cosf(g_aEnemy[nCntEnemy].fVaim) * 2.0f * (2.0f + 2.0f * (float)(nCnt))), D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, -1.0f);
					}
				}
				break;
			case ENEMY09_DARKSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
				if (g_nDelayEnemy % (113) == 0)
				{
				PlaySound(SOUND_LABEL_SE_SHOT_ENEMY_002);
					
					SetBullet(BULLETTYPE_RING, 420, 10.0f, 10.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].Size.y / 2, g_aEnemy[nCntEnemy].pos.z),
						D3DXVECTOR3(sinf(g_aEnemy[nCntEnemy].fVaim) * 6.0f, sinf(g_aEnemy[nCntEnemy].fVaimY1) * 6.0f, cosf(g_aEnemy[nCntEnemy].fVaim) * 6.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].fVaim, 0.0f), -1, -1.0f);

				}
				break;
			case ENEMY10_RAINBOWSLIME:
				g_aEnemy[nCntEnemy].rot.y = g_aEnemy[nCntEnemy].fVaim + D3DX_PI;
				if (g_nDelayEnemy % 4  == 0)
				{
					if (g_nDelayEnemy % 28 == 0)
					{
						PlaySound(SOUND_LABEL_SE_SPLETBULLET);
					}
					float fRandumRot = float(rand() % 200 + 1) / 100;
					float fRandumSpeed = float(rand() % 100 + 30) / 10;
					float fRandumMove = float(rand() % 21 - 10);
					float fRandumLength = float(rand() % 550 + 200);

					SetBullet(BULLETTYPE_CHAOS, 420, 10.0f, 10.0f, D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + sinf(-D3DX_PI * fRandumRot) * fRandumLength, g_aEnemy[nCntEnemy].pos.y + 600.0f, g_aEnemy[nCntEnemy].pos.z + cosf(-D3DX_PI * fRandumRot) * fRandumLength),
						D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f,0.0f, 0.0f), -1, -1.0f);


				}
				break;	
			}

			
			//======================================
			//�ړ�����
			//======================================
			g_aEnemy[nCntEnemy].move.x = sinf(g_aEnemy[nCntEnemy].fVaim) * g_aEnemy[nCntEnemy].fSpeed;
			g_aEnemy[nCntEnemy].move.z = cosf(g_aEnemy[nCntEnemy].fVaim) * g_aEnemy[nCntEnemy].fSpeed;
		
			g_aEnemy[nCntEnemy].posOld = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			//==================================================================================================

			//�̗͂O����
			if (g_aEnemy[nCntEnemy].nHp <= 0)
			{
				AddCombo(1);//�R���{���𑝉�������
				int nCombo = GetCombo();//�R���{�����擾����
				float fScoreBonus = nCombo * 0.1f;
				g_aEnemy[nCntEnemy].bUse = false;//�̗͂O�ȉ��Ȃ̂ŁA�|���
				AddScore(g_aEnemy[nCntEnemy].nDefeatScore * (int)((1.0f + fScoreBonus)));
				
			}

			SetPositionShadow(g_aEnemy[nCntEnemy].nIdxShadow,D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x,g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].Size.y / 2,g_aEnemy[nCntEnemy].pos.z),-1,nCntEnemy,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

			if (g_aEnemy[nCntEnemy].bUse == false)
			{
				KillShadow(g_aEnemy[nCntEnemy].nIdxShadow);
			}

		}
	}
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);

			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);


			//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
			pMat = (D3DXMATERIAL*)g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pBuffMat->GetBufferPointer();

			int nNumTexture = 0;
			//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
			for (int nCntMat = 0; nCntMat < (int)g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].apTextureEnemy[nNumTexture]);
					nNumTexture++;
				}
				else
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].apTextureEnemy[nNumTexture]);
					nNumTexture++;
				}
				//���f���i�p�[�c�j�̕`��
				g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	BYTE* pVtxBuff;
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aEnemy[nCntEnemy].pos = pos;//�ʒu
			g_aEnemy[nCntEnemy].posOld = pos;//1F�O�̈ʒu
			g_aEnemy[nCntEnemy].rot = rot;//����
			g_aEnemy[nCntEnemy].nType = nType;//���
			g_aEnemy[nCntEnemy].fPenduram = 0.0f;//�U��q�̂悤�ɒe�𔭎˂���ϐ�
			g_aEnemy[nCntEnemy].bPenduramFlag = false;
			g_aEnemy[nCntEnemy].nIdxShadow = SetShadow();

			//=====================================
			//���f���̈ʒu�̍ő�ŏ��l���擾����
			//=====================================

				//���_���̎擾
				g_aEnemy[nCntEnemy].nNumVtx = g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pMesh->GetNumVertices();

				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				g_aEnemy[nCntEnemy].sizeFVF = D3DXGetFVFVertexSize(g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pMesh->GetFVF());

				//���_�o�b�t�@�̃��b�N
				g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


				for (int nCntVtx = 0; nCntVtx < g_aEnemy[nCntEnemy].nNumVtx; nCntVtx++)
				{
					//���_���W�̑��
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

					//====================================================
					//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
					//====================================================
					if (vtx.x > g_aEnemy[nCntEnemy].vtxMaxEnemy.x)
					{
						g_aEnemy[nCntEnemy].vtxMaxEnemy.x = vtx.x;
					}
					else if (vtx.x < g_aEnemy[nCntEnemy].vtxMinEnemy.x)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aEnemy[nCntEnemy].vtxMinEnemy.x = vtx.x;
					}
					else if (vtx.y > g_aEnemy[nCntEnemy].vtxMaxEnemy.y)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aEnemy[nCntEnemy].vtxMaxEnemy.y = vtx.y;
					}
					else if (vtx.y < g_aEnemy[nCntEnemy].vtxMinEnemy.y)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aEnemy[nCntEnemy].vtxMinEnemy.y = vtx.y;
					}
					else if (vtx.z > g_aEnemy[nCntEnemy].vtxMaxEnemy.z)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aEnemy[nCntEnemy].vtxMaxEnemy.z = vtx.z;
					}
					else if (vtx.z < g_aEnemy[nCntEnemy].vtxMinEnemy.z)
					{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
						g_aEnemy[nCntEnemy].vtxMinEnemy.z = vtx.z;
					}
					//========================================================================

					//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
					g_aEnemy[nCntEnemy].pVtxBuff += g_aEnemy[nCntEnemy].sizeFVF;

				}

				//���_�o�b�t�@�̃A�����b�N
				g_aEnemyModelInfo[g_aEnemy[nCntEnemy].nType].pMesh->UnlockVertexBuffer();

				//��ޓ��肵�����A�����^�C�v��for���񂷕K�v�Ȃ��̂ŁAbreak
				
			
			//============================================================================================================================

			//���_�̍ő�ŏ��������āA�傫�������߂�B
			g_aEnemy[nCntEnemy].Size = g_aEnemy[nCntEnemy].vtxMaxEnemy - g_aEnemy[nCntEnemy].vtxMinEnemy;

			//=========================
			//�X�e�[�^�X�ݒ菈��
			//=========================
			switch (g_aEnemy[nCntEnemy].nType)
			{
			case ENEMY00_NOOBSLIME:
				g_aEnemy[nCntEnemy].nHp = 10;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 5;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 100;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 1.0f;//����
				break;
			case ENEMY01_ANGRYSLIME:
				g_aEnemy[nCntEnemy].nHp = 70;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 30;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 300;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 1.5f;//����
				break;
			case ENEMY02_SWORDSLIME:
				g_aEnemy[nCntEnemy].nHp = 60;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 20;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore =500;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 3.0f;//����
				break;
			case ENEMY03_HAMMERSLIME:
				g_aEnemy[nCntEnemy].nHp = 115;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 60;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 500;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 0.5f;//����

				break;
			case ENEMY04_ORANGESLIME:
				g_aEnemy[nCntEnemy].nHp = 70;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 70;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 800;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 1.6f;//����

				break;
			case ENEMY05_GREENSLIME:
				g_aEnemy[nCntEnemy].nHp = 150;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 50;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 1000;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 2.2f;//����

				break;
			case ENEMY06_WHITESLIME:
				g_aEnemy[nCntEnemy].nHp = 120;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 50;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 1000;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 2.2f;//����

				break;
			case ENEMY07_TURQUOISSLIME:
				g_aEnemy[nCntEnemy].nHp = 175;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 110;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 1500;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 1.8f;//����

				break;
			case ENEMY08_ENGELSLIME:
				g_aEnemy[nCntEnemy].nHp = 200;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 90;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 2000;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 3.5f;//����
				break;
			case ENEMY09_DARKSLIME:
				g_aEnemy[nCntEnemy].nHp = 250;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 200;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 2500;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 0.8f;//����

				break;
			case ENEMY10_RAINBOWSLIME:
				g_aEnemy[nCntEnemy].nHp = 500;//�̗�
				g_aEnemy[nCntEnemy].nAttack = 140;//�U����
				g_aEnemy[nCntEnemy].nDefeatScore = 5000;//�|�������ɂ��炦��X�R�A
				g_aEnemy[nCntEnemy].fSpeed = 2.5f;//����
				break;
			}
			//===========================================================
			//g_aEnemy[nCntEnemy].nIdxShadow = SetShadow();//�e�̃C���f�b�N�X��ݒ�
			break;
		}
	}
}


Enemy* GetEnemy(void)//�G�\���̂̏����擾����
{
	return &g_aEnemy[0];
}

void SetDamageEnemy(int nDamage, int nNumEnemy)
{
	Player* pPlayer = GetPlayer();

	/*PlaySound(SOUND_LABEL_SE_HIT);*/
	g_aEnemy[nNumEnemy].nHp -= nDamage;//�̗͂����炷
}
