//========================================================
//
//�P�P���V���F���f���ǂݍ���[AttackModel.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "AttackModel.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include "enemy.h"
#include "effect.h"
#include "particle.h"
#include "damage.h"
#include "emitter.h"
#include "bullet.h"
//�O���[�o���ϐ�
int g_nNumAttackModel = 0;//�ǂݍ��ރ��f���̍ő吔�����߂�
#define AttackModel_SCALE (10.0f)
//#define SAVEAttackModel "data\\TEXTFILE\\SaveAttackModel.txt"

#define MAX_TEXTURE (32)


typedef struct
{
	LPD3DXMESH pMeshAttackModel;//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
	LPD3DXBUFFER pBuffMatAttackModel;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMatAttackModel;//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 apTextureAttackModel[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
}AttackModelMat;

D3DXVECTOR3 g_posAttackModel;//�ʒu
D3DXVECTOR3 g_rotAttackModel;//����
D3DXMATRIX g_mtxWorldAttackModel;//���[���h�}�g���b�N�X

AttackModel g_aAttackModel[MAX_ATTACKMODEL];//���f�����̍\����

AttackModelMat g_aAttackModelMat[NUM_ATTACKMODEL];//���f���̃}�e���A���Ⓒ�_�̍\����


int g_nDelayAttack = 0;//�q�b�g�X�g�b�v�p�ϐ�

//int g_nldxShadow = -1;//�Ώۂ̉e�̃C���f�b�N�X�i�ԍ��j
//bool g_bIsLanding;//�n�ʂɂ��邩�ǂ���

