//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[Ranking.cpp]
//Author:ShinaTaiyo
//
//=========================================================

//�w�b�_�[
#include "ranking.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "ranking.h"
#include <string.h>
#include <stdio.h>
#include "score.h"

//�}�N����`
#define MAX_RANK (5)//�����N�C�����鏇�ʂ̐�
#define MAX_SCOREDIGIT (8)//�����N�C���������ʂ̃X�R�A�̍ő包��
#define RANKSCORE_SIZE_X (50.0f)//X�����̃X�R�A�\�L�̃T�C�Y
#define RANKSCORE_SIZE_Y (50.0f)//Y�����̃X�R�A�\�L�̃T�C�Y
#define RANKING_TEXT "data\\TEXTFILE\\Ranking.txt" //�ǂݍ��ރe�L�X�g�t�@�C��

//�O���[�o���ϐ�
typedef struct
{
	D3DXVECTOR3 pos;//�X�R�A�̂��ꂼ��̌���\��������ʒu
	int nScore;//���ꂼ��̏��ʂ̃X�R�A
	int nScorePosTexU;//�X�R�A�̃e�N�X�`���̈ʒu
	int nBlinkingPoint;//�X�R�A��_�ł����邽�߂̏����Ɋւ��|�C���g
	bool bBlinkingFlag;//�����N�C�������X�R�A��_�ł�����t���O
}RankScore;

//===================
//�����L���O�̐���
//===================
LPDIRECT3DTEXTURE9 g_pTextureRank =NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK][MAX_SCOREDIGIT];//�����L���O�X�R�A���BMAX_RANK�́A�P�ʁ`�T�ʁAMAX_SCOREDIGIT�́A�����B
int g_nRankUpdate = -1;//�X�V�����NNo
int g_nTimerRanking;   //�����L���O��ʕ\���^�C�}�[
int g_nBlinkingCount;  //�����N�C�������X�R�A�̓_�ŏ����Ɏg��

//===================
//�����L���O�w�i
//===================
LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG= NULL;//���_�o�b�t�@�ւ̃|�C���^


//============================
//�����L���O�̏���������
//============================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();
	int nCntRank;
	int nCntDigit;
	g_nBlinkingCount = 0;

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number_001.png",
		&g_pTextureRank);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking_bg.png",
		&g_pTextureRankBG);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_RANK*MAX_SCOREDIGIT,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	VERTEX_2D* pVtx;
	//============================================================
	//�����L���O�ݒ菈��
	//============================================================
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�\���̂̏��̏�����
		for (int nCntDigit = 0; nCntDigit < MAX_SCOREDIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aRankScore[nCntRank][nCntDigit].pos = D3DXVECTOR3(SCREEN_WIDTH / 2+300.0f-80.0f*nCntDigit, 50.0f + 100.0f * nCntRank, 0.0f);
			g_aRankScore[nCntRank][nCntDigit].nBlinkingPoint = 0;
			g_aRankScore[nCntRank][nCntDigit].bBlinkingFlag = false;//�X�R�A�������N�C��������A���̃X�R�A��_�ł�����t���O
			g_aRankScore[nCntRank][nCntDigit].nScorePosTexU = 0;
				;
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntRank = 0; nCntRank < MAX_RANK * MAX_SCOREDIGIT; nCntRank++)
	{

		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�i�����ݒ�j
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�i�����ݒ�j
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_���W�̃|�C���^���C���N�������g
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();
	SetRanking(GetScore());
	//====================================================================================

	//=============================================================
	// �����L���O�w�i�̏���
	//=============================================================
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�i�����ݒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�i�����ݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankBG->Unlock();
	//==========================================================================

	//SetStaging(STAGINGTYPE_RANKING_BG, -1, D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2, 0.0f));
	
}



//==============================
//���U���g��ʂ̏I������
//==============================
void UninitRanking(void)
{
	//==============================================
	//�����L���O�ݒ菈��
	// =============================================
	
	//�e�N�X�`���̔j��
	if (g_pTextureRank!= NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
	//=============================================================

	//===================================
	//�����L���O�w�i����
	//===================================

	//�e�N�X�`���̔j��
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankBG != NULL)
	{
		g_pVtxBuffRankBG->Release();
		g_pVtxBuffRankBG = NULL;
	}
	//============================================================
}

//===================================
//���U���g��ʂ̍X�V����
//===================================
void UpdateRanking(void)
{
	g_nBlinkingCount++;
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_SCOREDIGIT; nCntDigit++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - RANKSCORE_SIZE_X, g_aRankScore[nCntRank][nCntDigit].pos.y - RANKSCORE_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + RANKSCORE_SIZE_X, g_aRankScore[nCntRank][nCntDigit].pos.y - RANKSCORE_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - RANKSCORE_SIZE_X, g_aRankScore[nCntRank][nCntDigit].pos.y + RANKSCORE_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + RANKSCORE_SIZE_X, g_aRankScore[nCntRank][nCntDigit].pos.y + RANKSCORE_SIZE_Y, 0.0f);

			if (g_aRankScore[nCntRank][nCntDigit].bBlinkingFlag == true)
			{
				if (g_nBlinkingCount % 2 == 0)
				{
					//0���_�J���[�̐ݒ�i�����ݒ�j
					pVtx[0].col = D3DCOLOR_RGBA(255,0,0, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255,0,0, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255,0,0, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255,0,0, 255);
				}
				else
				{

					//���_�J���[�̐ݒ�i�����ݒ�j
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
			}

			pVtx += 4;//���_���W�̃|�C���^���C���N�������g
		}
	}
	g_pVtxBuffRank->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true||GetJoyPadTrigger(JOYKEY_START)==true)
	{
		PlaySound(SOUND_LABEL_SE_DECISION_000);
		StopSound(SOUND_LABEL_BGM002);
		SetFade(MODE_TITLE);
	}

}






