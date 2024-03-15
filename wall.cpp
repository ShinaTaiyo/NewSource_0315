//========================================================
//
//�X���Q�U���F�n�b�J�\���̊�Ս��[Wall.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include <stdio.h>
#include <string.h>

#include "wall.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

#define WALLSET "data\\TEXTFILE\\WallSet.txt"//�ǃZ�b�g�\���̂��Ă�

//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posWall;//�ʒu
D3DXVECTOR3 g_rotWall;//����
D3DXMATRIX g_mtxWorldWall;//���[���h�}�g���b�N�X(float4*4)


Wall g_aWall[MAX_WALL];//�ǂ̏��

float g_fRotWall;

#define WALL_SCALE (200.0f)

//�^�C�g����ʂ̏���������
void InitWall(void)
{
	g_fRotWall = 0.0f;

	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\win_001.png",
		&g_pTextureWall);

	//g_posWall = D3DXVECTOR3(0.0f, 0.0f, 200.0f);//�ʒu�̏�����
	//g_rotWall = D3DXVECTOR3(0.0f, -D3DX_PI * 0.0f, 0.0f);//�����̏�����

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].fWidth = 0.0f;
		g_aWall[nCntWall].fHeight = 0.0f;
		g_aWall[nCntWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,/** MAX_WALL,*///���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);


	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	char aString[100];

	int nCnt = 0;//�J�E���g

	int nType = 0;//���
	
	float fPosX = 0.0f;//�ʒuX
	float fPosY = 0.0f;//�ʒuY
	float fPosZ = 0.0f;//�ʒuZ

	float fRotX = 0.0f;//����X
	float fRotY = 0.0f;//����Y
	float fRotZ = 0.0f;//����Z

	float fWidth = 0.0f;//��
	float fHeight = 0.0f;//����

	//pFile = fopen(WALLSET, "r");

	//if (pFile != NULL)//�t�@�C�����J���Ă��邩�ǂ���
	//{
	//	while (1)
	//	{

	//		fscanf(pFile,"%s",&aString[0]);
	//		
	//		if (strcmp(&aString[0], "ENDSCRIPT") == 0)
	//		{
	//			break;//�s�̍Ō�ł��̕�����𔻒肳���邱�Ƃɂ��A���[�v���I��点��
	//		}
	//		else if (strcmp(&aString[0], "WALLSET") == 0)
	//		{
	//			while (1)
	//			{
	//				fscanf(pFile, "%s", &aString[0]);
	//				if (strcmp(&aString[0], "TYPE") == 0)
	//				{
	//					fscanf(pFile, "%d", &nType);//�E�H�[���̎�ނ����߂�
	//				}
	//				else if (strcmp(&aString[0], "POS") == 0)
	//				{
	//					fscanf(pFile, "%f%f%f", &fPosX, &fPosY, &fPosZ);//�ʒu����ǂݍ���
	//				}
	//				else if (strcmp(&aString[0], "ROT") == 0)
	//				{
	//					fscanf(pFile, "%f%f%f", &fRotX, &fRotY, &fRotZ);//��������ǂݍ���
	//				}
	//				else if (strcmp(&aString[0], "WIDTH") == 0)
	//				{
	//					fscanf(pFile, "%f", &fWidth);//������ǂݍ���
	//				}
	//				else if (strcmp(&aString[0], "HEIGHT") == 0)
	//				{
	//					fscanf(pFile, "%f", &fHeight);//��������ǂݍ���
	//				}
	//				else if (strcmp(&aString[0], "ENDWALLSET") == 0)
	//				{
	//					SetWall(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(fRotX, fRotY, fRotZ), fWidth, fHeight);
	//					break;
	//				}
	//				nCnt++;
	//			}
	//		}
	//		nCnt++;
	//	}
	//fclose(pFile);
	//}


	SetWall(D3DXVECTOR3(0.0f, 0.0f, 3000.0f),D3DXVECTOR3(0.0f,-D3DX_PI * 0.0f,0.0f),3000.0f,3000.0f);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -3000.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 1.0f, 0.0f), 3000.0f, 3000.0f);
	SetWall(D3DXVECTOR3(-3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 3000.0f, 3000.0f);
	SetWall(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 1.5f, 0.0f), 3000.0f, 3000.0f);
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateWall(void)
{

	if (GetKeyboardPress(DIK_R) == true)
	{
		g_fRotWall += 0.01f;
	}
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���_���W�̐ݒ�i�����ʒu�j
			pVtx[0].pos = D3DXVECTOR3(- g_aWall[nCntWall].fWidth,g_aWall[nCntWall].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth,g_aWall[nCntWall].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(- g_aWall[nCntWall].fWidth, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].fWidth, 0.0f, 0.0f);
		}
			pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();




	g_rotWall = D3DXVECTOR3(0.0f,0.0f + (-D3DX_PI * g_fRotWall), 0.0f);//�����̏�����
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
	        D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	        
	        //���[���h�}�g���b�N�X�̏�����
	        D3DXMatrixIdentity(&g_mtxWorldWall);
	        
	        //�����𔽉f
	        D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
	        
	        D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);
	        
	        //�ʒu�𔽉f
	        D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
	        D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);
	        
	        //���[���h�}�g���b�N�X�̐ݒ�
	        pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);
	        
	        
	        //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	        pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y
	        
	        //���_�t�H�[�}�b�g�̐ݒ�
	        pDevice->SetFVF(FVF_VERTEX_3D);

	
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u
		}
	}
	
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeiht)
{
	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].fWidth = fWidth;
			g_aWall[nCntWall].fHeight = fHeiht;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}

Wall* GetWall(void)
{
	return &g_aWall[0];
}

