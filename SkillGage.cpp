//========================================================
//
//�X���P�P���F�v���C���[���X�L���Q�[�W�̒��ɓ������Ƃ��ɁA�������鏈��[SkillGage.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "SkillGage.h"
#include "SkillName.h"
#include "input.h"
#include "player.h"

//�}�N����`
#define NUM_SKILLGAGE (2)
#define MAX_SKILLGAGE (2)
#define SKILLGAGE_HEIGHT (30.0f)
#define SKILLGAGE_WIDTH (500.0f)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureSkillGage[NUM_SKILLGAGE] = {};//�e�N�X�`��3�����̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillGage = NULL;//���_�o�b�t�@�ւ̃|�C���^

SkillGage g_aSkillGage[MAX_SKILLGAGE];

//float g_fSkillGage = 0;
//int g_nSkillGage_Count = 0;
//Result_2 g_aResult_2;
//============================
//�̗͂̏���������
//============================
void InitSkillGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSkillGage;

	/*g_nCountBoss1 = 0;*/


	

	/*g_aResult_2.bResultFlag2 = false;*/

	//g_bResultFlag2 = false;

	/* g_fSkillGage = 0;
	 g_nSkillGage_Count = 0;*/

	for (nCntSkillGage = 0; nCntSkillGage < MAX_SKILLGAGE; nCntSkillGage++)
	{
		g_aSkillGage[nCntSkillGage].nSkillGageCount = 0;
		g_aSkillGage[nCntSkillGage].fSkillGage = 0;
		g_aSkillGage[nCntSkillGage].bUse = false;
		g_aSkillGage[nCntSkillGage].bBrinkingFlag= false;
		g_aSkillGage[nCntSkillGage].fBrinkingPoint = 1.0f;
		g_aSkillGage[nCntSkillGage].fBoss1MaxHp = 0.0f;
		g_aSkillGage[nCntSkillGage].nCountBoss1 = 0;
		g_aSkillGage[nCntSkillGage].pos = D3DXVECTOR3(500.0f, 690.0f, 0.0f);
	}



	/*g_aSkillGage[0].bUse = true;
	g_aSkillGage[0].nType = SkillGageTYPE_SKILL;*/
	/*g_fAnimationPattern = 0;*/

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Skill_Gage.png",
		&g_apTextureSkillGage[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Skill_Energy_000.png",
		&g_apTextureSkillGage[1]);

	/*D3DXCreateTextureFromFile(pDevice,
		"data\\BossHp_000.png",
		&g_apTextureSkillGage[NUM_SKILLGAGE][0]);*/

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_SKILLGAGE,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkillGage,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSkillGage->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntSkillGage = 0; nCntSkillGage < MAX_SKILLGAGE; nCntSkillGage++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 670.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 670.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSkillGage->Unlock();
}

