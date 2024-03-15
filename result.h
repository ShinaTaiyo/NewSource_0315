//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[result.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//�}�N����`
#define MAX_RESULT_TEX (2)

//�񋓌^��`
typedef enum
{
	RESULTTYPE_CLEAR=0,//�Q�[���N���A���̃��U���g
	RESULTTYPE_GAMEOVER,//�Q�[���I�[�o�[���̃��U���g
	RESULTTYPE_MAX
}RESULTTYPE;

//�\���̒�`
typedef struct
{
	int nResultType;//�Ăяo�����U���g�̎�ނ����߂�ϐ�
	bool bResultMode;//�������U���g���[�h���ǂ����𔻒肷��
}ResultType;


//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult (void);
void DrawResult(void);

ResultType* GetResultType(void);

#endif
