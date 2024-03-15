//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Emitter.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "emitter.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "effect.h"
#include "AttackModel.h"

#define EMITTER_SCALE (10.0f)
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffEmitter = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEmitter = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posEmitter;//�ʒu
//D3DXVECTOR3 g_rotEmitter;//����
D3DXMATRIX g_mtxWorldEmitter;//���[���h�}�g���b�N�X(float4*4)

Emitter g_aEmitter[MAX_EMITTER];//�e�̍\���̏��



//�^�C�g����ʂ̏���������
void InitEmitter(void)
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
		&g_pTextureEmitter);

	g_posEmitter = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EMITTER,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEmitter,
		NULL);

	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		g_aEmitter[nCntEmitter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aEmitter[nCntEmitter].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aEmitter[nCntEmitter].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aEmitter[nCntEmitter].nLife = 0;//�̗�
		g_aEmitter[nCntEmitter].fRWidth = 0.0f;//���i���a�j
		g_aEmitter[nCntEmitter].fRHeight = 0.0f;//�����i���a�j
		g_aEmitter[nCntEmitter].nType = 0;//���
		g_aEmitter[nCntEmitter].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aEmitter[nCntEmitter].nIdxShadow = -1;//�e�̃C���f�b�N�X
		g_aEmitter[nCntEmitter].fScale = 0.0f;//�傫��
		g_aEmitter[nCntEmitter].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//�F
		g_aEmitter[nCntEmitter].fRedution = 0.0f;//�G�t�F�N�g������������X�s�[�h
		g_aEmitter[nCntEmitter].EmitterType = EMITTERTYPE_EFFECT;//�G�~�b�^�[�ŌĂяo�������̎��
		g_aEmitter[nCntEmitter].nSummonLife = 0;//�Ăяo�������̗̑�
		g_aEmitter[nCntEmitter].SummonMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEmitter[nCntEmitter].fRotMove = 0.0f;//���������̐��l�����߂�
		g_aEmitter[nCntEmitter].nNumAttack = -1;//�G�~�b�^�[���Ăяo���Ă���U���̔ԍ����i�[����
	}




	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEmitter->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-EMITTER_SCALE, EMITTER_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EMITTER_SCALE, EMITTER_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EMITTER_SCALE, -EMITTER_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EMITTER_SCALE, -EMITTER_SCALE, 0.0f);

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
	g_pVtxBuffEmitter->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitEmitter(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEmitter != NULL)
	{
		g_pTextureEmitter->Release();
		g_pTextureEmitter = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEmitter != NULL)
	{
		g_pVtxBuffEmitter->Release();
		g_pVtxBuffEmitter = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateEmitter(void)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEmitter->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{

		if (g_aEmitter[nCntEmitter].bUse == true)
		{

			//�̗͂����炷
			g_aEmitter[nCntEmitter].nLife -= 1;

			if (g_aEmitter[nCntEmitter].nType == EMITTERTYPE_CURVE)
			{
				g_aEmitter[nCntEmitter].fRotMove += 0.005f;

				g_aEmitter[nCntEmitter].move.x = sinf(D3DX_PI * g_aEmitter[nCntEmitter].fRotMove) * 5.0f;
				g_aEmitter[nCntEmitter].move.z = cosf(D3DX_PI * g_aEmitter[nCntEmitter].fRotMove) * 5.0f;

				//�ړ�����
				g_aEmitter[nCntEmitter].pos.x += g_aEmitter[nCntEmitter].move.x;
				g_aEmitter[nCntEmitter].pos.y += g_aEmitter[nCntEmitter].move.y;
				g_aEmitter[nCntEmitter].pos.z += g_aEmitter[nCntEmitter].move.z;
			}
			

			

			if (g_aEmitter[nCntEmitter].nType == EMITTERTYPE_TORNADO)
			{
				AttackModel* pAttackModel = GetAttackModel();
				g_aEmitter[nCntEmitter].fRotMove += 0.1f;

				g_aEmitter[nCntEmitter].move.y += 0.001f;
				g_aEmitter[nCntEmitter].fScale += 0.01f;
				for (int nCntAttackModel = 0; nCntAttackModel < MAX_ATTACKMODEL; nCntAttackModel++, pAttackModel++)
				{
					if (pAttackModel->bUse == true && g_aEmitter[nCntEmitter].nNumAttack == nCntAttackModel)
					{
						g_aEmitter[nCntEmitter].pos.x = sinf(-D3DX_PI * g_aEmitter[nCntEmitter].fRotMove) * 50.0f + pAttackModel->pos.x;
						g_aEmitter[nCntEmitter].pos.z = cosf(-D3DX_PI * g_aEmitter[nCntEmitter].fRotMove) * 50.0f + pAttackModel->pos.z;

						if (pAttackModel->nLife <= 1)
						{
							g_aEmitter[nCntEmitter].bUse = false;
						}
					}
				}
			}

			//g_aEmitter[nCntEmitter].fScale -= g_aEmitter[nCntEmitter].fRedution;//�傫��������������X�s�[�h



			//�G�t�F�N�g���Ăяo������
			/*if (g_aEmitter[nCntEmitter].EmitterType == EMITTERTYPE_EFFECT)*/
				SetEffect(0,
					g_aEmitter[nCntEmitter].nSummonLife,
					g_aEmitter[nCntEmitter].fScale,
					g_aEmitter[nCntEmitter].fRedution,
					g_aEmitter[nCntEmitter].pos,
					D3DXVECTOR3(0.0f,0.0f,0.0f),
					g_aEmitter[nCntEmitter].col,
					0.0f);
			
				//�ړ�����
				g_aEmitter[nCntEmitter].pos.x += g_aEmitter[nCntEmitter].move.x;
				g_aEmitter[nCntEmitter].pos.y += g_aEmitter[nCntEmitter].move.y;
				g_aEmitter[nCntEmitter].pos.z += g_aEmitter[nCntEmitter].move.z;

			//�g�p��Ԃ�false�ɂ���
			if (g_aEmitter[nCntEmitter].nLife <= 0 || g_aEmitter[nCntEmitter].fScale <= 0.0f)
			{
				g_aEmitter[nCntEmitter].bUse = false;//�̗͂��O�ɂȂ�����false�ɂ���
			}
		}

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEmitter->Unlock();
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawEmitter(void)
{

}

void SetEmitterEffect(int nType, int nLife, int nSummonLife, float fScale, float fRedution, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRotMove, int nNumAttack)
{
	for (int nCntEmitter = 0; nCntEmitter < MAX_EMITTER; nCntEmitter++)
	{
		if (g_aEmitter[nCntEmitter].bUse == false)
		{
			g_aEmitter[nCntEmitter].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aEmitter[nCntEmitter].pos = pos;//�ʒu
			g_aEmitter[nCntEmitter].move = move;//�ړ���
			g_aEmitter[nCntEmitter].col = col;//�F
			g_aEmitter[nCntEmitter].nLife = nLife;//�̗�
			g_aEmitter[nCntEmitter].nType = nType;//���
			g_aEmitter[nCntEmitter].fScale = fScale;//�傫��
			g_aEmitter[nCntEmitter].fRedution = fRedution;//�G�t�F�N�g������������X�s�[�h
			g_aEmitter[nCntEmitter].nSummonLife = nSummonLife;//�Ăяo�������̗̑�
			g_aEmitter[nCntEmitter].fRotMove = fRotMove;//���������̐��l�����߂�
			g_aEmitter[nCntEmitter].nNumAttack = nNumAttack;//�G�~�b�^�[���Ăяo���Ă���U���̔ԍ����i�[����

			break;
		}
	}
}