//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawRanking(void)
{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

    
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		pDevice->SetTexture(0, g_pTextureRankBG);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			//&g_pVtxBuffPolygon[0],//���_���̐擪�A�h���X
			//sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
	//===================================
	//�����L���O�ݒ菈��
	//===================================


	int nCntRank;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_SCOREDIGIT; nCntRank++)
	{
		
			pDevice->SetTexture(0, g_pTextureRank);
	
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			//&g_pVtxBuffPolygon[0],//���_���̐擪�A�h���X
			//sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
	}
	////===============================================================================================================================================
	//

}

//====================================
//�����L���O�̃��Z�b�g
//====================================
void ResetRanking(void)
{
	int nCntRank;

	int nCntDigit;

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�S�ẴX�R�A������������B
		for (nCntDigit = 0; nCntDigit < MAX_SCOREDIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScore = 0;

		}
	}
}

//========================================
//�����L���O�̃Z�b�g
//========================================
void SetRanking(int nScore)
{
	VERTEX_2D* pVtx;

	//GameCustom* pGameCustom = GetGameCustom();

	/*for (nCount = 0; nCount < MAX_RANK; nCount++)
	{
		nData[nCount] = 0;
	}*/

	FILE* pFile;//�t�@�C���|�C���^��錾

	int nCount;

	int nData[MAX_RANK];//�����L���O�̃X�R�A�������ϐ�
	int nCopyData;//���l�����ւ���Ƃ��̌��̒l�̎󂯎M�p�ϐ�
	int nCountData;
	int nAdditionData;//�ǉ�����l

	

	int nResultScoreData[MAX_RANK];//�ŏI�I�Ƀ����N�C�������X�R�A�̏���������ϐ�
	//===============================================================
	//��񏈗����玝���Ă�������
	//===============================================================
	pFile = fopen(RANKING_TEXT, "r");//�G���[�h�~
	
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fscanf(pFile, "%d", &nData[nCount]);
			

			nResultScoreData[nCount] = 0;//���傫��
		}
		fclose(pFile);//�t�@�C�������
	}


	

		nAdditionData = nScore;//����̃X�R�A

		if (nAdditionData > nData[MAX_RANK - 1])
		{//����̃X�R�A�������N�C�����Ă����X�R�A�̍ŏ��l���傫���ꍇ
			nData[MAX_RANK - 1] = nAdditionData;
		}


			for (nCountData = 0; nCountData < MAX_RANK - 1; nCountData++)//��ׂ鐔�l�i�v�f�P�j��MAX_RANK-1�́A�Ō�̒l�̈�O�̒l�ƍŌ�̒l���ׂ�(�S���ׂ�j
			{
				for (nCount = nCountData + 1; nCount < MAX_RANK; nCount++)//�v�f�Q�i��ׂ��l�̎��̒l����j��nCountData+1�́A�v�f�P�̎��̒l����Ƃ����Ӗ�
				{
					if (nData[nCountData] < nData[nCount])//�v�f�P���v�f�Q��菬�����Ƃ�
					{
						nCopyData = nData[nCountData];//�󂯎M���[nCopyData]
						nData[nCountData] = nData[nCount];//���l�̓���ւ��i��ڂ̐��l�̏��ʂ��A����̏��ʂ́A��ڂ̏��ʂɕς��B�j
						nData[nCount] = nCopyData;//���l�̓���ւ��i����ւ������ڂ̏��ʂɁA����ւ���O�̈�ڂ̏��ʂ̐��l���󂯎M�������B�j
					}
				}
			}
		
	

			
			pFile = fopen(RANKING_TEXT, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		//�t�@�C���ɕ�����������o��
		for (nCount = 0; nCount < MAX_RANK; nCount++)
		{
			fprintf(pFile, "%d\n", nData[nCount]);//���׏I������̂ŁA��ɏ��ʂ�ۑ�����
		}

		//�t�@�C�������
		fclose(pFile);
	}
	
	//==========================================================================================================================

	for (nCount = 0; nCount < MAX_RANK; nCount++)
	{//	�O���[�o���ϐ��ɃX�R�A��ۑ�
		nResultScoreData[nCount] = nData[nCount];//�ŏI�I�ȃX�R�A�̑���i�����N�C�������X�R�A���������ꍇ���܂߂āj�B�i�\�����鏇�ʕ��j
	}




	//==============================================================================================================
	//�����L���O�̃X�R�A�̐����̈ʒu��A�����N�C�������X�R�A�����点�鏈��
	//==============================================================================================================

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)//�����N�C�������X�R�A�T���̓ǂݍ��݁B
	{
		for (int nCntDigit = 0; nCntDigit < MAX_SCOREDIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScorePosTexU = nData[nCntRank] % 10;//�e���ʂ̂��ꂼ��̃X�R�A�����ꂼ��̏��ʂ̂W�����ɑ������B(�����N�C�����鏇�ʂ̐���score.cpp�ł��������������B�j
			nData[nCntRank] = nData[nCntRank] / 10;
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_SCOREDIGIT; nCntDigit++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePosTexU), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePosTexU), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePosTexU), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePosTexU), 1.0f);

			//===========================================================================================================================================================================================
			//���点�鏈��
			if (nResultScoreData[nCntRank]==nScore)	
			{//�����N�C�������X�R�A�̒��ɁA�������̂��Ȃ������X�R�A�̎�
				g_aRankScore[nCntRank][nCntDigit].bBlinkingFlag = true;
			}
			//=======================================================================================================================================================================================================
			pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
		}
	}
	g_pVtxBuffRank->Unlock();
}
