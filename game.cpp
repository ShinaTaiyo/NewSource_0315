//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[game.cpp]
//Author:ShinaTaiyo
//
//=========================================================
#include "main.h"
#include "input.h"
#include "bg.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "tutorial.h"
#include "sound.h"
#include "fade.h"
#include <time.h>
#include "ranking.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "field.h"
#include "wall.h"
#include "model.h"
#include "player.h"
#include "shadow.h"
#include <stdio.h>
#include "billboard.h"
#include "bullet.h"
#include "effect.h"
#include "emitter.h"
#include "meshfield.h"
#include "particle.h"
#include "meshcylinder.h"
#include "Block.h"
#include "edit.h"
#include "motion.h"
#include "enemy.h"
#include "editEnemy.h"
#include "AttackModel.h"
#include "timer.h"
#include "score.h"
#include "damage.h"
#include "SkillGage.h"
#include "SkillName.h"
#include "AttackBillBoard.h"
#include "health.h"
#include "combo.h"
#include "Summon.h"
#include "pause.h"

//==============================
//�O���[�o���ϐ�
//==============================
GAMESTATE g_GameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[
int g_nCountTime;//�Q�[���J�n������o�������Ԃ��Ǘ�����ϐ�
bool g_bPause = false;//�|�[�Y�����ǂ���
int g_nChoosePauseCommand;//�|�[�Y���̎��ɑI�����郁�j���[��I������ϐ�
int g_nCountPauseMenu;//�|�[�Y��ʂ��J���Ă��鎞�Ԃ��J�E���g����ϐ�
bool g_bEditEnemyMode = false;//�G�G�f�B�^�����ǂ���

//============================================================================================================

//===================================
//�Q�[����ʂ̏���������
//===================================
void InitGame(void)
{
	g_bEditEnemyMode = false;        //�G�G�f�B�^�����ǂ���
	g_nChoosePauseCommand = 0;       //�ǂ̃|�[�Y�R�}���h��I��ł��邩
	g_nCountPauseMenu = 0;           //�|�[�Y��ʂ��J���Ă��鎞��
	g_nCountTime = 0;                //�Q�[�����n�܂��Ă���̎���
	g_bPause = false;                //�|�[�Y�����ǂ���


	//�G�����p
	InitCamera();         //�J����
	InitMotion();         //���[�V����
	InitLight();          //���C�g
	InitField();          //�t�B�[���h
	InitWall();           //��

	//======================
	// �r���{�[�h
	//======================
	InitDamage();         //�_���[�W�\�L
	InitBullet();         //�e
	InitAttackBillBoard();//�U���r���{�[�h

	//============================
	// ���f��
	//============================
	InitSummon();         //����
	InitModel();          //���f��
	InitEnemy();          //�G
	InitPlayer();         //�v���C���[
	InitAttackModel();    //�U�����f��
	InitEnemyEditor();    //�G�G�f�B�^

	//==================================================
	// �G�t�F�N�g�֌W
	//==================================================
	InitEmitter();        //�G�~�b�^�[
	InitShadow();         //�e
	InitParticle();       //�p�[�e�B�N��
	InitEffect();         //�G�t�F�N�g

	//===================================================
	// UI
	//===================================================
	InitTimer();          //�^�C�}�[
	InitScore();          //�X�R�A
	InitSkillGage();      //�X�L���Q�[�W
	InitSkillName();      //�X�L�����O
	InitHealth();         //�̗�
	InitCombo();          //�R���{
	InitPause();          //�|�[�Y


	//=============================================================================================
	g_GameState = GAMESTATE_NORMAL;//�Q�[���̏��

	g_nCounterGameState = 0;

	PlaySound(SOUND_LABEL_BGM004);
}

//==================================
//�Q�[����ʂ̏I������
//==================================
void UninitGame(void)
{
	//�G�����p
	UninitCamera();         //�J����
	UninitLight();          //���C�g
	UninitField();          //�t�B�[���h
	UninitWall();           //��

	//======================
	// �r���{�[�h
	//======================
	UninitDamage();         //�_���[�W�\�L
	UninitBullet();         //�e
	UninitAttackBillBoard();//�U���r���{�[�h

	//============================
	// ���f��
	//============================
	UninitSummon();         //����
	UninitModel();          //���f��
	UninitEnemy();          //�G
	UninitPlayer();         //�v���C���[
	UninitAttackModel();    //�U�����f��
	UninitEnemyEditor();    //�G�G�f�B�^

	//==================================================
	// �G�t�F�N�g�֌W
	//==================================================
	UninitEmitter();        //�G�~�b�^�[
	UninitShadow();         //�e
	UninitParticle();       //�p�[�e�B�N��
	UninitEffect();         //�G�t�F�N�g

	//===================================================
	// UI
	//===================================================
	UninitTimer();          //�^�C�}�[
	UninitScore();          //�X�R�A
	UninitSkillGage();      //�X�L���Q�[�W
	UninitSkillName();      //�X�L�����O
	UninitHealth();         //�̗�
	UninitCombo();          //�R���{
	UninitPause();          //�|�[�Y

}

//=================================
//�Q�[����ʂ̍X�V����
//=================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true||GetJoyPadTrigger(JOYKEY_BACK)==true)
	{//�|�[�Y�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (GetKeyboardTrigger(DIK_F5) == true )
	{//�G�G�f�B�^�{�^���������ꂽ
		g_bEditEnemyMode = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		if (g_bEditEnemyMode == false)
		{
			g_nCountPauseMenu = 0;

			g_nCountTime++;//�Q�[���J�n������̎��Ԃ��v������B
			UpdateCamera();         //�J����*
			UpdateLight();          //���C�g*
			UpdateField();          //�t�B�[���h
			UpdateWall();           //��

			//======================
			// �r���{�[�h
			//======================
			UpdateDamage();         //�_���[�W�\�L
			UpdateBullet();         //�e
			UpdateAttackBillBoard();//�U���r���{�[�h

			//============================
			// ���f��
			//============================
			UpdateSummon();         //����
			UpdateModel();          //���f��
			UpdateEnemy();          //�G
			UpdatePlayer();         //�v���C���[
			UpdateAttackModel();    //�U�����f��
			//==================================================
			// �G�t�F�N�g�֌W
			//==================================================
			UpdateEmitter();        //�G�~�b�^�[
			UpdateShadow();         //�e
			UpdateParticle();       //�p�[�e�B�N��
			UpdateEffect();         //�G�t�F�N�g

			//===================================================
			// UI
			//===================================================
			UpdateTimer();          //�^�C�}�[
			UpdateScore();          //�X�R�A
			UpdateSkillGage();      //�X�L���Q�[�W
			UpdateSkillName();      //�X�L�����O
			UpdateHealth();         //�̗�
			UpdateCombo();          //�R���{
		}
		else
		{
			UpdateCamera();         //�J����*
			UpdateLight();          //���C�g*

			//==============
			//���f��
			//==============
			UpdateEnemyEditor();    //�G�G�f�B�^

		}
	}

	if (g_bPause == true)
	{//�|�[�Y��
	//�|�[�Y�̍X�V����
		UpdatePause();
		g_nCountPauseMenu++;
		if (g_nCountPauseMenu == 1)
		{//�|�[�Y��ʂ̑I���ʒu�̏����ʒu��ݒ�B
			g_nChoosePauseCommand = 0;
		}
		if (GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(JOYKEY_DOWN) == true)
		{
			StopSound(SOUND_LABEL_SE_SELECT_000);
			g_nChoosePauseCommand += 1;//���ɑI�����ړ�����B
		}
		if (GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(JOYKEY_UP) == true)
		{
			StopSound(SOUND_LABEL_SE_SELECT_000);
			g_nChoosePauseCommand -= 1;//��ɑI�����ړ�����
		}

		if (g_nChoosePauseCommand == -1)
		{//�I���ꏊ�������ֈړ�
			g_nChoosePauseCommand = 2;
		}
		if (g_nChoosePauseCommand == 3)
		{//�I���ꏊ���㑤�ֈړ�
			g_nChoosePauseCommand = 0;
		}

		if (g_nChoosePauseCommand == 0)
		{//�R���e�B�j���[�R�}���h��I��
			SetEnablePause(PAUSE_MENU_CONTINUE);

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(JOYKEY_START) == true)
			{
				g_bPause = false;
			}
		}
		if (g_nChoosePauseCommand == 1)
		{//���g���C�R�}���h��I��
			SetEnablePause(PAUSE_MENU_RETRY);
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(JOYKEY_START) == true)
			{
				SetMode(MODE_GAME);
				StopSound(SOUND_LABEL_BGM004);
			}
		}
		if (g_nChoosePauseCommand == 2)
		{//�^�C�g����ʂɖ߂�R�}���h��I��
			SetEnablePause(PAUSE_MENU_QUIT);
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(JOYKEY_START) == true)
			{
				SetMode(MODE_TITLE);
				StopSound(SOUND_LABEL_BGM004);
			}
		}
	}

	bool bTimeUpFlag = CheckTime();

	if (bTimeUpFlag == true)
	{//�^�C�}�[���O�ɂȂ�����A�Q�[�����I��������B
		g_GameState = GAMESTATE_END;
	}
	//���̑�
	bool bDeathFlag = bPlayerDeath();
	if (bDeathFlag == true)
	{
		g_GameState = GAMESTATE_END;
	}

	if (GetKeyboardTrigger(DIK_0) == true /*|| GetJoyPadTrigger(JOYKEY_START) == true*/)
	{//�Q�[�������I���{�^��
		g_GameState = GAMESTATE_END;
	}

	switch (g_GameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 150)
		{
			StopSound(SOUND_LABEL_BGM004);
			SetFade(MODE_RESULT);
		}
		break;
	}
	
}

