//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[bg.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "main.h"
#include "bg.h"

//�}�N����`
#define NUM_BG (1)//�w�i�̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};//�e�N�X�`��3�����̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexV[NUM_BG];//�e�N�X�`�����W�̊J�n�ʒu�iV�l�j

float g_fColorChangeBg;

//============================
//�w�i�̏���������
//============================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;

	g_fColorChangeBg = 0.0f;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\Game_bg.png",
		&g_apTextureBG[0]);

	//====================================
	//�w�i�𕡐����g�������Ȃ�����g��
	//====================================
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\new_bg_000.png",
	//	&g_apTextureBG[1]);

	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\new_bg_001.png",
	//	&g_apTextureBG[2]);
	//==============================================================

	//�e�N�X�`�����W�̊J�n�ʒu�iV�l�j�̏�����
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexV[nCntBG] = 0.0f;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,//�S�͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
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
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,g_aPosTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f,g_aPosTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f,g_aPosTexV[nCntBG]+1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,g_aPosTexV[nCntBG]+1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
		
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//==========================
//�w�i�̏I������
//==========================
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_apTextureBG[nCntBG] != NULL)
		{
			g_apTextureBG[nCntBG]->Release();
			g_apTextureBG[nCntBG] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//==================================
//�w�i�̍X�V����
//==================================
void UpDateBG(void)
{
	int nCntBG;

	VERTEX_2D* pVtx;

	g_fColorChangeBg = 1.0f;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`�����W�̐ݒ�

		switch (nCntBG)
		{
		case 0:
			/*g_aPosTexV[nCntBG] -= 0.0025f;*/ //�w�i�����������Ȃ�g���B



			pVtx[0].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[1].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[2].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
			pVtx[3].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 1.0f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B


			/*pVtx[0].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG]);
			pVtx[1].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG]);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG] + 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG] + 1.0f);*/

			break;


			//==================================
			//�g�������Ȃ�����g��
			//==================================

		//case 1:
		//	g_aPosTexV[nCntBG] -= 0.004f;



		//	pVtx[0].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[1].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[2].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[3].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B


		//	pVtx[0].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG]);
		//	pVtx[1].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG]);
		//	pVtx[2].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG] + 1.0f);
		//	pVtx[3].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG] + 1.0f);

		//	break;

		//case 2:
		//	g_aPosTexV[nCntBG] -= 0.006f;



		//	pVtx[0].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[1].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[2].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
		//	pVtx[3].col = D3DXCOLOR(g_fColorChangeBg, g_fColorChangeBg, g_fColorChangeBg, 0.2f);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B


		//	pVtx[0].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG]);
		//	pVtx[1].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG]);
		//	pVtx[2].tex = D3DXVECTOR2(0.0f, g_aPosTexV[nCntBG] + 1.0f);
		//	pVtx[3].tex = D3DXVECTOR2(1.0f, g_aPosTexV[nCntBG] + 1.0f);

		//	break;
		}

		//============================================================================================================================================

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//==================================
//�w�i�̕`�揈��
//==================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

		//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntBG * 4,
			2);
	}
}