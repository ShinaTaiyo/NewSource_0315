//========================================================
//
//�P�O���P�O���F�G�t�F�N�g������񌩒���[Health.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "main.h"
#include "Health.h"
#include "input.h"
#include "player.h"
#include "health.h"
#include "result.h"
#include "damage.h"
#include "game.h"

#define MAX_HEALTH (4) //�̗͂̍ő包��
#define NUM_HEALTH (1) //�̗͕\���̎��
#define HEALTH_RADIUS (10.0f) //�̗͕\���̐��l�̔��a�i�傫���j

#define HEALTH_WIDTH (15.0f) //�̗͂̉���
#define HEALTH_HEIGHT (30.0f)//�̗͂̍���

#define HEALTH_UI_RADIUS_X (100.0f)//�̗�UI�̉���
#define HEALTH_UI_RADIUS_Y (50.0f)//�̗�UI�̍���

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	bool bUse;//�̗͕\�������悤���Ă��邩�ǂ���
}Health;

//�O���[�o���ϐ�

//================================================================================
//�̗͂�UI����
//================================================================================
LPDIRECT3DTEXTURE9 g_pTextureUIHealth = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUIHealth = NULL;
D3DXVECTOR3 g_posUIHealth;//�ʒu
D3DXVECTOR3 g_moveUIHealth;//�ړ���

//=======================================================================

//�̗͕\������============================================================
LPDIRECT3DTEXTURE9 g_pTextureHealth = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHealth = NULL;
Health g_aHealth[MAX_HEALTH];
D3DXVECTOR3 g_posHealth;//�ʒu
D3DXVECTOR3 g_moveHealth;//�ړ���

int g_nHealth = 0;


int g_aPosHealthTexU[8];//�e���̐������i�[

int g_nSaveHealth = 0;


int g_nMaxHealth;//�ő�̗͕ۑ��p
//=========================================================================
//�̗͂̏���������
void InitHealth(void)
{
	ResultType* pResultType = GetResultType();
	g_nHealth = 500;//�̗͂̏����l
	LPDIRECT3DDEVICE9 pDevice;
	int	nCntHealth;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//=======================================
	//�̗�UI����
	//=======================================


	g_posUIHealth = D3DXVECTOR3(150.0f, 50.0f, 0.0f);//UI�\���ꏊ

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\HP_Display_ver1.0.png",
		&g_pTextureUIHealth);
	//�e�N�X�`���̓ǂݍ��݁i�X�R�A�̃e�N�X�`����ǂݍ��ށj

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUIHealth,
		NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUIHealth->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posUIHealth.x - HEALTH_UI_RADIUS_X,g_posUIHealth.y - HEALTH_UI_RADIUS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posUIHealth.x + HEALTH_UI_RADIUS_X,g_posUIHealth.y - HEALTH_UI_RADIUS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posUIHealth.x - HEALTH_UI_RADIUS_X,g_posUIHealth.y + HEALTH_UI_RADIUS_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posUIHealth.x + HEALTH_UI_RADIUS_X,g_posUIHealth.y + HEALTH_UI_RADIUS_Y, 0.0f);

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
	g_pVtxBuffUIHealth->Unlock();
	//===============================================================================================================================

	//=================================
	//�̗͕\������
	//=================================
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number_001.png",
		&g_pTextureHealth);
	//�e�N�X�`���̓ǂݍ��݁i�X�R�A�̃e�N�X�`����ǂݍ��ށj
	for (nCntHealth = 0; nCntHealth < MAX_HEALTH; nCntHealth++)
	{

		g_aPosHealthTexU[nCntHealth] = 0;
	}
	//�X�R�A���̏�����
	for (nCntHealth = 0; nCntHealth < MAX_HEALTH; nCntHealth++)
	{
		g_aHealth[nCntHealth].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 400.0f - ((nCntHealth + 1) * 30.0f), 20.0f, 0.0f);
		g_aHealth[nCntHealth].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HEALTH,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHealth,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHealth->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHealth = 0; nCntHealth < MAX_HEALTH; nCntHealth++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aHealth[nCntHealth].pos.x - HEALTH_WIDTH, g_aHealth[nCntHealth].pos.y - HEALTH_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aHealth[nCntHealth].pos.x + HEALTH_WIDTH, g_aHealth[nCntHealth].pos.y - HEALTH_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aHealth[nCntHealth].pos.x - HEALTH_WIDTH, g_aHealth[nCntHealth].pos.y + HEALTH_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aHealth[nCntHealth].pos.x + HEALTH_WIDTH, g_aHealth[nCntHealth].pos.y + HEALTH_HEIGHT, 0.0f);

		g_aHealth[nCntHealth].bUse = true;//�g�p���Ă����Ԃɂ���

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
	g_pVtxBuffHealth->Unlock();

	//====================================================================================================================
	
	
}

