//========================================================
//
//�P�P���V���FX�t�@�C����ǂݍ���[Enemy.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define NUM_ENEMY (11)//�G�̎��
#define MAX_ENEMY (1024)//�ǂݍ��ޓG�̍ő吔
#define ENEMYSET "data\\TEXTFILE\\Enemy.txt"
#define MAX_ENEMYTEXTURE (100)

typedef struct
{
	LPD3DXMESH pMesh;//���b�V���i���_���j�ւ̃|�C���^�i���f���̎�ސ����j
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 apTextureEnemy[MAX_ENEMYTEXTURE];//�e�N�X�`���ւ̃|�C���^
}EnemyModelInfo;


typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 posOld;//1F�O�̈ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 vtxMinEnemy;//���ꂼ��̍��W�̓G�̈ʒu�̍ŏ��l
	D3DXVECTOR3 vtxMaxEnemy;//���ꂼ��̍��W�̓G�̈ʒu�̍ő�l
	D3DXMATRIX mtxWorld;    //�}�g���b�N�X

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	int nType;//���
	int nIdxShadow;//�e�̃C���f�b�N�X
	bool bUse;//�g�p���Ă��邩�ǂ���
	bool bIsLanding;//�n�ʂɂ��邩�ǂ���

	int nHp;//�̗�
	int nAttack;//�U����
	int nDefeatScore;//�|�����Ƃ��ɂ��炦��X�R�A
	float fSpeed;//����

	float fVXaim;//X�����̃x�N�g��
	float fVYaim;//Y�����̃x�N�g��
	float fVZaim;//Z�����̃x�N�g��
	float fVaim;//���������x�N�g��
	float fVaimY1;//��������Y�����̃x�N�g��
	float fVaimY2;
	float fVaim3;

	float fPenduram;//�U��q�̂悤�ɒe�𔭎˂�����ϐ�
	bool bPenduramFlag;

	D3DXVECTOR3 Size;//�G�̑傫��
}Enemy;

typedef enum
{
	ENEMY00_NOOBSLIME = 0,//�ア�X���C��
	ENEMY01_ANGRYSLIME,//�{��X���C��
	ENEMY02_SWORDSLIME,//���X���C��
	ENEMY03_HAMMERSLIME,//�n���}�[�X���C��
	ENEMY04_ORANGESLIME,//�I�����W�X���C��
	ENEMY05_GREENSLIME,//�O���[���X���C��
	ENEMY06_WHITESLIME,//�z���C�g�X���C��
	ENEMY07_TURQUOISSLIME,//�^�[�R�C�Y�X���C��
	ENEMY08_ENGELSLIME,//�G���W�F���X���C��
	ENEMY09_DARKSLIME,//�_�[�N�X���C��
	ENEMY10_RAINBOWSLIME,//���C���{�[�X���C��
	ENEMY_MAX
}ENEMYTYPE;

//=========================================
static const char* ENEMY_FILENAME[NUM_ENEMY] =
{
	"data\\Enemy\\00_noobSlime.x",
    "data\\Enemy\\01_angrySlime.x",
    "data\\Enemy\\02_swordSlime.x",
    "data\\Enemy\\03_hammerSlime.x",
    "data\\Enemy\\04_orangeSlime.x",
    "data\\Enemy\\05_greenSlime.x",
    "data\\Enemy\\06_WhiteSlime.x",
    "data\\Enemy\\07_turquoiseSlime.x",
    "data\\Enemy\\08_engelSlime.x",
    "data\\Enemy\\09_darkSlime.x",
    "data\\Enemy\\10_RainbowSlime.x",
};


//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
Enemy* GetEnemy(void);//�G�\���̂̏����擾����

void SetDamageEnemy(int nDamage,int nNumEnemy);

#endif


