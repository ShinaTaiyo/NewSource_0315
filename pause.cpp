//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[pause.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "result.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "pause.h"


#define COMMAND_SIZE_X (76.0f)
#define COMMAND_SIZE_Y (38.0f)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE_TEX] = {};//�e�N�X�`���ւ̃|�C���^
//VERTEX_2D g_aVertex[4];//���_�����i�[�i�l�p�`����肽���j
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//���_�o�b�t�@�ւ̃|�C���^

Pause g_aPause[MAX_PAUSE_TEX];



//���U���g��ʂ̏���������
void InitPause(void)
{
	int nCntPause;

	

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\3DGame_Pause.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\CONTINE_indicate.png",
		&g_pTexturePause[1]);


	D3DXCreateTextureFromFile(pDevice,
		"data\\RETRY_indicate.png",
		&g_pTexturePause[2]);


	D3DXCreateTextureFromFile(pDevice,
		"data\\QUIT_indicate.png",
		&g_pTexturePause[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE_TEX,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	for (nCntPause = 1; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{
		
		g_aPause[nCntPause].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f,SCREEN_HEIGHT / 2  + 90.0f + 80.0f * nCntPause, 0.0f);//�^�񒆂ɎO�i�I�v�V�����R�}���h��p�ӂ���B
	}
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntPause = 0; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		g_aPause[nCntPause].nPauseMenu = nCntPause;//4�̃|���S���Ƀe�N�X�`�������蓖�Ă�B
		g_aPause[nCntPause].bChooseMenu = false;
		if (g_aPause->nPauseMenu == PAUSE_MENU_INDICATE)
		{//��ʑS�̂ɕ\������e�N�X�`��
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
		}
		else
		{//�R�}���h�̈ʒu���̏�����
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);




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
		}

		pVtx += 4;//���_���W�̃|�C���^���C���N�������g
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//==============================
//���U���g��ʂ̏I������
//==============================
void UninitPause(void)
{
	int nCntPause;
	//�e�N�X�`���̔j��
	for (nCntPause = 0; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//===================================
//���U���g��ʂ̍X�V����
//===================================
void UpdatePause(void)
{
	int nCntPause;
	VERTEX_2D* pVtx;





	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPause = 0; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{
		//���_���W�̐ݒ�i�����ʒu�j

		if (g_aPause[nCntPause].nPauseMenu >=PAUSE_MENU_CONTINUE&&g_aPause[nCntPause].nPauseMenu<=PAUSE_MENU_QUIT)
		{//�|�[�Y��ʃe�N�X�`���ȊO�̃R�}���h�̈ʒu�����肷��B


			pVtx[0].pos = D3DXVECTOR3(g_aPause[nCntPause].pos.x- COMMAND_SIZE_X,g_aPause[nCntPause].pos.y-COMMAND_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aPause[nCntPause].pos.x+ COMMAND_SIZE_X,g_aPause[nCntPause].pos.y-COMMAND_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aPause[nCntPause].pos.x- COMMAND_SIZE_X,g_aPause[nCntPause].pos.y+COMMAND_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aPause[nCntPause].pos.x+ COMMAND_SIZE_X,g_aPause[nCntPause].pos.y+COMMAND_SIZE_Y, 0.0f);

			//���_�J���[�̐ݒ�i�����ݒ�j
			pVtx[0].col = D3DCOLOR_RGBA(255,255,255,100);
			pVtx[1].col = D3DCOLOR_RGBA(255,255,255,100);
			pVtx[2].col = D3DCOLOR_RGBA(255,255,255,100);
			pVtx[3].col = D3DCOLOR_RGBA(255,255,255,100);
		}
		if (g_aPause[nCntPause].bChooseMenu == true)
		{
			//���_�J���[�̐ݒ�i�I�����Ă���R�}���h�����邭�Ȃ�j
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		pVtx += 4;//���_���W�̃|�C���^���C���N�������g
	}
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	int nCntPause;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntPause = 0; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		if (g_aPause[nCntPause].nPauseMenu == PAUSE_MENU_INDICATE)
		{
			pDevice->SetTexture(0, g_pTexturePause[PAUSE_MENU_INDICATE]);
		}
		if (g_aPause[nCntPause].nPauseMenu == PAUSE_MENU_CONTINUE)
		{
			pDevice->SetTexture(0, g_pTexturePause[PAUSE_MENU_CONTINUE]);
		}
		if (g_aPause[nCntPause].nPauseMenu == PAUSE_MENU_RETRY)
		{
			pDevice->SetTexture(0, g_pTexturePause[PAUSE_MENU_RETRY]);
		}
		if (g_aPause[nCntPause].nPauseMenu == PAUSE_MENU_QUIT)
		{
			pDevice->SetTexture(0, g_pTexturePause[PAUSE_MENU_QUIT]);
		}
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
			//&g_pVtxBuffPolygon[0],//���_���̐擪�A�h���X
			//sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
	}
}

//================================
//���U���g��ʕ����\���̂̎擾
//================================

void SetEnablePause(int nType)
{
	int nCntPause;
	for (nCntPause = 0; nCntPause < MAX_PAUSE_TEX; nCntPause++)
	{//�Z�b�g����邽�тɃ|�[�Y�̖��邭�\������t���O��false�ɂ���B
		g_aPause[nCntPause].bChooseMenu = false;
	}
	//�Z�b�g���ꂽ�Ƃ��ɁA�������ŌĂяo�����|�[�Y���j���[�����邭�\�������B
	g_aPause[nType].bChooseMenu = true;
}