//�̗͂̏I������
void UninitHealth(void)
{
	//===================================
	//�̗�UI�̏I������
	//===================================
	
	//�e�N�X�`���̔j��
	if (g_pTextureUIHealth != NULL)
	{
		g_pTextureUIHealth->Release();
		g_pTextureUIHealth = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUIHealth != NULL)
	{
		g_pVtxBuffUIHealth->Release();
		g_pVtxBuffUIHealth = NULL;
	}
	//=======================================================================

	//===================================
	//�̗͕\���̏I������
	//===================================

	//�e�N�X�`���̔j��
	if (g_pTextureHealth != NULL)
	{
		g_pTextureHealth->Release();
		g_pTextureHealth = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHealth != NULL)
	{
		g_pVtxBuffHealth->Release();
		g_pVtxBuffHealth = NULL;
	}
	//========================================================================
}

//�e�̍X�V����
void UpdateHealth(void)
{
	int nCntHealth;
	VERTEX_2D* pVtx;
	Player* pPlayer = GetPlayer();

	//======================================
	//�̗�UI�̍X�V����
	//======================================
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffUIHealth->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nHealth >= 9999)
	{
		g_nHealth = 9999;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posUIHealth.x - HEALTH_UI_RADIUS_X, g_posUIHealth.y - HEALTH_UI_RADIUS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posUIHealth.x + HEALTH_UI_RADIUS_X, g_posUIHealth.y - HEALTH_UI_RADIUS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posUIHealth.x - HEALTH_UI_RADIUS_X, g_posUIHealth.y + HEALTH_UI_RADIUS_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posUIHealth.x + HEALTH_UI_RADIUS_X, g_posUIHealth.y + HEALTH_UI_RADIUS_Y, 0.0f);

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
	g_pVtxBuffUIHealth->Unlock();
	//====================================================================================================================



	//=================================================
	//�̗͕\������
	//=================================================
	int nGetHealth;

	nGetHealth = pPlayer->nHp;//�X�R�A��ۑ�����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffHealth->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntHealth = 0; nCntHealth < MAX_HEALTH; nCntHealth++)
	{



		////���_�J���[�̐ݒ�
		//if (pPlayer->pos.x >= g_aHealth[nCntHealth].pos.x - HEALTH_WIDTH && pPlayer->pos.x <= g_aHealth[nCntHealth].pos.x + HEALTH_WIDTH
		//	&& pPlayer->pos.y >= g_aHealth[nCntHealth].pos.y - HEALTH_HEIGHT && pPlayer->pos.y <= g_aHealth[nCntHealth].pos.y + HEALTH_HEIGHT)
		//{
		//	//���_�J���[�̐ݒ�
		//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		//}
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		//���l�̕\������
		g_aPosHealthTexU[nCntHealth] = nGetHealth % 10;
		nGetHealth = nGetHealth / 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aPosHealthTexU[nCntHealth]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aPosHealthTexU[nCntHealth]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aPosHealthTexU[nCntHealth]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aPosHealthTexU[nCntHealth]), 1.0f);
		

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHealth->Unlock();
	//==========================================================================================================================================
}

//�e�̕`�揈��
void DrawHealth(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^


	//===============================================
	//�̗�UI�`�揈��
	//===============================================
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUIHealth, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUIHealth);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			0,
			2);

	//=============================================
	//�̗͕\���̕`�揈��
	//=============================================
	int nCntHealth;

	////�f�o�C�X�̎擾
	//pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHealth, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);



	for (nCntHealth = 0; nCntHealth < MAX_HEALTH; nCntHealth++)
	{
			//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureHealth);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			nCntHealth * 4,
			2);
		
	}
	//==============================================================================================================================================

}

//=====================================
//�̗͂̉��Z���Z����
//=====================================
void SetHealing(int nHeal)
{
	g_nHealth += nHeal;
	
}

void DamageHealth(int nValue)
{
	SetHealth(nValue);
	Player* pPlayer = GetPlayer();
	float fRandumRot;
	float fRandumSpeed;
	fRandumRot = float((rand)() % 629 - 314) / 100.0f;
	fRandumSpeed = float((rand)() % 30) / 10.0f;
	SetDamage(nValue, 100,pPlayer->pos, 20.0f,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
}

//�̗͂̐ݒ菈��
void SetHealth(int nDamage)
{
	g_nHealth -= nDamage;
	if (g_nHealth <= 0)
	{
		SetGameState(GAMESTATE_END);
	}
}


//===================================
//�̗͏��̎擾
//===================================
int GetHealth(void)
{
	return g_nHealth;
}