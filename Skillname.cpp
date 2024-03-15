//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[Skillname.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "SkillName.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "sound.h"

//�}�N����`
#define NUM_SKILLTEX
#define SKILLNAME_WIDTH (120.0f)
#define SKILLNAME_HEIGHT (80.0f)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureSkillName = NULL;//�e�N�X�`��3�����̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkillName = NULL;//���_�o�b�t�@�ւ̃|�C���^

Skill g_aSkill;//�X�L���\���̂̃O���[�o���ϐ�

//float g_fSkillGage = 0;
//int g_nSkillGage_Count = 0;
//Result_2 g_aResult_2;
//============================
//�X�L���l�[���̏���������
//============================
void InitSkillName(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_aSkill.fSkillPattern = 0.0f;
	g_aSkill.nSkillType = 0;
	g_aSkill.pos = D3DXVECTOR3(130.0f, 605.0f, 0.0f);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\3DGame_SkillTable.png",
		&g_apTextureSkillName);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSkillName,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSkillName->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(g_aSkill.pos.x-SKILLNAME_WIDTH,g_aSkill.pos.y-SKILLNAME_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aSkill.pos.x+SKILLNAME_WIDTH,g_aSkill.pos.y-SKILLNAME_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aSkill.pos.x-SKILLNAME_WIDTH,g_aSkill.pos.y+SKILLNAME_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aSkill.pos.x+SKILLNAME_WIDTH,g_aSkill.pos.y+SKILLNAME_HEIGHT, 0.0f);
																			
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
	pVtx[1].tex = D3DXVECTOR2(1.0f/6.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 6.0f, 1.0f);

	pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B

//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSkillName->Unlock();
}

//==========================
//�X�L���l�[���̏I������
//==========================
void UninitSkillName(void)
{
	//�e�N�X�`���̔j��

	if (g_apTextureSkillName != NULL)
	{
		g_apTextureSkillName->Release();
		g_apTextureSkillName = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSkillName != NULL)
	{
		g_pVtxBuffSkillName->Release();
		g_pVtxBuffSkillName = NULL;
	}
}

//==================================
//�X�L���l�[���̍X�V����
//==================================
void UpdateSkillName(void)
{

	//================================
	//�擾�����\����
	//================================
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();

	//==========================================================
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSkillName->Lock(0, 0, (void**)&pVtx, 0);


	if (GetKeyboardTrigger(DIK_N)==true||GetJoyPadTrigger(JOYKEY_Y)==true)
	{//�X�L���I��p�ϐ��i�œ_���E�ɃX���C�h�j
		PlaySound(SOUND_LABEL_SE_SELECT_000);
		g_aSkill.nSkillType++;
		//PlaySound(SOUND_LABEL_SE_SELECT_000);
	}
	if (GetKeyboardTrigger(DIK_B) == true)
	{//�X�L���I��p�ϐ��i�œ_���E�ɃX���C�h�j
		PlaySound(SOUND_LABEL_SE_SELECT_000);

		g_aSkill.nSkillType--;
		//PlaySound(SOUND_LABEL_SE_SELECT_000);
	}

	if (g_aSkill.nSkillType > 5)
	{
		g_aSkill.nSkillType = 0;
	}
	if (g_aSkill.nSkillType < 0)
	{
		g_aSkill.nSkillType = 5;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((1.0f / 6.0f) * g_aSkill.nSkillType, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 6.0f + (1.0f/6.0f) * g_aSkill.nSkillType, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / 6.0f) * g_aSkill.nSkillType, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 6.0f + (1.0f / 6.0f) * g_aSkill.nSkillType, 1.0f);


	if (pPlayer->pos.x >= g_aSkill.pos.x - SKILLNAME_WIDTH && pPlayer->pos.x <= g_aSkill.pos.x + SKILLNAME_WIDTH
		&& pPlayer->pos.y >= g_aSkill.pos.y - SKILLNAME_HEIGHT && pPlayer->pos.y <= g_aSkill.pos.y + SKILLNAME_HEIGHT)
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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSkillName->Unlock();
}

//==================================
//�X�L���l�[���̕`�揈��
//==================================
void DrawSkillName(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffSkillName, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_apTextureSkillName);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//======================================
//�X�L���l�[���\���̂̎擾
//======================================
Skill* GetSkill(void)
{
	return &g_aSkill;
}
