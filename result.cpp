//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[result.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "result.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "ranking.h"
#include "score.h"

#define MAX_SCORERESULT (8)
#define MAX_SCORERESULTSIZE (50.0f)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_RESULT_TEX] = {};//�e�N�X�`���ւ̃|�C���^
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//���_�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9 g_pTextureScoreResult = {};//�e�N�X�`���ւ̃|�C���^
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreResult = NULL;//���_�o�b�t�@�ւ̃|�C���^


typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	//D3DXVECTOR3 move;//�ړ���
	////int nLife;//�����i�ǂ̂��炢�e�����ł������j
	bool bUse;//�e���g�p���Ă��邩�ǂ���
}ScoreResult;



ResultType g_aResultType;

ScoreResult g_aScoreResult[MAX_SCORERESULT];

bool g_bColorChangeResult;
int g_nColorChangeValue;

int g_nPosTexU[MAX_SCORERESULT];

//���U���g��ʂ̏���������
void InitResult(void)
{
	int nCntResult;

	g_bColorChangeResult = false;

	g_nColorChangeValue = 0;

	//�����L���O�̐ݒ�
	

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Result_BG.png",
		&g_pTextureResult[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
		
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
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
	g_pVtxBuffResult->Unlock();

	



	//==============================================================
	//�ŏI�X�R�A�̏���������
	//==============================================================
	int nCntScoreResult;

	//�e�N�X�`���̓ǂݍ��݁i�X�R�A�̃e�N�X�`����ǂݍ��ށj
	for (nCntScoreResult = 0; nCntScoreResult < MAX_SCORERESULT; nCntScoreResult++)
	{

		g_nPosTexU[nCntScoreResult] = 0;
	}
		//�X�R�A���̏�����
	for (nCntScoreResult = 0; nCntScoreResult < MAX_SCORERESULT; nCntScoreResult++)
	{
		g_aScoreResult[nCntScoreResult].pos = D3DXVECTOR3(SCREEN_WIDTH/2+300.0f - ((nCntScoreResult + 1) * 80.0f), SCREEN_HEIGHT/2+300.0f, 0.0f);
		g_aScoreResult[nCntScoreResult].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	D3DXCreateTextureFromFile(pDevice,
		"data\\number_001.png",
		&g_pTextureScoreResult);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORERESULT,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreResult,
		NULL);

	

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScoreResult = 0; nCntScoreResult < MAX_SCORERESULT; nCntScoreResult++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aScoreResult[nCntScoreResult].pos.x - MAX_SCORERESULTSIZE, g_aScoreResult[nCntScoreResult].pos.y -MAX_SCORERESULTSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aScoreResult[nCntScoreResult].pos.x + MAX_SCORERESULTSIZE, g_aScoreResult[nCntScoreResult].pos.y -MAX_SCORERESULTSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aScoreResult[nCntScoreResult].pos.x - MAX_SCORERESULTSIZE, g_aScoreResult[nCntScoreResult].pos.y +MAX_SCORERESULTSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aScoreResult[nCntScoreResult].pos.x + MAX_SCORERESULTSIZE, g_aScoreResult[nCntScoreResult].pos.y +MAX_SCORERESULTSIZE, 0.0f);
		g_aScoreResult[nCntScoreResult].bUse = true;//�g�p���Ă����Ԃɂ���
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
		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScoreResult->Unlock();

	PlaySound(SOUND_LABEL_BGM002);
}

//==============================
//���U���g��ʂ̏I������
//==============================
void UninitResult(void)
{
	int nCnt;
	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_RESULT_TEX; nCnt++)
	{
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	if (g_pTextureScoreResult != NULL)
	{
		g_pTextureScoreResult->Release();
		g_pTextureScoreResult = NULL;
	}
	//}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScoreResult != NULL)
	{
		g_pVtxBuffScoreResult->Release();
		g_pVtxBuffScoreResult = NULL;
	}
}

//===================================
//���U���g��ʂ̍X�V����
//===================================
void UpdateResult(void)
{
	int nCntResult;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	//for (nCntResult = 0; nCntResult < MAX_RESULT_TEX; nCntResult++)
	//{
	//	//���_���W�̐ݒ�i�����ʒu�j

		if (g_aResultType.nResultType == RESULTTYPE_CLEAR)
		{//�Q�[�����N���A�ł��Ă�����Ă΂��B


			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (g_aResultType.nResultType == RESULTTYPE_GAMEOVER)
		{//�Q�[���I�[�o�[��������Ă΂��B
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		pVtx += 4;//���_���W�̃|�C���^���C���N�������g
	/*}*/
	g_pVtxBuffResult->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true||GetJoyPadTrigger(JOYKEY_START)==true)
	{//����L�[�iENTER�L�[�j�������ꂽ

		PlaySound(SOUND_LABEL_SE_DECISION_000);
		//���[�h�̐ݒ�i�Q�[����ʂɈڍs�j
		SetFade(MODE_RANKING);
	}
//==========================================================================================================================

	//=================================
	//�ŏI�X�R�A�\������
	//=================================

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScoreResult->Lock(0, 0, (void**)&pVtx, 0);


	int nGetScore;
	//
	//nScore = 184545;
	/*g_nScore += nScore;*/

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	nGetScore = GetScore();//�X�R�A���擾����B

	int nCnt;
	int	nCntScore;
	for (nCnt = 0; nCnt < MAX_SCORERESULT; nCnt++)
	{
		g_nPosTexU[nCnt] = nGetScore % 10;
		nGetScore = nGetScore / 10;
	}

	for (nCntScore = 0; nCntScore < MAX_SCORERESULT; nCntScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_nPosTexU[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_nPosTexU[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_nPosTexU[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_nPosTexU[nCntScore]), 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScoreResult->Unlock();

	/*for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		SetScore(10);
	}*/


}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	int nCntResult;
		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		if (g_aResultType.nResultType == RESULTTYPE_CLEAR)
		{
			pDevice->SetTexture(0, g_pTextureResult[RESULTTYPE_CLEAR]);
		}
		if (g_aResultType.nResultType == RESULTTYPE_GAMEOVER)
		{
			pDevice->SetTexture(0, g_pTextureResult[RESULTTYPE_GAMEOVER]);
		}
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
	

		//=============================================================
		//�ŏI�X�R�A�\�������̕`��(�X�R�A�\��������������A�g��
		//=============================================================
		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScoreResult, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);


		int nCntScore;
		for (nCntScore = 0; nCntScore < MAX_SCORERESULT; nCntScore++)
		{
			
				//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScoreResult);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
				nCntScore * 4,
				2);
			

		}
}

//================================
//���U���g��ʕ����\���̂̎擾
//================================

ResultType* GetResultType(void)
{
	return &g_aResultType;//���U���g�^�C�v�̏���Ԃ��B
}