//�^�C�g����ʂ̏���������
void InitAttackModel(void)
{

	//for (int nCntAttackModel = 0; nCntAttackModel < NUM_ATTACKMODEL; nCntAttackModel++)
	//{
	//	g_dwNumMatAttackModel[nCntAttackModel] = 0;//�}�e���A���̐�
	//}
	//g_nldxShadow = 0;//�Ώۂ̉e�̃C���f�b�N�X

	g_nNumAttackModel = 2;

	g_nDelayAttack = 0;//�q�b�g�X�g�b�v�p�ϐ�

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾

	g_posAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nNumAttackModel = 0;

	//g_bIsLanding = false;//�n�ʂɂ��邩�ǂ���



	////���f���̓ǂݍ���
	//D3DXLoadMeshFromX("data\\AttackModel\\bill.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatAttackModel,
	//	NULL,
	//	&g_dwNumMatAttackModel,
	//	&g_pMeshAttackModel[AttackModelTYPE_BILL]);

	//D3DXLoadMeshFromX("data\\AttackModel\\BigBriddge.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_pBuffMatAttackModel,
	//	NULL,
	//	&g_dwNumMatAttackModel,
	//	&g_pMeshAttackModel[AttackModelTYPE_BRIDDGE]);


	for (int nCntMatAttackModel = 0; nCntMatAttackModel < NUM_ATTACKMODEL; nCntMatAttackModel++)
	{
		g_aAttackModelMat[nCntMatAttackModel].dwNumMatAttackModel = {};
		g_aAttackModelMat[nCntMatAttackModel].pBuffMatAttackModel = {};
		g_aAttackModelMat[nCntMatAttackModel].pMeshAttackModel = {};
		for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
		{
			g_aAttackModelMat[nCntMatAttackModel].apTextureAttackModel[nCntTexture] = {};//��̃��f���Ɋ֘A����e�N�X�`���̏�����
		}
	}


	for (int nCnt = 0; nCnt < MAX_ATTACKMODEL; nCnt++)
	{
		g_aAttackModel[nCnt].bUse = false;//�g�p���Ă��邩�ǂ���
		g_aAttackModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu
		g_aAttackModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
		g_aAttackModel[nCnt].nIdxShadow = -1;
		g_aAttackModel[nCnt].nType = -1;
		g_aAttackModel[nCnt].vtxMinAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ŏ��l
		g_aAttackModel[nCnt].vtxMaxAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���ꂼ��̍��W�̃��f���̈ʒu�̍ő�l
		g_aAttackModel[nCnt].nNumVtx = 0;//���_��
		g_aAttackModel[nCnt].sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		g_aAttackModel[nCnt].pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
		g_aAttackModel[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ړ���
		g_aAttackModel[nCnt].nLife = 0;//�̗�
		g_aAttackModel[nCnt].bOneFlag = false;//��񂾂����������鏈��
	}


	//���f���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\FireTornado.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aAttackModelMat[0].pBuffMatAttackModel,
		NULL,
		&g_aAttackModelMat[0].dwNumMatAttackModel,
		&g_aAttackModelMat[0].pMeshAttackModel);

	//���f���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Attack\\meteo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aAttackModelMat[1].pBuffMatAttackModel,
		NULL,
		&g_aAttackModelMat[1].dwNumMatAttackModel,
		&g_aAttackModelMat[1].pMeshAttackModel);


	//���f���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\Attack\\KillNeedle.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aAttackModelMat[2].pBuffMatAttackModel,
		NULL,
		&g_aAttackModelMat[2].dwNumMatAttackModel,
		&g_aAttackModelMat[2].pMeshAttackModel);
	


	

	//for (int nCntAttackModel = 0; nCntAttackModel < MAX_ATTACKMODEL; nCntAttackModel++)
	//{//�S�Ẵ��f���Ɋ��蓖�Ă�
	//	for (int nCntMat = 0; nCntMat < NUM_ATTACKMODEL; nCntMat++)
	//	{//��ނ����蓖�Ă�for��
	//		if (g_aAttackModel[nCntAttackModel].nType == nCntMat)
	//		{//���f���̎�ނ���v

	//			//���_���̎擾
	//			g_aAttackModel[nCntAttackModel].nNumVtx = g_aAttackModelMat[nCntMat].pMeshAttackModel->GetNumVertices();

	//			//���_�t�H�[�}�b�g�̃T�C�Y���擾
	//			g_aAttackModel[nCntAttackModel].sizeFVF = D3DXGetFVFVertexSize(g_aAttackModelMat[nCntMat].pMeshAttackModel->GetFVF());

	//			//���_�o�b�t�@�̃��b�N
	//			g_aAttackModelMat[nCntMat].pMeshAttackModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aAttackModel[nCntAttackModel].pVtxBuff);


	//			for (int nCntVtx = 0; nCntVtx < g_aAttackModel[nCntAttackModel].nNumVtx; nCntVtx++)
	//			{
	//				//���_���W�̑��
	//				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aAttackModel[nCntAttackModel].pVtxBuff;

	//				//====================================================
	//				//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
	//				//====================================================
	//				if (vtx.x > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.x)
	//				{
	//					g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.x = vtx.x;
	//				}
	//				else if (vtx.x < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.x)
	//				{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
	//					g_aAttackModel[nCntAttackModel].vtxMinAttackModel.x = vtx.x;
	//				}
	//				else if (vtx.y > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.y)
	//				{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
	//					g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.y = vtx.y;
	//				}
	//				else if (vtx.y < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.y)
	//				{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
	//					g_aAttackModel[nCntAttackModel].vtxMinAttackModel.y = vtx.y;
	//				}
	//				else if (vtx.z > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.z)
	//				{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
	//					g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.z = vtx.z;
	//				}
	//				else if (vtx.z < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.z)
	//				{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
	//					g_aAttackModel[nCntAttackModel].vtxMinAttackModel.z = vtx.z;
	//				}
	//				//========================================================================

	//				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	//				g_aAttackModel[nCntAttackModel].pVtxBuff += g_aAttackModel[nCntAttackModel].sizeFVF;

	//			}

	//			//���_�o�b�t�@�̃A�����b�N
	//			g_aAttackModelMat[nCntMat].pMeshAttackModel->UnlockVertexBuffer();

	//			//��ޓ��肵�����A�����^�C�v��for���񂷕K�v�Ȃ��̂ŁAbreak
	//			break;

	//		}
	//	}
	//}
	//���_���̎擾

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
	for (int nCntATTACKMODELSET = 0; nCntATTACKMODELSET < NUM_ATTACKMODEL; nCntATTACKMODELSET++)
	{
		//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
		pMat = (D3DXMATERIAL*)g_aAttackModelMat[nCntATTACKMODELSET].pBuffMatAttackModel->GetBufferPointer();
		int nNumTexture = 0;
		for (int nCntMat = 0; nCntMat < (int)g_aAttackModelMat[nCntATTACKMODELSET].dwNumMatAttackModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���
					//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aAttackModelMat[nCntATTACKMODELSET].apTextureAttackModel[nNumTexture]);
				nNumTexture++;
			}
		}
	}

}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitAttackModel(void)
{
	for (int nCnt = 0; nCnt < NUM_ATTACKMODEL; nCnt++)
	{
		//���b�V���̔j��
		if (g_aAttackModelMat[nCnt].pMeshAttackModel != NULL)
		{
			g_aAttackModelMat[nCnt].pMeshAttackModel->Release();
			g_aAttackModelMat[nCnt].pMeshAttackModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_aAttackModelMat[nCnt].pBuffMatAttackModel != NULL)
		{
			g_aAttackModelMat[nCnt].pBuffMatAttackModel->Release();
			g_aAttackModelMat[nCnt].pBuffMatAttackModel = NULL;
		}
	}
}
//============================
//���f���̍X�V����
//============================
void UpdateAttackModel(void)
{

	g_nDelayAttack++;

	float fRandumRot = float(rand() % 200 + 1) / 100;
	float fRandumSpeed = float(rand() % 100 + 30) / 10;
	float fRandumMove = float(rand() % 21);

	float fRandumRot2 = float(rand() % 200 + 1) / 100;
	float fRandumSpeed2 = float(rand() % 100 + 30) / 10;
	float fRandumMove2 = float(rand() % 21);


	float fRandumColor1 = float(rand() % 100) / 100;
	float fRandumColor2 = float(rand() % 100) / 100;
	float fRandumColor3 = float(rand() % 100) / 100;


	float fLength = 0.0f;
	Player* pPlayer = GetPlayer();
	for (int nCntAttack = 0; nCntAttack < MAX_ATTACKMODEL; nCntAttack++)
	{
		if (g_aAttackModel[nCntAttack].bUse == true)
		{
	        Enemy* pEnemy = GetEnemy();

			g_aAttackModel[nCntAttack].nLife -= 1;//�̗͂����炷


			switch (g_aAttackModel[nCntAttack].nType)
			{
			case ATTACKMODELTYPE_FIRETORNADO://�v���C���[�̋Z�F�t�@�C�A�g���l�[�h
			

				g_aAttackModel[nCntAttack].rot.y += 0.1f;

			

				SetParticle(PARTICLETYPE_GRAVITY, 300, 10.0f, 0.01f, g_aAttackModel[nCntAttack].pos,
					D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
					D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, PARTICLETEX_NORMAL);

			
				SetParticle(PARTICLETYPE_GRAVITY, 300, 10.0f, 0.01f, g_aAttackModel[nCntAttack].pos,
					D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot2) * fRandumSpeed2, fRandumMove2, cosf(-D3DX_PI * fRandumRot2) * fRandumSpeed2),
					D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f), 0.0f, PARTICLETEX_NORMAL);

				if (g_aAttackModel[nCntAttack].bOneFlag == true)
				{//��x�����G�~�b�^�[�����͂ɏ�������
					for (int nCntEmitter = 0; nCntEmitter < 6; nCntEmitter++)
					{
						float fEmitterPos = 0;
						fEmitterPos = (2.0f / 6) * nCntEmitter;

						SetEmitterEffect(EMITTERTYPE_TORNADO, 1000, 10, 20.0f, 0.1f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(0.0f, 0.001f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), fEmitterPos,nCntAttack);

					}
					g_aAttackModel[nCntAttack].bOneFlag = false;//���̏������������������Ȃ�
				}

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x + pEnemy->Size.x / 2 >= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMinAttackModel.x &&
							pEnemy->pos.x - pEnemy->Size.x / 2 <= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMaxAttackModel.x &&
							pEnemy->pos.y + pEnemy->Size.y / 2 >= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMinAttackModel.y &&
							pEnemy->pos.y - pEnemy->Size.y / 2 <= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMaxAttackModel.y &&
							pEnemy->pos.z + pEnemy->Size.z / 2 >= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMinAttackModel.z &&
							pEnemy->pos.z - pEnemy->Size.z / 2 <= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMaxAttackModel.z)
						{
							if (g_nDelayAttack % 4 == 0)
							{
								//pEnemy->nHp -= 15;//�P�O�_���[�W��^����
								SetDamageEnemy(15, nCntEnemy);
								
								SetDamage(/*Damage*/ 15,
									/*Life*/ 100,
									/*Pos*/ pEnemy->pos,
									/*���a*/ 20.0f,
									D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
							}
						}
					}

				}
				break;
			case ATTACKMODELTYPE_METEOBALL://�v���C���[�̋Z�F���e�I�{�[��


				g_aAttackModel[nCntAttack].rot.y += 0.1f;
				SetEffect(EFFECTTYPE_NORMAL, 200, 300.0f, 2.0f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 0.0f);


				if (g_nDelayAttack % 15 == 0)
				{
						float fRandumRot3 = float(rand() % 100 - 50) / 100;
						
						SetEmitterEffect(-1, 1000, 1000, 50.0f, 1.0f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(sinf(pPlayer->rot.y + fRandumRot3) * 10.0f,fRandumMove, cosf(pPlayer->rot.y + fRandumRot3) * 10.0f), D3DXCOLOR(fRandumColor1, fRandumColor2, fRandumColor3, 1.0f),0.0f, nCntAttack);
				}

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x + pEnemy->Size.x / 2 >= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMinAttackModel.x &&
							pEnemy->pos.x - pEnemy->Size.x / 2 <= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMaxAttackModel.x &&
							pEnemy->pos.y + pEnemy->Size.y >= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMinAttackModel.y &&
							pEnemy->pos.y <= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMaxAttackModel.y &&
							pEnemy->pos.z + pEnemy->Size.z / 2 >= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMinAttackModel.z &&
							pEnemy->pos.z - pEnemy->Size.z / 2 <= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMaxAttackModel.z)
						{
							if (g_nDelayAttack % 20 == 0)
							{
								//pEnemy->nHp -= 50;//�P�O�_���[�W��^����
								SetDamageEnemy(50, nCntEnemy);
								SetDamage(/*Damage*/ 50,
									/*Life*/ 100,
									/*Pos*/ pEnemy->pos,
									/*���a*/ 50.0f,
									D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
							}
						}
					}

				}
				break;
			case ATTACKMODELTYPE_KILLNEEDLE://�v���C���[�̋Z�L���j�[�h��

				Bullet* pBullet = GetBullet();

				//g_aAttackModel[nCntAttack].rot.y += 0.1f;
				//SetEffect(EFFECTTYPE_NORMAL, 200, 300.0f, 2.0f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 0.0f);


		/*		if (g_nDelayAttack % 15 == 0)
				{
					float fRandumRot3 = float(rand() % 100 - 50) / 100;

					SetEmitterEffect(-1, 1000, 1000, 50.0f, 1.0f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(sinf(pPlayer->rot.y + fRandumRot3) * 10.0f, fRandumMove, cosf(pPlayer->rot.y + fRandumRot3) * 10.0f), D3DXCOLOR(fRandumColor1, fRandumColor2, fRandumColor3, 1.0f), 0.0f, nCntAttack);
				}*/

				
				
				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					SetParticle(PARTICLETYPE_NORMAL, 300, 5.0f, 0.5f, g_aAttackModel[nCntAttack].pos, D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
						D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), 0.0f, PARTICLETEX_NORMAL);
				}

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x + pEnemy->Size.x / 2 >= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMinAttackModel.x &&
							pEnemy->pos.x - pEnemy->Size.x / 2 <= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMaxAttackModel.x &&
							pEnemy->pos.y + pEnemy->Size.y>= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMinAttackModel.y &&
							pEnemy->pos.y<= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMaxAttackModel.y &&
							pEnemy->pos.z + pEnemy->Size.z / 2 >= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMinAttackModel.z &&
							pEnemy->pos.z - pEnemy->Size.z / 2 <= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMaxAttackModel.z)
						{
							if (g_nDelayAttack % 10 == 0)
							{
								//pEnemy->nHp -= 25;//�P�O�_���[�W��^����
								SetDamageEnemy(25, nCntEnemy);
								SetDamage(/*Damage*/25,
									/*Life*/ 100,
									/*Pos*/ pEnemy->pos,
									/*���a*/ 15.0f,
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
							}
						}
					}

				}
				float fRandumRot = float(rand() % 200 + 1) / 100;
				float fRandumSpeed = float(rand() % 50) / 10;
				float fRandumMove = float(rand() % 21 - 10);
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
				{
					if (pBullet->bUse == true)
					{
						int nData = 100;
						if (pBullet->pos.x + pBullet->fRWidth / 2 >= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMinAttackModel.x &&
							pBullet->pos.x - pBullet->fRWidth / 2 <= g_aAttackModel[nCntAttack].pos.x + g_aAttackModel[nCntAttack].vtxMaxAttackModel.x &&
							pBullet->pos.y + pBullet->fRHeight / 2 >= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMinAttackModel.y &&
							pBullet->pos.y - pBullet->fRHeight / 2 <= g_aAttackModel[nCntAttack].pos.y + g_aAttackModel[nCntAttack].vtxMaxAttackModel.y &&
							pBullet->pos.z + pBullet->fRWidth / 2 >= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMinAttackModel.z &&
							pBullet->pos.z - pBullet->fRWidth / 2 <= g_aAttackModel[nCntAttack].pos.z + g_aAttackModel[nCntAttack].vtxMaxAttackModel.z)
						{
							if (pBullet->nType != BULLETTYPE_NORMAL && pBullet->nType != BULLETTYPE_FIRE)
							{
								pBullet->bUse = false;
								for (int nCnt = 0; nCnt < 5; nCnt++)
								{
									SetParticle(PARTICLETYPE_NORMAL, 300, 10.0f, 0.1f, pBullet->pos, D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
										D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),0.0f, PARTICLETEX_NORMAL);
								}
								if (pBullet->bUse == false)
								{
									KillShadow(pBullet->nIdxShadow);
								}
							}
						}
					}
				}
				break;

			}

			/*	fLength = sqrtf((g_aAttackModel[nCnt].pos.x - pPlayer->pos.x) * (g_aAttackModel[nCnt].pos.x - pPlayer->pos.x) +
					(g_aAttackModel[nCnt].pos.z - pPlayer->pos.z) * (g_aAttackModel[nCnt].pos.z - pPlayer->pos.z) +
						(g_aAttackModel[nCnt].pos.y - pPlayer->pos.y) * (g_aAttackModel[nCnt].pos.y - pPlayer->pos.y)) / 3;

				if (fLength <= 20.0f)
				{
					pPlayer->pos = pPlayer->posOld;
				}*/



			g_aAttackModel[nCntAttack].pos += g_aAttackModel[nCntAttack].move;

			//�e�̈ʒu��ݒ�
			SetPositionShadow(g_aAttackModel[nCntAttack].nIdxShadow, g_aAttackModel[nCntAttack].pos, -1,-1,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

			if (g_aAttackModel[nCntAttack].nLife <= 0)
			{
				g_aAttackModel[nCntAttack].bUse = false;
			}

			if (g_aAttackModel[nCntAttack].bUse == false)
			{
				KillShadow(g_aAttackModel[nCntAttack].nIdxShadow);
			}
		}
	}
}

