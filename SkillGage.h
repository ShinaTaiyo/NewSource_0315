//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[SkillGage.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#ifndef _SKILLSkillGage_H_
#define _SKILLSkillGage_H





//�\���̒�`
typedef struct
{
	int nSkillGageCount;
	float fSkillGage;//�Q�[�W�̒�����ς���ϐ�
	int nType;//�Q�[�W�̎��
	bool bUse;//�g�p���Ă��邩�ǂ���
	bool bBrinkingFlag;//�_�ł�����t���O
	int nSubjectEnemy;//HP��\������G
	int nCountBoss1;//�{�X�P���o�����Ă���̎��Ԃ��v������B
	float fBrinkingPoint;//�_�ł����邽�߁A�F��ς���
	float fBoss1MaxHp;//�{�X�P���o�����Ă���{�X�P��Hp��ۑ�����B
	D3DXVECTOR3 pos;//�X�L���Q�[�W��ݒ肷��ꏊ

}SkillGage;

typedef enum
{
	SKILLGAGETYPE_NORMAL=0,
	SKILLGAGETYPE_ENERGY,
	SKILLGAGETYPE_MAX
}SKILLGAGETYPE;

//�v���g�^�C�v�錾
void InitSkillGage(void);
void UninitSkillGage(void);
void UpdateSkillGage(void);
void DrawSkillGage(void);
void AddSkillGage(float fSkillPoint);//�X�L���Q�[�W�𑝂₷����



SkillGage* GetSkillGage(void);//�Q�[�W�\���̂̏����Q�b�g����B
#endif


