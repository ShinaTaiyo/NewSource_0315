//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[AttackBillBoard.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "AttackBillBoard.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"
#include "enemy.h"
#include "damage.h"
#include "SkillGage.h"
#include "player.h"

#define ATTACKBILLBOARD_SCALE (10.0f)
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttackBillBoard = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureAttackBillBoard[NUM_ATTACKBILLBOARD] = {};//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posAttackBillBoard;//�ʒu
//D3DXVECTOR3 g_rotAttackBillBoard;//����
D3DXMATRIX g_mtxWorldAttackBillBoard;//���[���h�}�g���b�N�X(float4*4)

AttackBillBoard g_aAttackBillBoard[MAX_ATTACKBILLBOARD];//�e�̍\���̏��

int g_nDelayA_Billboard = 0;//�U���r���{�[�h�̒x�点��J�E���g����

//�^�C�g����ʂ̏���������
void InitAttackBillBoard(void)
{

	g_nDelayA_Billboard = 0;
	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\AttackMotion_Thunder.png",
		&g_pTextureAttackBillBoard[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Skill_Slash.png",
		&g_pTextureAttackBillBoard[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\AtomicSlash.png",
		&g_pTextureAttackBillBoard[2]);


	g_posAttackBillBoard = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ATTACKBILLBOARD,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAttackBillBoard,
		NULL);

	for (int nCntAttackBillBoard = 0; nCntAttackBillBoard < MAX_ATTACKBILLBOARD; nCntAttackBillBoard++)
	{
		g_aAttackBillBoard[nCntAttackBillBoard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aAttackBillBoard[nCntAttackBillBoard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aAttackBillBoard[nCntAttackBillBoard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aAttackBillBoard[nCntAttackBillBoard].nLife = 0;//�̗�
		g_aAttackBillBoard[nCntAttackBillBoard].fRWidth = 0.0f;//���i���a�j
		g_aAttackBillBoard[nCntAttackBillBoard].fRHeight = 0.0f;//�����i���a�j
		g_aAttackBillBoard[nCntAttackBillBoard].nType = 0;//���
		g_aAttackBillBoard[nCntAttackBillBoard].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aAttackBillBoard[nCntAttackBillBoard].nIdxShadow = -1;//�e�̃C���f�b�N�X
		g_aAttackBillBoard[nCntAttackBillBoard].nAnimationCnt = 0;//�A�j���[�V�����J�E���g
		g_aAttackBillBoard[nCntAttackBillBoard].nAnimationPattern = 0;//�A�j���[�V�����p�^�[��
		g_aAttackBillBoard[nCntAttackBillBoard].bOneFlag = false;//��x�������������鏈���p
		g_aAttackBillBoard[nCntAttackBillBoard].SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu��ۑ�����

	}




	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAttackBillBoard->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntAttackBillBoard = 0; nCntAttackBillBoard < MAX_ATTACKBILLBOARD; nCntAttackBillBoard++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-ATTACKBILLBOARD_SCALE, ATTACKBILLBOARD_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ATTACKBILLBOARD_SCALE, ATTACKBILLBOARD_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ATTACKBILLBOARD_SCALE, -ATTACKBILLBOARD_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ATTACKBILLBOARD_SCALE, -ATTACKBILLBOARD_SCALE, 0.0f);

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
	g_pVtxBuffAttackBillBoard->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitAttackBillBoard(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < NUM_ATTACKBILLBOARD; nCnt++)
	{
		if (g_pTextureAttackBillBoard[nCnt] != NULL)
		{
			g_pTextureAttackBillBoard[nCnt]->Release();
			g_pTextureAttackBillBoard[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffAttackBillBoard != NULL)
	{
		g_pVtxBuffAttackBillBoard->Release();
		g_pVtxBuffAttackBillBoard = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateAttackBillBoard(void)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAttackBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	Player* pPlayer = GetPlayer();

	for (int nCnfAttackBillBoard = 0; nCnfAttackBillBoard < MAX_ATTACKBILLBOARD; nCnfAttackBillBoard++)
	{

		if (g_aAttackBillBoard[nCnfAttackBillBoard].bUse == true)
		{
			g_aAttackBillBoard[nCnfAttackBillBoard].nLife -= 1;
			g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationCnt++;

			if (g_aAttackBillBoard[nCnfAttackBillBoard].nLife <= 0)
			{
				g_aAttackBillBoard[nCnfAttackBillBoard].bUse = false;//�̗͂��O�ɂȂ�����false�ɂ���
			}

			if (g_aAttackBillBoard[nCnfAttackBillBoard].nType == A_BILLBOARDTYPE_THUNDER)
			{
				Enemy* pEnemy = GetEnemy();
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						//�G�ƍU����X��Z�̋������Ƃ�
						float fLength = sqrtf((g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) +
							(g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z)) / 2;

						if (pEnemy->pos.y + pEnemy->Size.y >= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y - g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
							pEnemy->pos.y - pEnemy->Size.y <= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y + g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
							fLength <= 50.0f)
						{
							/*pEnemy->nHp -= 2;*/
							SetDamageEnemy(2, nCntEnemy);
							SetDamage(2, 100, pEnemy->pos, 20.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
					}
				}

				if (g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationCnt % 5 == 0)
				{
					g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern++;

					if (g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern >= 5)
					{
						g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern = 0;
					}
				}

				//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);

				if (g_aAttackBillBoard[nCnfAttackBillBoard].bUse == false)
				{
					for (int nCnt = 0; nCnt < 100; nCnt++)
					{
						float fRandumRot = float(rand() % 200 + 1) / 100;
						float fRandumSpeed = float(rand() % 100 + 30) / 10;
						float fRandumMove = float(rand() % 21 - 10);

						SetParticle(0, 1000, 20.0f, 0.1f, g_aAttackBillBoard[nCnfAttackBillBoard].pos,
							D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
							D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
					}
				}
			}
			else if (g_aAttackBillBoard[nCnfAttackBillBoard].nType == A_BILLBOARDTYPE_SLASH)
			{
				Enemy* pEnemy = GetEnemy();

				if (g_aAttackBillBoard[nCnfAttackBillBoard].bOneFlag == true)
				{//��񂾂��_���[�W��^����������
					for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)
						{
							//�G�ƍU����X��Z�̋������Ƃ�
							//�G�ƍU����X��Z�̋������Ƃ�
							float fLength = sqrtf((g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) +
								(g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z)) / 2;

							if (pEnemy->pos.y + pEnemy->Size.y >= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y - g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
								pEnemy->pos.y - pEnemy->Size.y <= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y + g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
								fLength < g_aAttackBillBoard[nCnfAttackBillBoard].fRWidth)
							{
								/*pEnemy->nHp -= 10;*/
								SetDamageEnemy(10, nCntEnemy);
								SetDamage(10, 100, pEnemy->pos, 50.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								g_aAttackBillBoard[nCnfAttackBillBoard].bOneFlag = false;
								AddSkillGage(6.5f);

								for (int nCnt = 0; nCnt < 2; nCnt++)
								{
									float fRandumRot = float(rand() % 200 + 1) / 100;
									float fRandumSpeed = float(rand() % 100 + 30) / 10;
									float fRandumMove = float(rand() % 21 - 10);

									SetParticle(0, 1000, 20.0f, 0.1f, g_aAttackBillBoard[nCnfAttackBillBoard].pos,
										D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
										D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
								}
							}
						}
					}
				}

				if (g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationCnt % 2 == 0)
				{
					g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern++;

					if (g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern >= 5)
					{
						g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern = 0;
					}
				}

				//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);
			}

			else if (g_aAttackBillBoard[nCnfAttackBillBoard].nType == A_BILLBOARDTYPE_ATOMICSLASH)
			{
				Enemy* pEnemy = GetEnemy();
					for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)
						{
							//�G�ƍU����X��Z�̋������Ƃ�
							//�G�ƍU����X��Z�̋������Ƃ�
							float fLength = sqrtf((g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.x - pEnemy->pos.x) +
								(g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z) * (g_aAttackBillBoard[nCnfAttackBillBoard].pos.z - pEnemy->pos.z)) / 2;

							if (pEnemy->pos.y + pEnemy->Size.y >= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y - g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
								pEnemy->pos.y - pEnemy->Size.y <= g_aAttackBillBoard[nCnfAttackBillBoard].pos.y + g_aAttackBillBoard[nCnfAttackBillBoard].fRHeight &&
								fLength < g_aAttackBillBoard[nCnfAttackBillBoard].fRWidth)
							{
							/*	pEnemy->nHp -= 25;*/
								SetDamageEnemy(25, nCntEnemy);
								pPlayer->nHp += 1;//�q�b�g����xHP���񕜂���
								SetDamage(25, 120, pEnemy->pos, 100.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
								AddSkillGage(1.7f);//�X�L���Q�[�W���u�[�X�g����
								for (int nCnt = 0; nCnt < 10; nCnt++)
								{
									float fRandumRot = float(rand() % 200 + 1) / 100;
									float fRandumSpeed = float(rand() % 100 + 30) / 10;
									float fRandumMove = float(rand() % 21 - 10);

									SetParticle(0, 1000, 15.0f, 0.2f, g_aAttackBillBoard[nCnfAttackBillBoard].pos,
										D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
										D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, PARTICLETEX_NORMAL);


								}
							}
						}
					}
				

				g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern++;

				if (g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern >= 5)
				{
					g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern = 0;
				}

				//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + 0.2f * g_aAttackBillBoard[nCnfAttackBillBoard].nAnimationPattern, 1.0f);
			}


		}

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffAttackBillBoard->Unlock();
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawAttackBillBoard(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();



	for (int nCntAttackBillBoard = 0; nCntAttackBillBoard < MAX_ATTACKBILLBOARD; nCntAttackBillBoard++)
	{
		if (g_aAttackBillBoard[nCntAttackBillBoard].bUse == true)
		{
			D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

			D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldAttackBillBoard);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldAttackBillBoard, NULL, &mtxView);

			//�t�s������߂�
			g_mtxWorldAttackBillBoard._41 = 0.0f;
			g_mtxWorldAttackBillBoard._42 = 0.0f;
			g_mtxWorldAttackBillBoard._43 = 0.0f;

			////�����𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotAttackBillBoard.y, g_rotAttackBillBoard.x, g_rotAttackBillBoard.z);

			//D3DXMatrixMultiply(&g_mtxWorldAttackBillBoard, &g_mtxWorldAttackBillBoard, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aAttackBillBoard[nCntAttackBillBoard].pos.x, g_aAttackBillBoard[nCntAttackBillBoard].pos.y, g_aAttackBillBoard[nCntAttackBillBoard].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldAttackBillBoard, &g_mtxWorldAttackBillBoard, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);



			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldAttackBillBoard);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffAttackBillBoard, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCnt = 0; nCnt < NUM_ATTACKBILLBOARD; nCnt++)
			{
				if (g_aAttackBillBoard[nCntAttackBillBoard].nType == nCnt)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureAttackBillBoard[nCnt]);
				}
			}
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntAttackBillBoard * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u

			//���C�g��L���ɖ߂�
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

void SetAttackBillBoard(int nType, int nLife, float fRWidth, float fRHeight, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot)
{

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAttackBillBoard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntAttackBillBoard = 0; nCntAttackBillBoard < MAX_ATTACKBILLBOARD; nCntAttackBillBoard++)
	{
		if (g_aAttackBillBoard[nCntAttackBillBoard].bUse == false)
		{
			g_aAttackBillBoard[nCntAttackBillBoard].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aAttackBillBoard[nCntAttackBillBoard].pos = pos;//�ʒu
			g_aAttackBillBoard[nCntAttackBillBoard].move = move;//�ړ���
			g_aAttackBillBoard[nCntAttackBillBoard].rot = rot;//����
			g_aAttackBillBoard[nCntAttackBillBoard].nLife = nLife;//�̗�
			g_aAttackBillBoard[nCntAttackBillBoard].fRWidth = fRWidth;//���i���a�j
			g_aAttackBillBoard[nCntAttackBillBoard].fRHeight = fRHeight;//�����i���a�j
			g_aAttackBillBoard[nCntAttackBillBoard].nType = nType;//���
			g_aAttackBillBoard[nCntAttackBillBoard].nAnimationCnt = 0;//�A�j���[�V�����J�E���g
			g_aAttackBillBoard[nCntAttackBillBoard].nAnimationPattern = 0;//�A�j���[�V�����p�^�[��
			g_aAttackBillBoard[nCntAttackBillBoard].bOneFlag = true;//�A�j���[�V�����p�^�[��
			g_aAttackBillBoard[nCntAttackBillBoard].SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu��ۑ�����

			//���_���W�̐ݒ�i�����ʒu�j
			pVtx[0].pos = D3DXVECTOR3(-g_aAttackBillBoard[nCntAttackBillBoard].fRWidth, g_aAttackBillBoard[nCntAttackBillBoard].fRHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aAttackBillBoard[nCntAttackBillBoard].fRWidth, g_aAttackBillBoard[nCntAttackBillBoard].fRHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aAttackBillBoard[nCntAttackBillBoard].fRWidth, -g_aAttackBillBoard[nCntAttackBillBoard].fRHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aAttackBillBoard[nCntAttackBillBoard].fRWidth, -g_aAttackBillBoard[nCntAttackBillBoard].fRHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffAttackBillBoard->Unlock();
}

AttackBillBoard* GetAttackBillBoard(void)//�e�\���̂̏����Q�b�g����
{
	return &g_aAttackBillBoard[0];
}

