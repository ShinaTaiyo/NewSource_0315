//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[tutorial.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "main.h""
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "result.h"
#include "tutorial.h"
#include "sound.h"
#include "fade.h"
//�}�N����`
#include "input.h"
#define NUM_TUTORIALTEX (2)//�`���[�g���A����ʂ̎��

int g_nCountTutorialTime;//�`���[�g���A�����n�܂��Ă���̃J�E���g���X�^�[�g����B

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureTutorial[NUM_TUTORIALTEX] = {};
//D3DXVECTOR3 g_rotPI;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
//Enemy g_aEnemy[MAX_ENEMY];//�G�̏��
//Result g_aResult;

Tutorial g_Tutorial;

//int g_nCountTime = 0;//���Ԃ�\���O���[�o���ϐ�

//=====================================================
//==========================
//�G�̏���������
//==========================
void InitTutorial(void)
{
	g_nCountTutorialTime = 0;


	//srand((unsigned int)time(NULL));//�Q�[�����J�n�������Ԗ��ɗ����̎��ݒ�

	/*SetStaging(STAGINGTYPE_PRESSENTER, -1, D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 150.0f, 0.0f));*/

	LPDIRECT3DDEVICE9 pDevice;
	int	nCntTutorial;

	g_Tutorial.bTutorialUse = true;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ��݁i�G�̃e�N�X�`����ǂݍ��ށj
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\3DGame_Rule.png",
		&g_apTextureTutorial[TUTORIALTYPE_RULE]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\tutorial_operation_004.png",
	//	&g_apTextureTutorial[TUTORIALTYPE_OPERATION]); //��������̉�ʂɂ����܂�Ȃ��Ƃ��Ɏg��


	g_Tutorial.nTutorialType = TUTORIALTYPE_RULE;//��������̏�����




	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,// * NUM_TUTORIALTEX,//�S�͕K�v�Ȓ��_���B����g���摜����2�������A��̃|���S���ł��̂ŁA���_�S�ő��v�B
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//for (nCntTutorial = 0; nCntTutorial < NUM_TUTORIALTEX; nCntTutorial++)
	//{
		//���_���W�̐ݒ�(�G�̑傫���j
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT, 0.0f);

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

		//pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	//}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//====================================
//�`���[�g���A���̏I������
//====================================
void UninitTutorial(void)
{
	//�e�N�X�`���̔j��
	int nCntTutorial;
	for (nCntTutorial = 0; nCntTutorial < NUM_TUTORIALTEX; nCntTutorial++)
	{
		if (g_apTextureTutorial[nCntTutorial] != NULL)
		{
			g_apTextureTutorial[nCntTutorial]->Release();
			g_apTextureTutorial[nCntTutorial] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}


//========================================
//�G�̍X�V����
//========================================
void UpdateTutorial(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	int nCntTutorial;

	g_nCountTutorialTime++;

	
	//=============================================================================
	//�����̃`���[�g���A�����Ăяo������(��̉�ʂɂ����܂�Ȃ��ꍇ�Ɏg�����I
	//=============================================================================

	//if (GetKeyboardTrigger(DIK_RIGHT) == true||GetJoyPadTrigger(JOYKEY_B)==true)
	//{
	//	PlaySound(SOUND_LABEL_SE_SELECT_000);
	//	g_Tutorial.nTutorialType = TUTORIALTYPE_OPERATION;//������@������
	//}
	//if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoyPadTrigger(JOYKEY_Y) == true)
	//{
	//	PlaySound(SOUND_LABEL_SE_SELECT_000);
	//	g_Tutorial.nTutorialType = TUTORIALTYPE_RULE;//���[������������
	//}
	//============================================================================================


	
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
//}
//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true||GetJoyPadTrigger(JOYKEY_START)==true)
	{
		g_Tutorial.bTutorialUse = false;//�`���[�g���A�����I���̂ŁAfalse�ɂ���B
		SetFade(MODE_GAME);//�Q�[����ʂɑJ��
		StopSound(SOUND_LABEL_BGM000);
	}
}


//=========================================
//�G�̕`�揈��
//=========================================
void DrawTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	int nCntTutorial;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

			if (g_Tutorial.nTutorialType == TUTORIALTYPE_RULE)//�f�t�H���g�ݒ�
			{
				pDevice->SetTexture(0, g_apTextureTutorial[TUTORIALTYPE_RULE]);
			}
			if (g_Tutorial.nTutorialType == TUTORIALTYPE_OPERATION)
			{
				pDevice->SetTexture(0, g_apTextureTutorial[TUTORIALTYPE_OPERATION]);
			}
			

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
				0,
				2);
		



}

Tutorial* GetTutorial(void)
{
	return &g_Tutorial;//�`���[�g���A���\���̂̏����Q�b�g����B
}

