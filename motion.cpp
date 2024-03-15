//========================================================
//
//１１月７日：モデル読み込み[Motion.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "motion.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

//グローバル変数
int g_nNumMotion = 0;//読み込むモデルの最大数を決める

int g_nUseMotion = 0;//何番のモーションを使っているか

int g_nCntFrame = 0;//フレームの長さを測る
#define Motion_SCALE (10.0f)
//#define SAVEMotion "data\\TEXTFILE\\SaveMotion.txt"

#define MAX_TEXTURE (32)


typedef struct
{
	LPD3DXMESH pMeshMotion;//メッシュ（頂点情報）へのポインタ（モデルの種類数分）
	LPD3DXBUFFER pBuffMatMotion;//マテリアルへのポインタ
	DWORD dwNumMatMotion;//マテリアルの数
	LPDIRECT3DTEXTURE9 apTextureMotion[MAX_TEXTURE];//テクスチャへのポインタ
}MotionMat;

D3DXVECTOR3 g_posMotion;//位置
D3DXVECTOR3 g_rotMotion;//向き
D3DXMATRIX g_mtxWorldMotion;//ワールドマトリックス

//Motion g_aMotion[MAX_MOTION];//モデル情報の構造体

MotionMat g_aMotionMat[NUM_MOTION];//モデルのマテリアルや頂点の構造体

int g_nCntKeySet;//キーセットをカウントする

//int g_nldxShadow = -1;//対象の影のインデックス（番号）
//bool g_bIsLanding;//地面にいるかどうか

int g_nNowKey;//現在のキー
int g_nNowMotion;//現在のモーション

//====================
//モーション関連処理
//====================
MotionSet g_aMotionSet[MAX_MOTION];//モーション設定処理

//タイトル画面の初期化処理
void InitMotion(void)
{
	//=======================
	//初期化処理
	//=======================
	int g_nUseMotion = 0;//何番のモーションを使っているか
	g_nCntKeySet = 0;//キーセットをカウントする
	g_nCntFrame = 0;//フレームの長さを測る
	g_nNowKey = 0;
	g_nNowMotion = 0;
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		g_aMotionSet[nCntMotion].bLoop = false;//ループさせるかどうかのフラグ
		g_aMotionSet[nCntMotion].nNumKey = 0;//キーの数
		g_aMotionSet[nCntMotion].bUse = false;//モーションを使用するかどうか
		for (int nCntKeySet = 0; nCntKeySet < MAX_KEYSET; nCntKeySet++)
		{
			g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].nFrame = 0;//次のポーズまでの時間を決める

			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
			{
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0);//位置
				g_aMotionSet[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);//向き

			}
		}
	}
	//===========================================================================================================
	char aString[100];//文字列を読み込むための変数
	int nMaxRoadMotion = 0;//読み込むモデルの最大数
	int nType = 0;//読み込んだモデルの種類

	float fPosX = 0.0f;//モデルの位置X
	float fPosY = 0.0f;//モデルの位置Y
	float fPosZ = 0.0f;//モデルの位置Z

	float fRotX = 0.0f;//モデルの位置X
	float fRotY = 0.0f;//モデルの位置Y
	float fRotZ = 0.0f;//モデルの位置Z
	int nCnt = 0;//読み込むモデルを数える用
	int nIdx = 0;//インデックス
	int nCntMotionSet = 0;//セットするモーション数のカウント
	int nCntKeySet = 0;//キーセット数のカウント
	int nCntKey = 0;//キー数のカウント
	int nRoadModel = 0;//読み込むモデルの最大数
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタと取得


	FILE* pFile;//ファイルポインタ
	pFile = fopen(MOTIONSET, "r");
	char aStringPass[100] = {};
	Player* pPlayer = GetPlayer();
	if (pFile != NULL)//ファイルが開いているかどうか
	{
		while (1)
		{

			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{
				fclose(pFile);
				break;//行の最後でこの文字列を判定させることにより、ループを終わらせる
			}
			else if (aString[0] == '#')
			{
				fgets(&aString[0], 100, pFile);
				continue;
			}
			else if (strcmp(&aString[0], "NUM_MODEL") == 0)//読み込むモデルの種類数を決める
			{
		       fscanf(pFile, "%s", &aString[0]);
			fscanf(pFile, "%d", &g_nNumMotion);
			}
			else if (strcmp(&aString[0], "MOTIONSET") == 0)
			{
				while (1)
				{
					int nLoop = 0;
					fscanf(pFile, "%s", &aString[0]);
					if (aString[0] == '#')
					{
						fgets(&aString[0], 100, pFile);
						continue;
					}
					else if (strcmp(&aString[0], "LOOP") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);// =
						fscanf(pFile, "%d", &nLoop);//ループさせるかどうかを数値で宣言する

						if (nLoop == 0)
						{
							g_aMotionSet[nCntMotionSet].bLoop = false;//ループしない
						}
						else if (nLoop == 1)
						{
							g_aMotionSet[nCntMotionSet].bLoop = true;//ループする
						}
					}
					else if (strcmp(&aString[0], "NUM_KEY") == 0)//キー数
					{
						int nData = ~0;
						fscanf(pFile, "%s %d", &aString[0], &nData);// =
						g_aMotionSet[nCntMotionSet].nNumKey = nData;
					}
					else if (strcmp(&aString[0], "KEYSET") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aString[0]);// =
							if (aString[0] == '#')
							{
								fgets(&aString[0], 100, pFile);
								continue;
							}
							if (strcmp(&aString[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s %d", &aString[0], &g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].nFrame);//=,フレームの値
							}
							else if (strcmp(&aString[0], "KEY") == 0)
							{
								while (1)
								{
									fscanf(pFile, "%s", &aString[0]);

									if (aString[0] == '#')
									{
										fgets(&aString[0], 100, pFile);//その行を全文字読み取り、完全に終わらせる
										continue;
									}
									else if (strcmp(&aString[0], "POS") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &aString[0],
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.x,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.y,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Pos.z);
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{
										fscanf(pFile, "%s%f%f%f", &aString[0],
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.x,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.y,
											&g_aMotionSet[nCntMotionSet].aKeySet[nCntKeySet].aKey[nCntKey].Rot.z);
									}
									else if (strcmp(&aString[0], "END_KEY") == 0)
									{
										nCntKey++;
										break;
									}

								}
							}
							else if (strcmp(&aString[0], "END_KEYSET") == 0)
							{
								nCntKey = 0;
								nCntKeySet++;
								break;
							}
						}

					}
					else if (strcmp(&aString[0], "END_MOTIONSET") == 0)
					{
						nCntKeySet = 0;
						nCntMotionSet++;
						break;
					}
				}
			}
		}
	}
}

