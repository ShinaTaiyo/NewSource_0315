//========================================================
//
//�P�O���P�O���F�G�t�F�N�g������񌩒���[Combo.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "main.h"
#include "Combo.h"
#include "input.h"
#include "player.h"
#include "Combo.h"
#include "result.h"
#include "damage.h"
#include "game.h"

#define MAX_COMBO (4) //�̗͂̍ő包��
#define NUM_COMBO (1) //�̗͕\���̎��
#define COMBO_RADIUS (10.0f) //�̗͕\���̐��l�̔��a�i�傫���j

#define COMBO_WIDTH (20.0f) //�̗͂̉���
#define COMBO_HEIGHT (40.0f)//�̗͂̍���

#define COMBO_UI_RADIUS_X (60.0f)//�̗�UI�̉���
#define COMBO_UI_RADIUS_Y (30.0f)//�̗�UI�̍���

#define COMBOGAGE_WIDTH (500.0f)
#define COMBOGAGE_HEIGHT (20.0f)



//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	bool bUse;//�̗͕\�������悤���Ă��邩�ǂ���
}Combo;

//�O���[�o���ϐ�

//================================================================================
//�R���{�����\������
//================================================================================
LPDIRECT3DTEXTURE9 g_pTextureUICombo = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUICombo = NULL;
D3DXVECTOR3 g_posUICombo;//�ʒu
D3DXVECTOR3 g_moveUICombo;//�ړ���

//=======================================================================

//�̗͕\������============================================================
LPDIRECT3DTEXTURE9 g_pTextureCombo = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCombo = NULL;
Combo g_aCombo[MAX_COMBO];
D3DXVECTOR3 g_posCombo;//�ʒu
D3DXVECTOR3 g_moveCombo;//�ړ���

int g_nCombo = 0;


int g_aPosComboTexU[8];//�e���̐������i�[

int g_nSaveCombo = 0;


int g_nMaxCombo;//�ő�̗͕ۑ��p


//========================================
//�R���{�Q�[�W�\�L����
//========================================
LPDIRECT3DTEXTURE9 g_pTextureComboGage = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffComboGage = NULL;
D3DXVECTOR3 g_posComboGage;//�ʒu
D3DXVECTOR3 g_moveComboGage;//�ړ���

float g_fComboGage;//�R���{�Q�[�W�̕\�L



//=========================================================================
//�̗͂̏���������
void InitCombo(void)
{
	ResultType* pResultType = GetResultType();
	g_nCombo = 0;//�̗͂̏����l
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//=======================================
	//�R���{UI����
	//=======================================
	g_posUICombo = D3DXVECTOR3(SCREEN_WIDTH - 80.0f, 70.0f, 0.0f);//UI�\���ꏊ

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Combo.png",
		&g_pTextureUICombo);
	//�e�N�X�`���̓ǂݍ��݁i�X�R�A�̃e�N�X�`����ǂݍ��ށj

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUICombo,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUICombo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posUICombo.x - COMBO_UI_RADIUS_X, g_posUICombo.y - COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posUICombo.x + COMBO_UI_RADIUS_X, g_posUICombo.y - COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posUICombo.x - COMBO_UI_RADIUS_X, g_posUICombo.y + COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posUICombo.x + COMBO_UI_RADIUS_X, g_posUICombo.y + COMBO_UI_RADIUS_Y, 0.0f);

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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUICombo->Unlock();
	//===============================================================================================================================

	//=================================
	//�̗͕\������
	//=================================
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ComboNum.png",
		&g_pTextureCombo);
	//�e�N�X�`���̓ǂݍ��݁i�X�R�A�̃e�N�X�`����ǂݍ��ށj
	for (int nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		g_aCombo[nCntCombo].pos = D3DXVECTOR3(SCREEN_WIDTH - 120.0f - ((nCntCombo + 1) * 30.0f), 70.0f, 0.0f);
		g_aCombo[nCntCombo].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aPosComboTexU[nCntCombo] = 0;
	}
	

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_COMBO,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCombo,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - COMBO_WIDTH, g_aCombo[nCntCombo].pos.y - COMBO_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + COMBO_WIDTH, g_aCombo[nCntCombo].pos.y - COMBO_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x - COMBO_WIDTH, g_aCombo[nCntCombo].pos.y + COMBO_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCombo[nCntCombo].pos.x + COMBO_WIDTH, g_aCombo[nCntCombo].pos.y + COMBO_HEIGHT, 0.0f);

		g_aCombo[nCntCombo].bUse = true;//�g�p���Ă����Ԃɂ���

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

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCombo->Unlock();

	//====================================================================================================================

	//==============================
	//�R���{�Q�[�W�̏�����
	//==============================

	g_fComboGage = 300;//�R���{�Q�[�W�̒l�̏�����

	g_posComboGage = D3DXVECTOR3(SCREEN_WIDTH,120.0f, 0.0f);//�R���{�Q�[�W�̈ʒu

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Skill_Gage.png",
		&g_pTextureComboGage);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffComboGage,
		NULL);

	g_pVtxBuffComboGage->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffComboGage->Unlock();

}

