////========================================================
////
////�W���R�O���F�G�t�F�N�g������񌩒���[BOSS.cpp]
////Author:ShinaTaiyo
////
////=========================================================
//#ifndef _BOSS_H_
//#define _BOSS_H_
//
//#include "main.h"
//
////�}�N����`
//#define MAX_BOSS (50)//�G�̍ő吔
//#define MAX_CIRCLEBULLET (20)//�~�`�e�U�e�̒e��
//#define MAX_CIRCLEBULLET_2 (10)//�~�`�e�U�e�̒e��
//
//
////�񋓌^��`
////=======================================
////�G�̏��
//typedef enum
//{
//	BOSSSTATE_NORMAL = 0,
//	BOSSSTATE_DAMAGE,
//	BOSSSTATE_MAX
//}BOSSSTATE;
//
////�G�̎��
//typedef enum
//{
//	BOSSTYPE_DELBY = 0,
//	BOSSTYPE_PUNDY,
//	BOSSTYPE_SMILY,
//	BOSSTYPE_SQUDY,
//	BOSSTYPE_REAFY,
//	BOSSTYPE_HONOBY,
//	BOSSTYPE_MIZUBY,
//	BOSSTYPE_BOMUBY,
//	BOSSTYPE_WINBY,
//	BOSSTYPE_BOLBY,
//	BOSSTYPE_BANDY,
//	BOSSTYPE_MAX
//}BOSSTYPE;
//
//
////�G�\���̂̒�`
//typedef struct//========================================================
////
////�W���R�O���F�G�t�F�N�g������񌩒���[enemy.cpp]
////Author:ShinaTaiyo
////
////=========================================================
//#ifndef _ENEMY_H_
//#define _ENEMY_H_
//
//#include "main.h"
//
////�}�N����`
//#define MAX_ENEMY (50)//�G�̍ő吔
//#define MAX_CIRCLEBULLET (20)//�~�`�e�U�e�̒e��
//#define MAX_CIRCLEBULLET_2 (10)//�~�`�e�U�e�̒e��
//
//
////�񋓌^��`
////=======================================
////�G�̏��
//typedef enum
//{
//	ENEMYSTATE_NORMAL = 0,
//	ENEMYSTATE_DAMAGE,
//	ENEMYSTATE_MAX
//}ENEMYSTATE;
//
////�G�̎��
//typedef enum
//{
//	ENEMYTYPE_DELBY = 0,
//	ENEMYTYPE_PUNDY,
//	ENEMYTYPE_SMILY,
//	ENEMYTYPE_SQUDY,
//	ENEMYTYPE_REAFY,
//	ENEMYTYPE_HONOBY,
//	ENEMYTYPE_MIZUBY,
//	ENEMYTYPE_BOMUBY,
//	ENEMYTYPE_WINBY,
//	ENEMYTYPE_BOLBY,
//	ENEMYTYPE_BANDY,
//	ENEMYTYPE_MAX
//}ENEMYTYPE;
//
//
////�G�\���̂̒�`
//typedef struct
//{
//	D3DXVECTOR3 pos;//�ʒu
//	D3DXVECTOR3 move;//�ړ���
//	D3DXVECTOR3 rot;//����
//	int nType;//���
//	ENEMYSTATE State;//���
//	int nCounterState;//��ԊǗ��J�E���^�[
//	int nLife;//�̗�
//	bool bUse;//�g�p���Ă��邩�ǂ���
//	int nEnemyCount;//�G�̍ő吔���J�E���g����ϐ�
//	bool bEnemyMoveX;//X�����̃X�N���[���Z�[�o�[
//	bool bEnemyMoveY;//Y�����̃X�N���[���Z�[�o�[
//	bool bSetEnemyUse;//�G���Z�b�g�����Ƃ���true�ɂȂ�t���O
//	bool bDefeatFlag;//�G���Z�b�g������A�G��|������false�ɂȂ�t���O
//	float fEnemy5BulletCurve;//�G�l�~�[�T�̒e�̃J�[�u�̒l
//	//bool bResultFlag;
//}Enemy;
//
//typedef struct
//{
//	bool bResultFlag;
//}Result;
//
//typedef struct
//{
//	//bool bWaveFlag;//�E�F�[�u���̃J�E���g
//	int DefeatEnemyCount;//�|�����G�l�~�[���̃J�E���g
//}Wave;
//
////�v���g�^�C�v�錾
//void InitEnemy(void);
//void UninitEnemy(void);
//void UpdateEnemy(void);
//void DrawEnemy(void);
//void SetEnemy(D3DXVECTOR3 pos, int ntype,int nLife,D3DXVECTOR3 move);//nType�͓G�̎��
//void HitEnemy(int nCntEnemy, int nDamage);//�unCntEnemy�v�́A�ǂ̓G�ɁH�A�unDamage�v�́A�ǂ̂��炢�_���[�W��^����H
//Enemy* GetEnemy(void);
//
//Result* GetResult(void);
//
//Wave* GetWave(void);//�E�F�[�u�����Ǘ�����\���̂��Q�b�g����B
//#endif
//
//{
//	D3DXVECTOR3 pos;//�ʒu
//	D3DXVECTOR3 move;//�ړ���
//	D3DXVECTOR3 rot;//����
//	int nType;//���
//	BOSSSTATE State;//���
//	int nCounterState;//��ԊǗ��J�E���^�[
//	int nLife;//�̗�
//	bool bUse;//�g�p���Ă��邩�ǂ���
//	int nBOSSCount;//�G�̍ő吔���J�E���g����ϐ�
//	bool bBOSSMoveX;//X�����̃X�N���[���Z�[�o�[
//	bool bBOSSMoveY;//Y�����̃X�N���[���Z�[�o�[
//	bool bSetBOSSUse;//�G���Z�b�g�����Ƃ���true�ɂȂ�t���O
//	bool bDefeatFlag;//�G���Z�b�g������A�G��|������false�ɂȂ�t���O
//	float fBOSS5BulletCurve;//�G�l�~�[�T�̒e�̃J�[�u�̒l
//	//bool bResultFlag;
//}BOSS;
//
//typedef struct
//{
//	bool bResultFlag;
//}Result;
//
//typedef struct
//{
//	//bool bWaveFlag;//�E�F�[�u���̃J�E���g
//	int DefeatBOSSCount;//�|�����G�l�~�[���̃J�E���g
//}Wave;
//
////�v���g�^�C�v�錾
//void InitBOSS(void);
//void UninitBOSS(void);
//void UpdateBOSS(void);
//void DrawBOSS(void);
//void SetBOSS(D3DXVECTOR3 pos, int ntype, int nLife, D3DXVECTOR3 move);//nType�͓G�̎��
//void HitBOSS(int nCntBOSS, int nDamage);//�unCntBOSS�v�́A�ǂ̓G�ɁH�A�unDamage�v�́A�ǂ̂��炢�_���[�W��^����H
//BOSS* GetBOSS(void);
//
//Result* GetResult(void);
//
//Wave* GetWave(void);//�E�F�[�u�����Ǘ�����\���̂��Q�b�g����B
//#endif
//