//============================
//モーションの更新処理
//============================
void UpdateMotion(void)
{
	Player* pPlayer = GetPlayer();

	bool bUse = true;
	//==============================
	//使用するモーションを決める
	//==============================
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		g_aMotionSet[nCntMotion].bUse = false;
	}
	g_nUseMotion = pPlayer->nState;
	g_nCntFrame++;
	if (g_nCntFrame >= g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].nFrame)
	{
		g_nCntFrame = 0;
		g_nCntKeySet++;
		if (g_nCntKeySet >= g_aMotionSet[g_nUseMotion].nNumKey)
		{
			g_nCntKeySet = 0;
			if (g_aMotionSet[g_nUseMotion].bLoop == false)
			{
				pPlayer->nState = PLAYERSTATE_NUTORAL;
				pPlayer->bMotionFlag = false;
			}
		}
		for (int nCntKey = 0; nCntKey < g_nNumMotion; nCntKey++)
		{
		//　ターゲット　＝　(現在呼び出しているモーションのキー　- (現在のプレイヤーのパーツの向き　- プレイヤーのパーツの初期設定）) / フレーム数 
			g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].TargetRot = (g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].Rot - (pPlayer->aModel[nCntKey].rot - pPlayer->aModel[nCntKey].SaveRot)) /
				(float)(g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].nFrame);	    
		}
	}

	for (int nCntKey = 0; nCntKey < g_nNumMotion; nCntKey++)
	{
		pPlayer->aModel[nCntKey].rot += g_aMotionSet[g_nUseMotion].aKeySet[g_nCntKeySet].aKey[nCntKey].TargetRot;
	}
}

void SetMotion(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, char aPath)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{
		if (g_aMotionSet[nCntMotion].bUse == false)
		{
			g_aMotionSet[nCntMotion].bUse = true;//使用しているかどうか
		
			

			break;
		}
	}
}