//==========================
//�̗͂̏I������
//==========================
void UninitSkillGage(void)
{
	//�e�N�X�`���̔j��
	int nCntSkillGage;

	for (nCntSkillGage = 0; nCntSkillGage < NUM_SKILLGAGE; nCntSkillGage++)
	{
		if (g_apTextureSkillGage[nCntSkillGage] != NULL)
		{
			g_apTextureSkillGage[nCntSkillGage]->Release();
			g_apTextureSkillGage[nCntSkillGage] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSkillGage != NULL)
	{
		g_pVtxBuffSkillGage->Release();
		g_pVtxBuffSkillGage = NULL;
	}
}

//==================================
//�̗͂̍X�V����
//==================================
void UpdateSkillGage(void)
{
	Player* pPlayer = GetPlayer();//�v���C���[�\���̂̏����Q�b�g����B
	Skill* pSkill = GetSkill();

	//g_aSkillGage[0].nSkillGageCount++;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSkillGage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSkillGage = 0; nCntSkillGage < MAX_SKILLGAGE; nCntSkillGage++)
	{
		if (nCntSkillGage == 0)
		{//�Q�[�W�\�L�����i�z��[0]�j



			//g_aSkillGage[nCntSkillGage].nSkillGageCount++;


			/*	if (g_aSkillGage[nCntSkillGage].nType == SkillGageTYPE_SKILL)
				{*/
			//if (g_aSkillGage[nCntSkillGage].nSkillGageCount % 2 == 0)
			//{
			//	g_aSkillGage[nCntSkillGage].fSkillGage++;//�X�L���Q�[�W�A�b�v�I
			//}

			if (g_aSkillGage[nCntSkillGage].fSkillGage >= 1000.0f)
			{
				g_aSkillGage[nCntSkillGage].fSkillGage = 1000.0f;
			}

			//	pVtx[0].pos = D3DXVECTOR3(0.0, 670.0f, 0.0f);
			//	pVtx[1].pos = D3DXVECTOR3(0.0f + g_aSkillGage.fSkillGage, 670.0f, 0.0f);
			//	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			//	pVtx[3].pos = D3DXVECTOR3(0.0f + g_aSkillGage.fSkillGage, SCREEN_HEIGHT, 0.0f);
			////}

			pVtx[0].pos = D3DXVECTOR3(g_aSkillGage[nCntSkillGage].pos.x - 500.0f, g_aSkillGage[nCntSkillGage].pos.y - SKILLGAGE_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f + g_aSkillGage[nCntSkillGage].fSkillGage, g_aSkillGage[nCntSkillGage].pos.y - SKILLGAGE_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSkillGage[nCntSkillGage].pos.x - 500.0f, g_aSkillGage[nCntSkillGage].pos.y + SKILLGAGE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f + g_aSkillGage[nCntSkillGage].fSkillGage, g_aSkillGage[nCntSkillGage].pos.y + SKILLGAGE_HEIGHT, 0.0f);



			if (pPlayer->pos.x >= g_aSkillGage[nCntSkillGage].pos.x - 500.0f && pPlayer->pos.x <= g_aSkillGage[nCntSkillGage].pos.x + 500.0f
				&& pPlayer->pos.y >= g_aSkillGage[nCntSkillGage].pos.y - 20.0f && pPlayer->pos.y <= g_aSkillGage[nCntSkillGage].pos.y + 20.0f)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			}
		}
		else
		{//����Q�[�W�\�L�����i�z��[1])

			if (pSkill->nSkillType == SKILLTYPE_FIRETORNADO)
			{//�I��ł���X�L�����u�t�@�C�A�g���l�[�h�v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 50.0f;
			}
			else if (pSkill->nSkillType == SKILLTYPE_THUNDERBURST)
			{//�I��ł���X�L�����u�T���_�[�o�[�X�g�v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 100.0f;
			}
			else if (pSkill->nSkillType == SKILLTYPE_METEOBALL)
			{//�I��ł���X�L�����u���e�I�{�[���v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 200.0f;
			}
			else if (pSkill->nSkillType == SKILLTYPE_KILLNEEDLE)
			{//�I��ł���X�L�����u�L���j�[�h���v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 150.0f;
			}
			else if (pSkill->nSkillType == SKILLTYPE_CHAINFIRE)
			{//�I��ł���X�L�����u�q�[���v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 300.0f;
			}
			else if (pSkill->nSkillType == SKILLTYPE_ATOMICSLASH)
			{//�I��ł���X�L�����u�C�[�W�X�V�[���h�v�̎�
				g_aSkillGage[nCntSkillGage].fSkillGage = 1000.0f;
			}
			pVtx[0].pos = D3DXVECTOR3(g_aSkillGage[nCntSkillGage].pos.x - 500.0f, g_aSkillGage[nCntSkillGage].pos.y - SKILLGAGE_HEIGHT+17.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f + g_aSkillGage[nCntSkillGage].fSkillGage, g_aSkillGage[nCntSkillGage].pos.y - SKILLGAGE_HEIGHT+17.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSkillGage[nCntSkillGage].pos.x - 500.0f, g_aSkillGage[nCntSkillGage].pos.y + SKILLGAGE_HEIGHT-17.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f + g_aSkillGage[nCntSkillGage].fSkillGage, g_aSkillGage[nCntSkillGage].pos.y + SKILLGAGE_HEIGHT-17.0f, 0.0f);



			if (g_aSkillGage[nCntSkillGage].bBrinkingFlag == false)
			{
				g_aSkillGage[nCntSkillGage].fBrinkingPoint-=0.02f;
			}
			if (g_aSkillGage[nCntSkillGage].bBrinkingFlag == true)
			{
				g_aSkillGage[nCntSkillGage].fBrinkingPoint+=0.02f;
			}

			if (g_aSkillGage[nCntSkillGage].fBrinkingPoint <= 0.0f)
			{
				g_aSkillGage[nCntSkillGage].bBrinkingFlag = true;
			}
			if (g_aSkillGage[nCntSkillGage].fBrinkingPoint >= 1.0f)
			{
				g_aSkillGage[nCntSkillGage].bBrinkingFlag =false;
			}
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f, g_aSkillGage[nCntSkillGage].fBrinkingPoint);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f,1.0f, g_aSkillGage[nCntSkillGage].fBrinkingPoint);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f,1.0f, g_aSkillGage[nCntSkillGage].fBrinkingPoint);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f,1.0f, g_aSkillGage[nCntSkillGage].fBrinkingPoint);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		}
		pVtx += 4;
	}




	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSkillGage->Unlock();
}

//==================================
//�̗͂̕`�揈��
//==================================
void DrawSkillGage(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSkillGage;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSkillGage, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSkillGage = 0; nCntSkillGage < MAX_SKILLGAGE; nCntSkillGage++)
	{
		pDevice->SetTexture(0, g_apTextureSkillGage[nCntSkillGage]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntSkillGage*4,
			2);
	}
	//}

}

void AddSkillGage(float fSkillPoint)//�X�L���Q�[�W�𑝂₷����
{
	g_aSkillGage[0].fSkillGage += fSkillPoint;
}


SkillGage* GetSkillGage(void)
{
	return &g_aSkillGage[0];
}

