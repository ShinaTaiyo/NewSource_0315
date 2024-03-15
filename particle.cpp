//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Particle.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "particle.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "enemy.h"
#include "damage.h"

#define Particle_SCALE (10.0f)
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle[NUM_PARTICLE] = {};//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posParticle;//�ʒu
//D3DXVECTOR3 g_rotParticle;//����
D3DXMATRIX g_mtxWorldParticle;//���[���h�}�g���b�N�X(float4*4)

Particle g_aParticle[MAX_PARTICLE];//�e�̍\���̏��



//�^�C�g����ʂ̏���������
void InitParticle(void)
{


	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureParticle[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ChainFire.png",
		&g_pTextureParticle[1]);

	g_posParticle = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aParticle[nCntParticle].nLife = 0;//�̗�
		g_aParticle[nCntParticle].fRWidth = 0.0f;//���i���a�j
		g_aParticle[nCntParticle].fRHeight = 0.0f;//�����i���a�j
		g_aParticle[nCntParticle].nType = 0;//���
		g_aParticle[nCntParticle].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aParticle[nCntParticle].nIdxShadow = -1;//�e�̃C���f�b�N�X
		g_aParticle[nCntParticle].fScale = 0.0f;//�傫��
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�F
		g_aParticle[nCntParticle].fRedution = 0.0f;//�G�t�F�N�g������������X�s�[�h
		g_aParticle[nCntParticle].fRotMove = 0.0f;//���������̐��l�����߂�
		g_aParticle[nCntParticle].nType = 0;//�p�[�e�B�N���̎��
		g_aParticle[nCntParticle].nTexType;//�p�[�e�B�N���̃e�N�X�`���̎��
		g_aParticle[nCntParticle].nAnimationPattern = 0;//�A�j���[�V�����p�^�[��
		g_aParticle[nCntParticle].nAnimaitonCount = 0;//�A�j���[�V�����J�E���g
	}




	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-Particle_SCALE, Particle_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Particle_SCALE, Particle_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-Particle_SCALE, -Particle_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Particle_SCALE, -Particle_SCALE, 0.0f);

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
	g_pVtxBuffParticle->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitParticle(void)
{
	for (int nCnt = 0; nCnt < NUM_PARTICLE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureParticle[nCnt] != NULL)
		{
			g_pTextureParticle[nCnt]->Release();
			g_pTextureParticle[nCnt] = NULL;
		}
		
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateParticle(void)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{

		if (g_aParticle[nCntParticle].bUse == true)
		{
			Enemy* pEnemy = GetEnemy();

			g_aParticle[nCntParticle].nLife -= 1;

			g_aParticle[nCntParticle].fScale -= g_aParticle[nCntParticle].fRedution;

			

			if (g_aParticle[nCntParticle].nType == PARTICLETYPE_GRAVITY)
			{
				g_aParticle[nCntParticle].move.y += -1.0f;
			}

			if (g_aParticle[nCntParticle].nTexType == PARTICLETEX_NORMAL)
			{
				//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aParticle[nCntParticle].nTexType == PARTICLETEX_CHAINFIRE)
			{

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fScale >= pEnemy->pos.x - pEnemy->Size.x / 2 &&
							g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fScale <= pEnemy->pos.x + pEnemy->Size.x / 2 &&
							g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fScale >= pEnemy->pos.y - pEnemy->Size.y / 2 &&
							g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fScale <= pEnemy->pos.y + pEnemy->Size.y / 2 &&
							g_aParticle[nCntParticle].pos.z + g_aParticle[nCntParticle].fScale >= pEnemy->pos.z - pEnemy->Size.z / 2 &&
							g_aParticle[nCntParticle].pos.z - g_aParticle[nCntParticle].fScale <= pEnemy->pos.z + pEnemy->Size.z / 2)
						{
							pEnemy->nHp -= 8;
							g_aParticle[nCntParticle].bUse = false;
							SetDamage(8, 100, pEnemy->pos, 10.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								float fRandumRot = float(rand() % 200 + 1) / 100;
								float fRandumSpeed = float(rand() % 50) / 10;
								float fRandumMove = float(rand() % 21 - 10);
								float fLength = float(rand() % 100 + 100);
								float fRandumPos = float(rand() % 100 + 50);

								int nFlag = rand() % 2 + 1;

								float fSave = fRandumPos;

								if (nFlag == 2)
								{
									fRandumPos = -fSave;
								}
								 
								SetParticle(PARTICLETYPE_NORMAL, 100, 30.0f, 0.4f, 
									D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(-D3DX_PI * fRandumRot) * fLength,g_aParticle[nCntParticle].pos.y + fRandumPos,g_aParticle[nCntParticle].pos.z +  cosf(-D3DX_PI * fRandumRot) * fLength),
									D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed,fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
									D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), 0.0f, PARTICLETEX_CHAINFIRE);

							/*	SetParticle(PARTICLETYPE_NORMAL, 100, 30.0f, 0.1f,
								    g_aParticle[nCntParticle].pos,
									D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, PARTICLETEX_CHAINFIRE);*/
							}
						}
					}
				}

				g_aParticle[nCntParticle].nAnimaitonCount++;

				if (g_aParticle[nCntParticle].nAnimaitonCount % 5 == 0)
				{
					g_aParticle[nCntParticle].nAnimationPattern++;
					if (g_aParticle[nCntParticle].nAnimationPattern >= 5)
					{
						g_aParticle[nCntParticle].nAnimationPattern = 0;
					}
				}


				//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 1.0f);
			}


			//���_���W�̐ݒ�i�����ʒu�j
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fScale, g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fScale, g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fScale, -g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fScale, -g_aParticle[nCntParticle].fScale, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
			g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;
			g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

			if (g_aParticle[nCntParticle].nLife <= 0 || g_aParticle[nCntParticle].fScale <= 0.0f)
			{
				g_aParticle[nCntParticle].bUse = false;//�̗͂��O�ɂȂ�����false�ɂ���
			}
		}

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

			D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldParticle);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldParticle, NULL, &mtxView);

			//�t�s������߂�
			g_mtxWorldParticle._41 = 0.0f;
			g_mtxWorldParticle._42 = 0.0f;
			g_mtxWorldParticle._43 = 0.0f;

			////�����𔽉f
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotParticle.y, g_rotParticle.x, g_rotParticle.z);

			//D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldParticle);

		


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���C�g�𖳌��ɂ���
			

			//a�u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			for (int nCnt = 0; nCnt < NUM_PARTICLE; nCnt++)
			{
				if (g_aParticle[nCntParticle].nTexType== nCnt)
				{
					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureParticle[nCnt]);
				}
			}
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntParticle * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u

			//a�u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

void SetParticle(int nType, int nLife, float fScale, float fRedution, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRotMove, int nTexType)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aParticle[nCntParticle].pos = pos;//�ʒu
			g_aParticle[nCntParticle].move = move;//�ړ���
			g_aParticle[nCntParticle].col = col;//�F
			g_aParticle[nCntParticle].fRotMove = fRotMove;//���������̐��l�����߂�
			g_aParticle[nCntParticle].nLife = nLife;//�̗�
			g_aParticle[nCntParticle].nType = nType;//���
			g_aParticle[nCntParticle].nTexType = nTexType;//�p�[�e�B�N���̃e�N�X�`���̎��
			g_aParticle[nCntParticle].fScale = fScale;//�傫��
			g_aParticle[nCntParticle].fRedution = fRedution;//�G�t�F�N�g������������X�s�[�h
			g_aParticle[nCntParticle].nAnimationPattern = 0;//�A�j���[�V�����p�^�[��
			g_aParticle[nCntParticle].nAnimaitonCount = 0;//�A�j���[�V�����J�E���g

			break;
		}
	}
}
