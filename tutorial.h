//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[tutorial.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H

#include "main.h"
//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

//�\���̒�`
typedef struct
{
	int nTutorialType;//�X�L���̃^�C�v�����߂�ϐ�
	float fTutorialPattern;//�g���X�L�������߂�����ϐ�
	bool bTutorialUse;//�`���[�g���A����ʂ��g���Ă��邩�ǂ����𔻒肷��t���O
}Tutorial;



//�񋓌^��`
typedef enum
{
	TUTORIALTYPE_RULE= 0,//���[���������ꂽ��ʂ��Ăяo���B
	TUTORIALTYPE_OPERATION,//������@�������ꂽ��ʂ��Ăяo���B
	TUTORIALTYPE_MAX
}TutorialType;

Tutorial* GetTutorial(void);
#endif