//======================================
//�Q�[����ʂ̕`�揈��
//======================================
void DrawGame(void)
{
	//DrawBG();
	if (g_bPause == true)
	{//�|�[�Y��
		//�|�[�Y�̕`�揈��
		DrawPause();
	}


	SetCamera();         //�J����
	DrawField();          //�t�B�[���h
	DrawWall();           //��

	//======================
	// �r���{�[�h
	//======================
	DrawDamage();         //�_���[�W�\�L
	DrawBullet();         //�e
	DrawAttackBillBoard();//�U���r���{�[�h

	//============================
	// ���f��
	//============================
	DrawSummon();         //����
	DrawModel();          //���f��
	DrawEnemy();          //�G
	DrawPlayer();         //�v���C���[
	DrawAttackModel();    //�U�����f��

	if (g_bEditEnemyMode == true)
	{
		DrawEnemyEditor();    //�G�G�f�B�^
	}
	//==================================================
	// �G�t�F�N�g�֌W
	//==================================================
	DrawEmitter();        //�G�~�b�^�[
	DrawShadow();         //�e
	DrawParticle();       //�p�[�e�B�N��
	DrawEffect();         //�G�t�F�N�g

	//===================================================
	// UI
	//===================================================
	DrawTimer();          //�^�C�}�[
	DrawScore();          //�X�R�A
	DrawSkillGage();      //�X�L���Q�[�W
	DrawSkillName();      //�X�L�����O
	DrawHealth();         //�̗�
	DrawCombo();          //�R���{

}

//============================================
//�Q�[���̏�Ԃ̐ݒ�
//============================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	
}

//==============================================
//�Q�[���̏�Ԃ̎擾
//==============================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}

bool bGetEditCheck(void)
{
	return g_bEditEnemyMode;
}
