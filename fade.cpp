//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[fade.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;//�e�N�X�`���ւ̃|�C���^
//VERTEX_2D g_aVertex[4];//���_�����i�[�i�l�p�`����肽���j
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//���_�o�b�t�@�ւ̃|�C���^


int g_colorFade_a;//�|���S���̐F�̓����x��ς���O���[�o���ϐ�


MODE g_ModeNext;//���̃��[�h��\���ϐ�

FADE g_fade;
//�^�C�g����ʂ̏���������
void InitFade(void)
{
	g_colorFade_a=255;//�|���S���̐F�̓����x��ς���O���[�o���ϐ�

	

	g_fade = FADE_IN;//�t�F�[�h�C������n�߂�B

	//g_ModeNext = modeNext;//�X�V�����Ńt�F�[�h�A�E�g�����������Ƃ��Ɏ��Ɉڍs���郂�[�h��ݒ肷��B


	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\fade_testure_2.png",
		&g_pTextureFade);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�����ʒu�j
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
	pVtx[0].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[1].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[2].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[3].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);

	//�e�N�X�`�����W�̐ݒ�i�����ݒ�j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateFade(void)
{

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//�t�F�[�h�C�����
			g_colorFade_a -= 5;//�|���S���𓧖��ɂ��Ă���


			if (g_colorFade_a <= 0)
			{
				g_colorFade_a = 0;
				g_fade = FADE_NONE;//�������Ă��Ȃ���Ԃɖ߂��B
			}
		}

		else if (g_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorFade_a += 5;//�|���S����s�����ɂ��Ă����B
			if (g_colorFade_a >= 255)
			{
				g_colorFade_a = 255;
				//g_fade = FADE_IN;//�t�F�[�h�C����Ԃ�

				//���[�h�ݒ�i���̉�ʂɈڍs�j

				SetMode(g_ModeNext);
			}

		}
	}

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);



	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[1].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[2].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	pVtx[3].col = D3DCOLOR_RGBA(0,0,0,g_colorFade_a);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u��
		//&g_pVtxBuffPolygon[0],//���_���̐擪�A�h���X
		//sizeof(VERTEX_2D));//���_���\���̂̃T�C�Y
}

//===============================================
//�t�F�[�h�̐ݒ菈��
//===============================================
void SetFade(MODE ModeNext)
{

	g_fade = FADE_OUT;//�Z�b�g�t�F�[�h���g���Ƃ�����A����̓t�F�[�h�A�E�g����^�C�~���O�Ȃ̂ŁA�t�F�[�h�A�E�g��Ԃɂ���B
	g_ModeNext = ModeNext;//�t�F�[�h�A�E�g��ɁA�ڍs���郂�[�h��ݒ肷��B

}

FADE GetFade(void)
{
	return g_fade;
}