//========================================================
//
//８月３０日：エフェクトもう一回見直す[game.cpp]
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
//グローバル変数
//==============================
GAMESTATE g_GameState = GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター
int g_nCountTime;//ゲーム開始時から経った時間を管理する変数
bool g_bPause = false;//ポーズ中かどうか
int g_nChoosePauseCommand;//ポーズ中の時に選択するメニューを選択する変数
int g_nCountPauseMenu;//ポーズ画面を開いている時間をカウントする変数
bool g_bEditEnemyMode = false;//敵エディタ中かどうか

//============================================================================================================

//===================================
//ゲーム画面の初期化処理
//===================================
void InitGame(void)
{
	g_bEditEnemyMode = false;        //敵エディタ中かどうか
	g_nChoosePauseCommand = 0;       //どのポーズコマンドを選んでいるか
	g_nCountPauseMenu = 0;           //ポーズ画面を開いている時間
	g_nCountTime = 0;                //ゲームが始まってからの時間
	g_bPause = false;                //ポーズ中かどうか


	//敵召喚用
	InitCamera();         //カメラ
	InitMotion();         //モーション
	InitLight();          //ライト
	InitField();          //フィールド
	InitWall();           //壁

	//======================
	// ビルボード
	//======================
	InitDamage();         //ダメージ表記
	InitBullet();         //弾
	InitAttackBillBoard();//攻撃ビルボード

	//============================
	// モデル
	//============================
	InitSummon();         //召喚
	InitModel();          //モデル
	InitEnemy();          //敵
	InitPlayer();         //プレイヤー
	InitAttackModel();    //攻撃モデル
	InitEnemyEditor();    //敵エディタ

	//==================================================
	// エフェクト関係
	//==================================================
	InitEmitter();        //エミッター
	InitShadow();         //影
	InitParticle();       //パーティクル
	InitEffect();         //エフェクト

	//===================================================
	// UI
	//===================================================
	InitTimer();          //タイマー
	InitScore();          //スコア
	InitSkillGage();      //スキルゲージ
	InitSkillName();      //スキル名前
	InitHealth();         //体力
	InitCombo();          //コンボ
	InitPause();          //ポーズ


	//=============================================================================================
	g_GameState = GAMESTATE_NORMAL;//ゲームの状態

	g_nCounterGameState = 0;

	PlaySound(SOUND_LABEL_BGM004);
}

//==================================
//ゲーム画面の終了処理
//==================================
void UninitGame(void)
{
	//敵召喚用
	UninitCamera();         //カメラ
	UninitLight();          //ライト
	UninitField();          //フィールド
	UninitWall();           //壁

	//======================
	// ビルボード
	//======================
	UninitDamage();         //ダメージ表記
	UninitBullet();         //弾
	UninitAttackBillBoard();//攻撃ビルボード

	//============================
	// モデル
	//============================
	UninitSummon();         //召喚
	UninitModel();          //モデル
	UninitEnemy();          //敵
	UninitPlayer();         //プレイヤー
	UninitAttackModel();    //攻撃モデル
	UninitEnemyEditor();    //敵エディタ

	//==================================================
	// エフェクト関係
	//==================================================
	UninitEmitter();        //エミッター
	UninitShadow();         //影
	UninitParticle();       //パーティクル
	UninitEffect();         //エフェクト

	//===================================================
	// UI
	//===================================================
	UninitTimer();          //タイマー
	UninitScore();          //スコア
	UninitSkillGage();      //スキルゲージ
	UninitSkillName();      //スキル名前
	UninitHealth();         //体力
	UninitCombo();          //コンボ
	UninitPause();          //ポーズ

}

