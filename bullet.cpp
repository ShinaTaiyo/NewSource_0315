//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Bullet.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "bullet.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "damage.h"
#include "SkillGage.h"
#define BULLET_SCALE (10.0f)
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posBullet;//�ʒu
//D3DXVECTOR3 g_rotBullet;//����
D3DXMATRIX g_mtxWorldBullet;//���[���h�}�g���b�N�X(float4*4)

Bullet g_aBullet[MAX_BULLET];//�e�̍\���̏��

int g_nDelayBullet = 0;

//�^�C�g����ʂ̏���������
void InitBullet(void)
{
	g_nDelayBullet = 0;

	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\lightbrueball_enemy.png",
		&g_pTextureBullet[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\redball_enemy.png",
		&g_pTextureBullet[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\greenball_enemy.png",
		&g_pTextureBullet[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\purpleball_enemy.png",
		&g_pTextureBullet[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PinkBall.png",
		&g_pTextureBullet[4]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\orangeBall_enemy.png",
		&g_pTextureBullet[5]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BrackBall.png",
		&g_pTextureBullet[6]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RingBall.png",
		&g_pTextureBullet[7]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\RingChainBall.png",
		&g_pTextureBullet[8]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ChaosBall.png",
		&g_pTextureBullet[9]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\FireBall.png",
		&g_pTextureBullet[10]);



	g_posBullet = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aBullet[nCntBullet].nLife = 0;//�̗�
		g_aBullet[nCntBullet].fRWidth = 0.0f;//���i���a�j
		g_aBullet[nCntBullet].fRHeight = 0.0f;//�����i���a�j
		g_aBullet[nCntBullet].nType = 0;//���
		g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aBullet[nCntBullet].nNumEnemy = 0;//���Ԃ̓G�������Ă��Ă��邩
		g_aBullet[nCntBullet].fLength = 0.0f;//����
		g_aBullet[nCntBullet].bOneFlag = false;
		g_aBullet[nCntBullet].bChangeFlag = false;//�l���㉺�����鎞�Ɏg��
	}

	


	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SCALE, BULLET_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SCALE, BULLET_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SCALE, -BULLET_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SCALE, -BULLET_SCALE, 0.0f);

		//nor�̐ݒ�i�����ݒ�j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B

		//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	for (int nCntBullet = 0; nCntBullet < NUM_BULLET; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateBullet(void)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	g_nDelayBullet++;

	for (int nCnfBullet = 0; nCnfBullet < MAX_BULLET; nCnfBullet++)
	{

		if (g_aBullet[nCnfBullet].bUse == true)
		{
			Wall* pWall = GetWall();
			Player* pPlayer = GetPlayer();
			Enemy* pEnemy = GetEnemy();
			switch (g_aBullet[nCnfBullet].nType)
			{
			case BULLETTYPE_NORMAL:
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pEnemy->pos.x - pEnemy->Size.x / 2 &&
							g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pEnemy->pos.x + pEnemy->Size.x / 2 &&
							g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pEnemy->pos.y - pEnemy->Size.y / 2 &&
							g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pEnemy->pos.y + pEnemy->Size.y / 2 &&
							g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pEnemy->pos.z - pEnemy->Size.z / 2 &&
							g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pEnemy->pos.z + pEnemy->Size.z / 2)
						{
						/*	pEnemy->nHp -= 1;*/
							SetDamageEnemy(1, nCntEnemy);
							g_aBullet[nCnfBullet].bUse = false;
							SetDamage(1, 100, pEnemy->pos, 5.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
							AddSkillGage(0.5f);
						}
					}


				}
				SetEffect(0, 10, 20.0f, 2.0f,
					g_aBullet[nCnfBullet].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0.0f);

				if (g_aBullet[nCnfBullet].bUse == false)
				{
					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			case BULLETTYPE_ENEMY:
				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(5);

					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(5, 100, pPlayer->pos, 5.0f,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			case BULLETTYPE_SWING:

				g_aBullet[nCnfBullet].rot.y += 0.02f;

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true && g_aBullet[nCnfBullet].nNumEnemy == nCntEnemy)
					{
						g_aBullet[nCnfBullet].pos = D3DXVECTOR3(pEnemy->pos.x + sinf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * g_aBullet[nCnfBullet].fLength,
							pEnemy->pos.y + pEnemy->Size.y / 2, pEnemy->pos.z + cosf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * g_aBullet[nCnfBullet].fLength);
					}
				}

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(10);
					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(10, 100, pPlayer->pos,15.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}
				break;
			case BULLETTYPE_RANDUM:
				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(7);
					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(7, 400, pPlayer->pos, 5.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed,0.0f, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}

				if (g_aBullet[nCnfBullet].pos.y <= 0.0f)
				{
					g_aBullet[nCnfBullet].bUse = false;
				}
				break;
			case BULLETTYPE_CURVE:

				g_aBullet[nCnfBullet].rot.y += 0.0045f;

				g_aBullet[nCnfBullet].move = D3DXVECTOR3(sinf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * 9.0f, 0.0f, cosf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * 9.0f);

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(4);

					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(4, 360, pPlayer->pos, 5.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, 0.0f, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}

				if (g_aBullet[nCnfBullet].pos.y <= 0.0f)
				{
					g_aBullet[nCnfBullet].bUse = false;
				}
				break;
			case BULLETTYPE_WALL:
				if (g_nDelayBullet % 60 == 0)
				{
					SetBullet(BULLETTYPE_ENEMY,
						60, 15.0f, 15.0f, g_aBullet[nCnfBullet].pos,
						D3DXVECTOR3(sinf(g_aBullet[nCnfBullet].rot.y + D3DX_PI / 2) * 3.0f, 0.0f, cosf(g_aBullet[nCnfBullet].rot.y + D3DX_PI / 2) * 3.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 0.0f);

					SetBullet(BULLETTYPE_ENEMY,
						60, 15.0f, 15.0f, g_aBullet[nCnfBullet].pos,
						D3DXVECTOR3(sinf(g_aBullet[nCnfBullet].rot.y - D3DX_PI / 2) * 3.0f, 0.0f, cosf(g_aBullet[nCnfBullet].rot.y - D3DX_PI / 2) * 3.0f),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1, 0.0f);
				}

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(20);

					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(30, 300, pPlayer->pos, 50.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			case BULLETTYPE_BOUND:
			
				g_aBullet[nCnfBullet].move.y += -0.6f;
				if (g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= 0.0f)
				{
					g_aBullet[nCnfBullet].move.y = 12.0f;
				}
				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight>= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight<= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(9);

					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(8, 100, pPlayer->pos, 10.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			case BULLETTYPE_RING:

				if (g_aBullet[nCnfBullet].bOneFlag == true)
				{
					for (int nCnt = 0; nCnt < 8; nCnt++)
					{
						float fRot = (2.0f / 8) * nCnt;
						SetBullet(BULLETTYPE_CHAINRING, 1000, 10.0f, 10.0f, D3DXVECTOR3(g_aBullet[nCnfBullet].pos.x + sinf(-D3DX_PI * fRot) * 50.0f, g_aBullet[nCnfBullet].pos.y + sinf(-D3DX_PI * fRot) * 50.0f, g_aBullet[nCnfBullet].pos.z + cosf(-D3DX_PI * fRot) * 50.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,fRot, 0.0f), nCnfBullet, 50.0f);
					}
					g_aBullet[nCnfBullet].bOneFlag = false;
				}

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(12);
					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(15, 100, pPlayer->pos, 40.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			case BULLETTYPE_CHAINRING:

				if (g_aBullet[nCnfBullet].bChangeFlag == false)
				{
					g_aBullet[nCnfBullet].fLength += 3.0f;
				}
				else if (g_aBullet[nCnfBullet].bChangeFlag == true)
				{
					g_aBullet[nCnfBullet].fLength -= 3.0f;
				}

				if (g_aBullet[nCnfBullet].fLength >= 100.0f)
				{
					g_aBullet[nCnfBullet].bChangeFlag = true;
				}
				else if (g_aBullet[nCnfBullet].fLength <= 0.0f)
				{
					g_aBullet[nCnfBullet].bChangeFlag = false;
				}

				if (g_aBullet[g_aBullet[nCnfBullet].nNumEnemy].nType == BULLETTYPE_RING)
				{
					g_aBullet[nCnfBullet].pos = D3DXVECTOR3(g_aBullet[g_aBullet[nCnfBullet].nNumEnemy].pos.x + sinf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * g_aBullet[nCnfBullet].fLength,
						g_aBullet[g_aBullet[nCnfBullet].nNumEnemy].pos.y + tanf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * g_aBullet[nCnfBullet].fLength,
						g_aBullet[g_aBullet[nCnfBullet].nNumEnemy].pos.z + cosf(-D3DX_PI * g_aBullet[nCnfBullet].rot.y) * g_aBullet[nCnfBullet].fLength);
				}

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(13);
					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(15, 100, pPlayer->pos, 40.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}

				if (g_aBullet[g_aBullet[nCnfBullet].nNumEnemy].bUse == false)
				{
					g_aBullet[nCnfBullet].bUse = false;
				}

				break;
			case BULLETTYPE_CHAOS:

				g_aBullet[nCnfBullet].move.y += -0.2f;

				if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.x - pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.x + pPlayer->Size.x / 2 &&
					g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pPlayer->pos.y - pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pPlayer->pos.y + pPlayer->Size.y / 2 &&
					g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pPlayer->pos.z - pPlayer->Size.z / 2 &&
					g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pPlayer->pos.z + pPlayer->Size.z / 2)
				{
					SetDamagePlayer(25);
					g_aBullet[nCnfBullet].bUse = false;
					SetDamage(25, 100, pPlayer->pos, 60.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				if (g_aBullet[nCnfBullet].pos.y <= 0.0f)
				{
					g_aBullet[nCnfBullet].bUse = false;
				}
				break;
			case BULLETTYPE_FIRE:
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aBullet[nCnfBullet].pos.x + g_aBullet[nCnfBullet].fRWidth >= pEnemy->pos.x - pEnemy->Size.x / 2 &&
							g_aBullet[nCnfBullet].pos.x - g_aBullet[nCnfBullet].fRWidth <= pEnemy->pos.x + pEnemy->Size.x / 2 &&
							g_aBullet[nCnfBullet].pos.y + g_aBullet[nCnfBullet].fRHeight >= pEnemy->pos.y - pEnemy->Size.y / 2 &&
							g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight <= pEnemy->pos.y + pEnemy->Size.y / 2 &&
							g_aBullet[nCnfBullet].pos.z + g_aBullet[nCnfBullet].fRWidth >= pEnemy->pos.z - pEnemy->Size.z / 2 &&
							g_aBullet[nCnfBullet].pos.z - g_aBullet[nCnfBullet].fRWidth <= pEnemy->pos.z + pEnemy->Size.z / 2)
						{
							pEnemy->nHp -= 25;
							g_aBullet[nCnfBullet].bUse = false;
							SetDamage(25, 100, pEnemy->pos, 25.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								float fRandumRot = float(rand() % 200 + 1) / 100;
								float fRandumSpeed = float(rand() % 50) / 10;
								float fRandumMove = float(rand() % 21 - 10);
								SetParticle(PARTICLETYPE_NORMAL, 180, 25.0f, 0.1f, g_aBullet[nCnfBullet].pos, D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
									D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), 0.0f, PARTICLETEX_CHAINFIRE);
							}
						}
					}


				}
				SetEffect(0, 10, 20.0f, 2.0f,
					g_aBullet[nCnfBullet].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0.0f);

				if (g_aBullet[nCnfBullet].bUse == false)
				{
					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aBullet[nCnfBullet].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
				break;
			}

		

			g_aBullet[nCnfBullet].nLife -= 1;

		

			

			g_aBullet[nCnfBullet].pos += g_aBullet[nCnfBullet].move;
			if (g_aBullet[nCnfBullet].nLife <= 0)
			{
				g_aBullet[nCnfBullet].bUse = false;//�̗͂��O�ɂȂ�����false�ɂ���
			}

			
			
			
			SetPositionShadow(g_aBullet[nCnfBullet].nIdxShadow,D3DXVECTOR3(g_aBullet[nCnfBullet].pos.x,g_aBullet[nCnfBullet].pos.y - g_aBullet[nCnfBullet].fRHeight,g_aBullet[nCnfBullet].pos.z),nCnfBullet,-1,D3DXCOLOR(1.0f,1.0f,1.0f,1.0));
			
			if (g_aBullet[nCnfBullet].bUse == false)
			{
				KillShadow(g_aBullet[nCnfBullet].nIdxShadow);
			}



		
		}

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();



	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].pos.y >= 0.0f)
			{
				D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

				D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldBullet);

				//�r���[�}�g���b�N�X���擾
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
				D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);

				//�t�s������߂�
				g_mtxWorldBullet._41 = 0.0f;
				g_mtxWorldBullet._42 = 0.0f;
				g_mtxWorldBullet._43 = 0.0f;

				////�����𔽉f
				//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBullet.y, g_rotBullet.x, g_rotBullet.z);

				//D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
				D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

				//���C�g�𖳌��ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);


				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				for (int nCntTexture = 0; nCntTexture < NUM_BULLET; nCntTexture++)
				{
					if (g_aBullet[nCntBullet].nType == nCntTexture)
					{
						//�e�N�X�`���̐ݒ�
						pDevice->SetTexture(0, g_pTextureBullet[nCntTexture]);
					}
				}
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u

				//���C�g��L���ɖ߂�
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
		}
	}
}