//�̗͂̏I������
void UninitCombo(void)
{
	//===================================
	//�̗�UI�̏I������
	//===================================

	//�e�N�X�`���̔j��
	if (g_pTextureUICombo != NULL)
	{
		g_pTextureUICombo->Release();
		g_pTextureUICombo = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUICombo != NULL)
	{
		g_pVtxBuffUICombo->Release();
		g_pVtxBuffUICombo = NULL;
	}
	//=======================================================================

	//===================================
	//�̗͕\���̏I������
	//===================================

	//�e�N�X�`���̔j��
	if (g_pTextureCombo != NULL)
	{
		g_pTextureCombo->Release();
		g_pTextureCombo = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffCombo != NULL)
	{
		g_pVtxBuffCombo->Release();
		g_pVtxBuffCombo = NULL;
	}
	//========================================================================

	//===================================
	//�R���{�Q�[�W�\���̏I������
	//===================================

	//�e�N�X�`���̔j��
	if (g_pTextureComboGage != NULL)
	{
		g_pTextureComboGage->Release();
		g_pTextureComboGage = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pTextureComboGage != NULL)
	{
		g_pTextureComboGage->Release();
		g_pTextureComboGage = NULL;
	}
	//========================================================================
}

//�e�̍X�V����
void UpdateCombo(void)
{
	int nCntCombo;
	VERTEX_2D* pVtx;
	Player* pPlayer = GetPlayer();

	//======================================
	//�̗�UI�̍X�V����
	//======================================

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUICombo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nCombo >= 9999)
	{
		g_nCombo = 9999;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posUICombo.x - COMBO_UI_RADIUS_X, g_posUICombo.y - COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posUICombo.x + COMBO_UI_RADIUS_X, g_posUICombo.y - COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posUICombo.x - COMBO_UI_RADIUS_X, g_posUICombo.y + COMBO_UI_RADIUS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posUICombo.x + COMBO_UI_RADIUS_X, g_posUICombo.y + COMBO_UI_RADIUS_Y, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUICombo->Unlock();
	//====================================================================================================================



	//=================================================
	//�̗͕\������
	//=================================================
	int nGetCombo;

	nGetCombo = g_nCombo;//�R���{����ۑ�����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntCombo = 0; nCntCombo < MAX_COMBO; nCntCombo++)
	{
		//���l�̕\������
		g_aPosComboTexU[nCntCombo] = nGetCombo % 10;
		nGetCombo = nGetCombo / 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aPosComboTexU[nCntCombo]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aPosComboTexU[nCntCombo]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aPosComboTexU[nCntCombo]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aPosComboTexU[nCntCombo]), 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCombo->Unlock();
	//==========================================================================================================================================

	//=================================================
	//�R���{�Q�[�W�\������
	//=================================================
	

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffComboGage->Lock(0, 0, (void**)&pVtx, 0);

	g_fComboGage -= 1.0f;//�R���{�Q�[�W�����炵������


	if (g_fComboGage < 0.0f)
	{
		g_fComboGage = 0.0f;
		g_nCombo = 0;//�R���{�������Z�b�g
	}

	//���_�̐ݒ�i�R���{�Q�[�W��\���j
	pVtx[0].pos = D3DXVECTOR3(g_posComboGage.x - 300.0f, g_posComboGage.y - COMBOGAGE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posComboGage.x - 300.0f + g_fComboGage, g_posComboGage.y - COMBOGAGE_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posComboGage.x - 300.0f, g_posComboGage.y + COMBOGAGE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posComboGage.x - 300.0f + g_fComboGage, g_posComboGage.y + COMBOGAGE_HEIGHT, 0.0f);
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);



	//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffComboGage->Unlock();
	//==========================================================================================================================================
}

//�e�̕`�揈��
void DrawCombo(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^


	if (g_nCombo >= 1)
	{
		//===============================================
		//�R���{�̕����`�揈��
		//===============================================

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffUICombo, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUICombo);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			0,
			2);

		//=============================================
		//�R���{���\���̕`�揈��
		//=============================================
		int nCntCombo;

		////�f�o�C�X�̎擾
		//pDevice = GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffCombo, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		int nDigit = 0;
		//�R���{�\���̌����̕\�L�𒲐����鏈��
		if (g_nCombo < 10)
		{
			nDigit = 3;
		}
		else if (g_nCombo < 100)
		{
			nDigit = 2;
		}
		else if (g_nCombo < 1000)
		{
			nDigit = 1;
		}
		//==========================

		for (nCntCombo = 0; nCntCombo < MAX_COMBO - nDigit; nCntCombo++)
		{

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCombo);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
				nCntCombo * 4,
				2);

		}

		//=============================================
		//�R���{�Q�[�W�\���̕`�揈��
		//=============================================
			////�f�o�C�X�̎擾
			//pDevice = GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffComboGage, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureComboGage);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			0,
			2);

		//==============================================================================================================================================
	}
}
//�̗͂̐ݒ菈��
void AddCombo(int nCombo)
{
	g_fComboGage = 300.0f;//�R���{�����̂ŁA�R���{�Q�[�W�̌��������Z�b�g����B
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffCombo->Lock(0, 0, (void**)&pVtx, 0);

	g_nCombo += nCombo;
	Player* pPlayer = GetPlayer();

	int nGetCombo = g_nCombo;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCombo->Unlock();
}


//===================================
//�̗͏��̎擾
//===================================
int GetCombo(void)
{
	return g_nCombo;
}

//==========================
//�R���{�����Z�b�g����
//==========================
void ResetCombo(void)
{
	g_nCombo = 0;
}