//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawAttackModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾

			D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

			D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

			D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
	
	for (int nCntAttackModel = 0; nCntAttackModel < MAX_ATTACKMODEL; nCntAttackModel++)
	{
		if (g_aAttackModel[nCntAttackModel].bUse == true)
		{

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldAttackModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aAttackModel[nCntAttackModel].rot.y, g_aAttackModel[nCntAttackModel].rot.x, g_aAttackModel[nCntAttackModel].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldAttackModel, &g_mtxWorldAttackModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aAttackModel[nCntAttackModel].pos.x, g_aAttackModel[nCntAttackModel].pos.y, g_aAttackModel[nCntAttackModel].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldAttackModel, &g_mtxWorldAttackModel, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldAttackModel);

		

			for (int nCntATTACKMODELSET = 0; nCntATTACKMODELSET < NUM_ATTACKMODEL; nCntATTACKMODELSET++)
			{//�ǂݍ��ރ��f���̎�ސ���for�����񂵁A�����^�C�v�̃}�e���A���̃|�C���^��A�A
			//�p�[�c�̕`��A�}�e���A���̐ݒ������B
				if (g_aAttackModel[nCntAttackModel].nType == nCntATTACKMODELSET)
				{
					//�}�e���A���ւ̃|�C���^���擾�i�Z�b�g�������f���Ɠ����^�C�v�j
					pMat = (D3DXMATERIAL*)g_aAttackModelMat[nCntATTACKMODELSET].pBuffMatAttackModel->GetBufferPointer();

					int nNumTexture = 0;
					//�Z�b�g���ꂽ���f���ƃ^�C�v���������̂̃��f���̃}�e���A���̐����ǂݍ��ށB
					for (int nCntMat = 0; nCntMat < (int)g_aAttackModelMat[nCntATTACKMODELSET].dwNumMatAttackModel; nCntMat++)
					{
						//�}�e���A���̐ݒ�
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							//�e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, g_aAttackModelMat[nCntATTACKMODELSET].apTextureAttackModel[nNumTexture]);
							nNumTexture++;
						}
						else
						{
							//�e�N�X�`���̐ݒ�
							pDevice->SetTexture(0, g_aAttackModelMat[nCntATTACKMODELSET].apTextureAttackModel[nNumTexture]);
							nNumTexture++;
						}
						//���f���i�p�[�c�j�̕`��
						g_aAttackModelMat[nCntATTACKMODELSET].pMeshAttackModel->DrawSubset(nCntMat);
					}
					break;
				}
			}

			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
}

void SetAttackModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType, int nLife)
{
	for (int nCntAttackModel = 0; nCntAttackModel < MAX_ATTACKMODEL; nCntAttackModel++)
	{
		if (g_aAttackModel[nCntAttackModel].bUse == false)
		{
			g_aAttackModel[nCntAttackModel].bUse = true;//�g�p���Ă��邩�ǂ���
			g_aAttackModel[nCntAttackModel].pos = pos;//�ʒu
			g_aAttackModel[nCntAttackModel].rot = rot;//����
			g_aAttackModel[nCntAttackModel].nType = nType;//���
			g_aAttackModel[nCntAttackModel].nLife = nLife;//�̗�
			g_aAttackModel[nCntAttackModel].nIdxShadow = SetShadow();//�e�̃C���f�b�N�X��ݒ�
			g_aAttackModel[nCntAttackModel].move = move;
			g_aAttackModel[nCntAttackModel].bOneFlag = true;//��񂾂����������鏈��
			g_aAttackModel[nCntAttackModel].vtxMaxAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aAttackModel[nCntAttackModel].vtxMinAttackModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//=========================
			//�T�C�Y���擾
			//=========================
			for (int nCntMat = 0; nCntMat < NUM_ATTACKMODEL; nCntMat++)
			{//��ނ����蓖�Ă�for��
				if (g_aAttackModel[nCntAttackModel].nType == nCntMat)
				{//���f���̎�ނ���v

					//���_���̎擾
					g_aAttackModel[nCntAttackModel].nNumVtx = g_aAttackModelMat[nCntMat].pMeshAttackModel->GetNumVertices();

					//���_�t�H�[�}�b�g�̃T�C�Y���擾
					g_aAttackModel[nCntAttackModel].sizeFVF = D3DXGetFVFVertexSize(g_aAttackModelMat[nCntMat].pMeshAttackModel->GetFVF());

					//���_�o�b�t�@�̃��b�N
					g_aAttackModelMat[nCntMat].pMeshAttackModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aAttackModel[nCntAttackModel].pVtxBuff);


					for (int nCntVtx = 0; nCntVtx < g_aAttackModel[nCntAttackModel].nNumVtx; nCntVtx++)
					{
						//���_���W�̑��
						D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aAttackModel[nCntAttackModel].pVtxBuff;

						//====================================================
						//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
						//====================================================
						if (vtx.x > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.x)
						{
							g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.x = vtx.x;
						}
						else if (vtx.x < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.x)
						{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
							g_aAttackModel[nCntAttackModel].vtxMinAttackModel.x = vtx.x;
						}
						else if (vtx.y > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.y)
						{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
							g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.y = vtx.y;
						}
						else if (vtx.y < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.y)
						{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
							g_aAttackModel[nCntAttackModel].vtxMinAttackModel.y = vtx.y;
						}
						else if (vtx.z > g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.z)
						{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
							g_aAttackModel[nCntAttackModel].vtxMaxAttackModel.z = vtx.z;
						}
						else if (vtx.z < g_aAttackModel[nCntAttackModel].vtxMinAttackModel.z)
						{//����ǂݍ��񂾒��_���A��ԏ��������_��菬�����ꍇ
							g_aAttackModel[nCntAttackModel].vtxMinAttackModel.z = vtx.z;
						}
						//========================================================================

						//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
						g_aAttackModel[nCntAttackModel].pVtxBuff += g_aAttackModel[nCntAttackModel].sizeFVF;

					}

					//���_�o�b�t�@�̃A�����b�N
					g_aAttackModelMat[nCntMat].pMeshAttackModel->UnlockVertexBuffer();

					//��ޓ��肵�����A�����^�C�v��for���񂷕K�v�Ȃ��̂ŁAbreak
					break;

				}
			}

			//==================================================================================================

			break;
		}
	}
}

int GetNumAttackModel(void)
{
	return g_nNumAttackModel;//�ǂݍ��ރ��f���̍ő吔���擾����
}

AttackModel* GetAttackModel(void)//�\���̂̏����擾����
{
	return &g_aAttackModel[0];
}
