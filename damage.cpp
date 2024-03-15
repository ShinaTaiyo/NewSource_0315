#include "Damage.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "effect.h"
#include "wall.h"
#include "particle.h"

#define MAX_DAMAGE (1024)//�_���[�W�\�L�̍ő吔
#define DAMAGE_DIGIT (3) //��񓖂���̃_���[�W�̍ő包��
#define DAMAGE_SCALE_X (10)
#define DAMAGE_SCALE_Y (5)

#define DAMAGE_RADIUS (10.0f)

#define Damage_SCALE (10.0f)
//�O���[�o���ϐ�
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffDamage = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureDamage = NULL;//�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posDamage;//�ʒu
//D3DXVECTOR3 g_rotDamage;//����
D3DXMATRIX g_mtxWorldDamage;//���[���h�}�g���b�N�X(float4*4)

Damage g_aDamage[MAX_DAMAGE][DAMAGE_DIGIT];


//�^�C�g����ʂ̏���������
void InitDamage(void)
{


	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//�J���[�̏������i���F�j

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data\\number_001.png",
		&g_pTextureDamage);

	g_posDamage = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_DAMAGE * DAMAGE_DIGIT,//���_�̐�
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDamage,
		NULL);

	//�X�R�A���̏�����
	for (int nCntDamage = 0; nCntDamage < MAX_DAMAGE; nCntDamage++)
	{
		for (int nCntDigit = 0; nCntDigit < DAMAGE_DIGIT; nCntDigit++)
		{
			g_aDamage[nCntDamage][nCntDigit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDamage[nCntDamage][nCntDigit].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���

			g_aDamage[nCntDamage][nCntDigit].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU = 0;
			g_aDamage[nCntDamage][nCntDigit].nLife = 0;
			g_aDamage[nCntDamage][nCntDigit].fDamageWrite = 0.0f;
			g_aDamage[nCntDamage][nCntDigit].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}




	////�^�C�g�����BGM�̐ݒ�
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDamage->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntDamage = 0; nCntDamage < MAX_DAMAGE * DAMAGE_DIGIT; nCntDamage++)
	{
		//���_���W�̐ݒ�i�����ʒu�j
		pVtx[0].pos = D3DXVECTOR3(-Damage_SCALE, Damage_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Damage_SCALE, Damage_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-Damage_SCALE, -Damage_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Damage_SCALE, -Damage_SCALE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//�|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDamage->Unlock();
}

//==============================
//�^�C�g����ʂ̏I������
//==============================
void UninitDamage(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureDamage != NULL)
	{
		g_pTextureDamage->Release();
		g_pTextureDamage = NULL;
	}
	//}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffDamage != NULL)
	{
		g_pVtxBuffDamage->Release();
		g_pVtxBuffDamage = NULL;
	}
}
//============================
//�^�C�g����ʂ̍X�V����
//============================
void UpdateDamage(void)
{
	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDamage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDamage = 0; nCntDamage < MAX_DAMAGE; nCntDamage++)
	{
		//���_���W�̐ݒ�

		for (int nCntDigit = 0; nCntDigit < DAMAGE_DIGIT; nCntDigit++)
		{
			if (g_aDamage[nCntDamage][nCntDigit].bUse == true)
			{

				g_aDamage[nCntDamage][nCntDigit].nLife -= 1;//�_���[�W�\�����Ԃ����炵������
				g_aDamage[nCntDamage][nCntDigit].a_col -= 0.01f;//�A���t�@�l��ς������A�ǂ�ǂ�_���[�W�\�L�𓧖��ɂ��Ă�������

				pVtx[0].pos = D3DXVECTOR3(-g_aDamage[nCntDamage][nCntDigit].fRadius - (g_aDamage[nCntDamage][nCntDigit].fRadius * nCntDigit),+g_aDamage[nCntDamage][nCntDigit].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(+g_aDamage[nCntDamage][nCntDigit].fRadius - (g_aDamage[nCntDamage][nCntDigit].fRadius * nCntDigit),+g_aDamage[nCntDamage][nCntDigit].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aDamage[nCntDamage][nCntDigit].fRadius - (g_aDamage[nCntDamage][nCntDigit].fRadius * nCntDigit),-g_aDamage[nCntDamage][nCntDigit].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(+g_aDamage[nCntDamage][nCntDigit].fRadius - (g_aDamage[nCntDamage][nCntDigit].fRadius * nCntDigit),-g_aDamage[nCntDamage][nCntDigit].fRadius, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aDamage[nCntDamage][nCntDigit].a_col);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aDamage[nCntDamage][nCntDigit].a_col);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aDamage[nCntDamage][nCntDigit].a_col);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aDamage[nCntDamage][nCntDigit].a_col);//D3DXCOLOR�́A0.0f�`1.0f�̊Ԃ̐��l�ŐF��ς���B


				//�_���[�W�̓���
				g_aDamage[nCntDamage][nCntDigit].pos += g_aDamage[nCntDamage][nCntDigit].move;

				if (g_aDamage[nCntDamage][nCntDigit].nLife < 1)
				{
					g_aDamage[nCntDamage][nCntDigit].bUse = false;
				}
			}
			pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�B
		}
	}
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDamage->Unlock();
}



