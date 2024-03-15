////========================================================
////
////�P�P���V���F���f���ǂݍ���[Model.cpp]
////Author:ShinaTaiyo
////
////=========================================================
//
//#include "model.h"
//#include "main.h"
//#include "input.h"
//#include "sound.h"
//#include "fade.h"
////�O���[�o���ϐ�
//LPD3DXMESH g_pMeshModel = NULL;//���b�V���i���_���j�ւ̃|�C���^
//LPD3DXBUFFER g_pBuffMatModel = NULL;//�}�e���A���ւ̃|�C���^
//DWORD g_dwNumMatModel = 0;//�}�e���A���̐�
//D3DXVECTOR3 g_posModel;//�ʒu
//D3DXVECTOR3 g_rotModel;//����
//D3DXMATRIX g_mtxWorldModel;//���[���h�}�g���b�N�X
//#define Model_SCALE (10.0f)
//
////�^�C�g����ʂ̏���������
//void InitModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^�Ǝ擾
//
//	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	//���f���̓ǂݍ���
//	D3DXLoadMeshFromX("data\\MODEL\\bill_003.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_pBuffMatModel,
//		NULL,
//		&g_dwNumMatModel,
//		&g_pMeshModel);
//}
//
////==============================
////�^�C�g����ʂ̏I������
////==============================
//void UninitModel(void)
//{
//	//���b�V���̔j��
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//
//	//�}�e���A���̔j��
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//}
////============================
////�^�C�g����ʂ̍X�V����
////============================
//void UpdateModel(void)
//{
//
//
//
//}
//
////================================
////�^�C�g����ʂ̕`�揈��
////================================
//void DrawModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//�f�o�C�X�ւ̃|�C���^�Ǝ擾
//
//
//	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
//
//	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
//
//	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
//
//	//���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&g_mtxWorldModel);
//
//	//�����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
//
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
//
//	//�ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);
//
//	//���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);
//
//	//���݂̃}�e���A�����擾
//	pDevice->GetMaterial(&matDef);
//
//	//�}�e���A���ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
//	{
//		//�}�e���A���̐ݒ�
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, NULL);
//
//		//���f���i�p�[�c�j�̕`��
//		g_pMeshModel->DrawSubset(nCntMat);
//	}
//
//	//�ۑ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//}