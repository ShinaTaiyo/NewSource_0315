//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[SkillName.h]
//Author:ShinaTaiyo
//
//=========================================================

#ifndef _SKILLGAGE_H_
#define _SKILLGAGE_H

#include "main.h"



//�v���g�^�C�v�錾
void InitSkillName(void);
void UninitSkillName(void);
void UpdateSkillName(void);
void DrawSkillName(void);

//�\���̒�`
typedef struct
{
	int nSkillType;//�X�L���̃^�C�v�����߂�ϐ�
	float fSkillPattern;//�g���X�L�������߂�����ϐ�
	D3DXVECTOR3 pos;//�ʒu
}Skill;



//�񋓌^��`
typedef enum
{
	SKILLTYPE_FIRETORNADO = 0,//�t�@�C�A�g���l�[�h
	SKILLTYPE_THUNDERBURST,//�T���_�[�o�[�X�g
	SKILLTYPE_METEOBALL,//���e�I�{�[��
	SKILLTYPE_KILLNEEDLE,//�L���j�[�h��
	SKILLTYPE_CHAINFIRE,//�`�F�C���t�@�C�A
	SKILLTYPE_ATOMICSLASH,//�A�g�~�b�N�X���b�V��
	SKILLNAME_MAX
}SkillType;

Skill* GetSkill(void);
#endif