//================================
//�^�C�g����ʂ̕`�揈��
//================================
void DrawDamage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
	pDevice = GetDevice();



	for (int nCntDamage = 0; nCntDamage < MAX_DAMAGE; nCntDamage++)
	{
		for (int nCntDigit = 0; nCntDigit < DAMAGE_DIGIT; nCntDigit++)
		{
			if (g_aDamage[nCntDamage][nCntDigit].bUse == true)
			{
				D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

				D3DXMATRIX mtxView;//�r���[�}�g���b�N�X�擾�p

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_mtxWorldDamage);

				//�r���[�}�g���b�N�X���擾
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
				D3DXMatrixInverse(&g_mtxWorldDamage, NULL, &mtxView);

				//�t�s������߂�
				g_mtxWorldDamage._41 = 0.0f;
				g_mtxWorldDamage._42 = 0.0f;
				g_mtxWorldDamage._43 = 0.0f;

				////�����𔽉f
				//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotDamage.y, g_rotDamage.x, g_rotDamage.z);

				//D3DXMatrixMultiply(&g_mtxWorldDamage, &g_mtxWorldDamage, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aDamage[nCntDamage][nCntDigit].pos.x, g_aDamage[nCntDamage][nCntDigit].pos.y, g_aDamage[nCntDamage][nCntDigit].pos.z);
				D3DXMatrixMultiply(&g_mtxWorldDamage, &g_mtxWorldDamage, &mtxTrans);

				//=============================
				//�`��̒���
				//==============================================================
				//���C�g�𖳌��ɂ���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

				//Z�̔�r���@�ύX�B
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

				//Z�o�b�t�@�ɏ������܂Ȃ�
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

				//�A���t�@�e�X�g��L��
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

				//===============================================================

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldDamage);


				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffDamage, 0, sizeof(VERTEX_3D));//���_�o�b�t�@�ւ̃|�C���^�ƒ��_���̍\���̂̃T�C�Y

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureDamage);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDigit * 4 + (DAMAGE_DIGIT * 4) * nCntDamage, 2);//0�́A�`�悷��ŏ��̒��_�C���f�b�N�X�ŁA2�́A�`�悷��v���~�e�B�u

				//============================
				//�`��̒��������Ƃɖ߂�
				//============================

				//���C�g��L���ɖ߂�
				pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

				//Z�̔�r���@�ύX�B
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

				//Z�o�b�t�@�ɏ�������
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

				//�A���t�@�e�X�g�𖳌��ɖ߂�
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

				//=========================================================
			}
		}
	}
}

//=================================
//�_���[�W�̐ݒ菈��
//=================================
void SetDamage(int nDamage, int nLife, D3DXVECTOR3 pos, float fRadius, D3DXCOLOR col)//pos�́u���ˈʒu�v�Amove�́u�ړ��ʁv
{
	VERTEX_3D* pVtx;
	int nGetDamage = nDamage;
	int nCntDamageDigit = 0;//�����_���[�W�\�L���g�p����Ă��Ȃ�������A�_���[�W�\�L�̌������̃J�E���g���J�n����B
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffDamage->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntDamage = 0; nCntDamage < MAX_DAMAGE; nCntDamage++)
	{
		float fRandumRot = float(rand() % 200 + 1) / 100;
		float fRandumSpeed = float(rand() % 100 + 30) / 10;
		float fRandumMove = float(rand() % 21 - 10);

		for (int nCntDigit = 0; nCntDigit < DAMAGE_DIGIT; nCntDigit++)
		{
			if (g_aDamage[nCntDamage][nCntDigit].bUse == false)
			{
				g_aDamage[nCntDamage][nCntDigit].bUse = true;
				g_aDamage[nCntDamage][nCntDigit].nLife = nLife;
				g_aDamage[nCntDamage][nCntDigit].pos = pos;
				g_aDamage[nCntDamage][nCntDigit].fRadius = fRadius;
				g_aDamage[nCntDamage][nCntDigit].a_col = 0.8f;
				g_aDamage[nCntDamage][nCntDigit].col = col;
				g_aDamage[nCntDamage][nCntDigit].move = D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed);

				g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU = nGetDamage % 10;
				nGetDamage = nGetDamage / 10;

				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU),0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU),0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU),1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aDamage[nCntDamage][nCntDigit].nDamagePosTexU),1.0f);

				nCntDamageDigit++;
			}
			if (nCntDamageDigit >= DAMAGE_DIGIT)
			{
				break;
			}
			pVtx += 4;

		}
		if (nCntDamageDigit >= DAMAGE_DIGIT)
		{
			break;
		}


	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDamage->Unlock();
}

Damage* GetDamage(void)//�e�\���̂̏����Q�b�g����
{
	return &g_aDamage[0][0];
}