//=================================
//ゲーム画面の更新処理
//=================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true||GetJoyPadTrigger(JOYKEY_BACK)==true)
	{//ポーズキーが押された
		g_bPause = g_bPause ? false : true;
	}

	if (GetKeyboardTrigger(DIK_F5) == true )
	{//敵エディタボタンが押された
		g_bEditEnemyMode = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		if (g_bEditEnemyMode == false)
		{
			g_nCountPauseMenu = 0;

			g_nCountTime++;//ゲーム開始時からの時間を計測する。
			UpdateCamera();         //カメラ*
			UpdateLight();          //ライト*
			UpdateField();          //フィールド
			UpdateWall();           //壁

			//======================
			// ビルボード
			//======================
			UpdateDamage();         //ダメージ表記
			UpdateBullet();         //弾
			UpdateAttackBillBoard();//攻撃ビルボード

			//============================
			// モデル
			//============================
			UpdateSummon();         //召喚
			UpdateModel();          //モデル
			UpdateEnemy();          //敵
			UpdatePlayer();         //プレイヤー
			UpdateAttackModel();    //攻撃モデル
			//==================================================
			// エフェクト関係
			//==================================================
			UpdateEmitter();        //エミッター
			UpdateShadow();         //影
			UpdateParticle();       //パーティクル
			UpdateEffect();         //エフェクト

			//===================================================
			// UI
			//===================================================
			UpdateTimer();          //タイマー
			UpdateScore();          //スコア
			UpdateSkillGage();      //スキルゲージ
			UpdateSkillName();      //スキル名前
			UpdateHealth();         //体力
			UpdateCombo();          //コンボ
		}
		else
		{
			UpdateCamera();         //カメラ*
			UpdateLight();          //ライト*

			//==============
			//モデル
			//==============
			UpdateEnemyEditor();    //敵エディタ

		}
	}

	if (g_bPause == true)
	{//ポーズ中
	//ポーズの更新処理
		UpdatePause();
		g_nCountPauseMenu++;
		if (g_nCountPauseMenu == 1)
		{//ポーズ画面の選択位置の初期位置を設定。
			g_nChoosePauseCommand = 0;
		}
		if (GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(JOYKEY_DOWN) == true)
		{
			StopSound(SOUND_LABEL_SE_SELECT_000);
			g_nChoosePauseCommand += 1;//下に選択を移動する。
		}
		if (GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(JOYKEY_UP) == true)
		{
			StopSound(SOUND_LABEL_SE_SELECT_000);
			g_nChoosePauseCommand -= 1;//上に選択を移動する
		}

		if (g_nChoosePauseCommand == -1)
		{//選択場所を下側へ移動
			g_nChoosePauseCommand = 2;
		}
		if (g_nChoosePauseCommand == 3)
		{//選択場所を上側へ移動
			g_nChoosePauseCommand = 0;
		}

		if (g_nChoosePauseCommand == 0)
		{//コンティニューコマンドを選択
			SetEnablePause(PAUSE_MENU_CONTINUE);

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(JOYKEY_START) == true)
			{
				g_bPause = false;
			}
		}
		if (g_nChoosePauseCommand == 1)
		{//リトライコマンドを選択
			SetEnablePause(PAUSE_MENU_RETRY);
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(JOYKEY_START) == true)
			{
				SetMode(MODE_GAME);
				StopSound(SOUND_LABEL_BGM004);
			}
		}
		if (g_nChoosePauseCommand == 2)
		{//タイトル画面に戻るコマンドを選択
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
	{//タイマーが０になったら、ゲームを終了させる。
		g_GameState = GAMESTATE_END;
	}
	//その他
	bool bDeathFlag = bPlayerDeath();
	if (bDeathFlag == true)
	{
		g_GameState = GAMESTATE_END;
	}

	if (GetKeyboardTrigger(DIK_0) == true /*|| GetJoyPadTrigger(JOYKEY_START) == true*/)
	{//ゲーム強制終了ボタン
		g_GameState = GAMESTATE_END;
	}

	switch (g_GameState)
	{
	case GAMESTATE_NORMAL://通常状態
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
//ゲーム画面の描画処理
//======================================
void DrawGame(void)
{
	//DrawBG();
	if (g_bPause == true)
	{//ポーズ中
		//ポーズの描画処理
		DrawPause();
	}


	SetCamera();         //カメラ
	DrawField();          //フィールド
	DrawWall();           //壁

	//======================
	// ビルボード
	//======================
	DrawDamage();         //ダメージ表記
	DrawBullet();         //弾
	DrawAttackBillBoard();//攻撃ビルボード

	//============================
	// モデル
	//============================
	DrawSummon();         //召喚
	DrawModel();          //モデル
	DrawEnemy();          //敵
	DrawPlayer();         //プレイヤー
	DrawAttackModel();    //攻撃モデル

	if (g_bEditEnemyMode == true)
	{
		DrawEnemyEditor();    //敵エディタ
	}
	//==================================================
	// エフェクト関係
	//==================================================
	DrawEmitter();        //エミッター
	DrawShadow();         //影
	DrawParticle();       //パーティクル
	DrawEffect();         //エフェクト

	//===================================================
	// UI
	//===================================================
	DrawTimer();          //タイマー
	DrawScore();          //スコア
	DrawSkillGage();      //スキルゲージ
	DrawSkillName();      //スキル名前
	DrawHealth();         //体力
	DrawCombo();          //コンボ

}

//============================================
//ゲームの状態の設定
//============================================
void SetGameState(GAMESTATE state)
{
	g_GameState = state;
	
}

//==============================================
//ゲームの状態の取得
//==============================================
GAMESTATE GetGameState(void)
{
	return g_GameState;
}

bool bGetEditCheck(void)
{
	return g_bEditEnemyMode;
}