void SetBullet(int nType, int nLife, float fRWidth, float fRHeight, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, int nNumEnemy, float fLength)
{

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aBullet[nCntBullet].pos = pos;//�ʒu
			g_aBullet[nCntBullet].move = move;//�ړ���
			g_aBullet[nCntBullet].rot = rot;//����
			g_aBullet[nCntBullet].nLife = nLife;//�̗�
			g_aBullet[nCntBullet].fRWidth = fRWidth;//���i���a�j
			g_aBullet[nCntBullet].fRHeight = fRHeight;//�����i���a�j
			g_aBullet[nCntBullet].nType = nType;//���
			g_aBullet[nCntBullet].nNumEnemy = nNumEnemy;
			g_aBullet[nCntBullet].fLength = fLength;
			g_aBullet[nCntBullet].bOneFlag = true;//��x�������������鏈���p�t���O
			g_aBullet[nCntBullet].bChangeFlag = false;//�l���㉺�����鎞�Ɏg��
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			//���_���W�̐ݒ�i�����ʒu�j
			pVtx[0].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fRWidth, g_aBullet[nCntBullet].fRHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fRWidth, g_aBullet[nCntBullet].fRHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aBullet[nCntBullet].fRWidth, -g_aBullet[nCntBullet].fRHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].fRWidth, -g_aBullet[nCntBullet].fRHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

Bullet* GetBullet(void)//�e�\���̂̏����Q�b�g����
{
	return &g_aBullet[0];
}

