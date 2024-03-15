//========================================================
//
//１１月７日：モデル読み込み[Summon.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "Summon.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "player.h"
#include <stdio.h>
#include <string.h>
#include "model.h"
#include "score.h"
#include "bullet.h"
#include "combo.h"
#include "timer.h"
#include "enemy.h"
#include "game.h"
#include "editEnemy.h"
//グローバル変数
int g_nDelaySummon = 0;
float g_fRandumRot = 0;
float g_fRandumLength = 0;
float g_fRandumPos = 0;
int g_nType = 0;

int g_nMaxSummon;//召喚する敵の最大数

Summon g_aSummon[MAX_SUMMON];//敵召喚構造体
SummonModelInfo g_aSummonModelInfo[NUM_ENEMY];

//タイトル画面の初期化処理
void InitSummon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタと取得


	D3DXMATERIAL* pMat;//マテリアルへのポインタ
	g_nDelaySummon = 0;
	g_fRandumRot = 0;
	g_fRandumLength = 0;
	g_fRandumPos = 0;
	g_nType = 0;
	g_nMaxSummon = 0;

	for (int nCntModelInfo = 0; nCntModelInfo < NUM_ENEMY; nCntModelInfo++)
	{
		g_aSummonModelInfo[nCntModelInfo].dwNumMat = {};
		g_aSummonModelInfo[nCntModelInfo].pBuffMat = {};
		g_aSummonModelInfo[nCntModelInfo].pMesh = {};
	}

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		g_aSummon[nCntSummon].bUse = false;//使用しているかどうか
		g_aSummon[nCntSummon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_aSummon[nCntSummon].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		g_aSummon[nCntSummon].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_aSummon[nCntSummon].nType = 0;//召喚する敵の種類
		g_aSummon[nCntSummon].nSummonTime = 0;//敵を召喚する時間
		g_aSummon[nCntSummon].mtxWorld;//マトリックスワールド
		g_aSummon[nCntSummon].nNumSetEdit = -1;//エディターでセットされた敵の番号
		g_aSummon[nCntSummon].bRemote = false;//遠隔からの変更を受けるかどうか

		for (int nCntModelInfo = 0; nCntModelInfo < NUM_ENEMY; nCntModelInfo++)
		{
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].dwNumMat = {};
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].pBuffMat = {};
			g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].pMesh = {};

			for (int nCntMat = 0; nCntMat < MAX_SUMMONMAT; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nCntModelInfo].Diffuse[nCntMat] = {};
			}
		}
	}



	for (int nCntType = 0; nCntType < NUM_ENEMY; nCntType++)
	{
		D3DXLoadMeshFromX(ENEMY_FILENAME[nCntType],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aSummonModelInfo[nCntType].pBuffMat,//モデルでは、これも配列にする
			NULL,
			&g_aSummonModelInfo[nCntType].dwNumMat,//モデルでは、これも配列にする
			&g_aSummonModelInfo[nCntType].pMesh);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aSummonModelInfo[nCntType].pBuffMat->GetBufferPointer();

		for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_aSummonModelInfo[nCntType].dwNumMat; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nCntType].Diffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
				g_aSummon[nCntSummon].SummonModelInfo[nCntType].FormarDiffuse[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;//元の色合い
			}
		}
	}
	


	char aString[100] = {};//文字列を読み込むための変数
	int nMaxRoadEnemy = 0;//読み込むモデルの最大数
	int nType = 0;//読み込んだモデルの種類

	float fPosX = 0.0f;//モデルの位置X
	float fPosY = 0.0f;//モデルの位置Y
	float fPosZ = 0.0f;//モデルの位置Z

	float fRotX = 0.0f;//モデルの位置X
	float fRotY = 0.0f;//モデルの位置Y
	float fRotZ = 0.0f;//モデルの位置Z
	int nCnt = 0;//読み込むモデルを数える用

	int nSummonTime = 0;//召喚する時間を宣言する
	FILE* pFile;//ファイルポインタ

	char aStringPass[100] = {};

	pFile = fopen(SUMMONSET, "r");
	
	if (pFile != NULL)//ファイルが開いているかどうか
	{
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);
			if (aString[0] == '#')
			{
				fgets(&aString[0], 100, pFile);
				continue;
			}
			if (strcmp(&aString[0], "ENDSCRIPT") == 0)
			{
				fclose(pFile);
				break;//行の最後でこの文字列を判定させることにより、ループを終わらせる
			}
			else if (strcmp(&aString[0], "SUMMONSET") == 0)
			{
				g_nMaxSummon++;//敵を召喚する最大数をインクリメントする
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);
					if (aString[0] == '#')
					{
						fgets(&aString[0], 100, pFile);
						continue;
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);//ウォールの種類を決める
					}
					else if (strcmp(&aString[0], "POS") == 0)
					{
						fscanf(pFile, "%f%f%f", &fPosX, &fPosY, &fPosZ);//位置情報を読み込む
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{
						fscanf(pFile, "%f%f%f", &fRotX, &fRotY, &fRotZ);//向き情報を読み込む
					}
					else if (strcmp(&aString[0], "TIME") == 0)
					{
						fscanf(pFile,"%d",&nSummonTime);//召喚する時間を読み込む。
					}
					else if (strcmp(&aString[0], "ENDSUMMONSET") == 0)
					{//初期化でセットされたデータは、既にあるデータなので、エディタの配置にはカウントしない
						SetSummon(nType,nSummonTime,-1,false,D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(fRotX, fRotY, fRotZ));
						break;
					}
				}
			}
		}
	}
}

void UninitSummon(void)
{
	for (int nCntSummon = 0; nCntSummon < NUM_ENEMY; nCntSummon++)
	{
		//メッシュの破棄
		if (g_aSummonModelInfo[nCntSummon].pMesh != NULL)
		{
			g_aSummonModelInfo[nCntSummon].pMesh->Release();
			g_aSummonModelInfo[nCntSummon].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_aSummonModelInfo[nCntSummon].pBuffMat != NULL)
		{
			g_aSummonModelInfo[nCntSummon].pBuffMat->Release();
			g_aSummonModelInfo[nCntSummon].pBuffMat = NULL;
		}
	}
}

//============================
//モデルの更新処理
//============================
void UpdateSummon(void)
{
	Player* pPlayer = GetPlayer();

	g_nDelaySummon++;

	g_fRandumRot = float(rand() % 200 + 1) / 100;
	int nGetTimer = GetTimer();//残り時間の取得
	int nLottery = rand() % 1001 + 1;//召喚する敵を抽選する

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].bUse == true && g_aSummon[nCntSummon].nSummonTime == nGetTimer)//使用しているかつ、召喚時間が一致したら
		{
			SetEnemy(g_aSummon[nCntSummon].pos, g_aSummon[nCntSummon].rot, g_aSummon[nCntSummon].nType);
			g_aSummon[nCntSummon].bUse = false;//一回召喚したので用済み
		}
	}
	

	if (150 <= nGetTimer && nGetTimer <= 180)//開始３０秒
	{
		if (g_nDelaySummon % 20 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置
			
			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//70%の確率で、弱スライムが登場
			}
			else if (901 <= nLottery && nLottery <= 950)
			{
				g_nType = ENEMY01_ANGRYSLIME;//7%の確率で怒りスライムが登場
			}
			else if (951 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY03_HAMMERSLIME;//3%の確率でハンマースライムが登場
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (120 <= nGetTimer && nGetTimer <= 150)
	{
		if (g_nDelaySummon % 17 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (901 <= nLottery && nLottery <= 930)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (931 <= nLottery && nLottery <= 950)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (951 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (90 <= nGetTimer && nGetTimer <= 120)
	{
		if (g_nDelaySummon % 15 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (901 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (926 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (941 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (60 <= nGetTimer && nGetTimer <= 90)
	{
		if (g_nDelaySummon % 12 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (901 <= nLottery && nLottery <= 915)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (916 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (925 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (946 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (60 <= nGetTimer && nGetTimer <= 90)
	{
		if (g_nDelaySummon % 9 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (901 <= nLottery && nLottery <= 915)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (916 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (925 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (946 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (971 <= nLottery && nLottery <= 980)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (981 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (30 <= nGetTimer && nGetTimer <= 60)
	{
		if (g_nDelaySummon % 5 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 880)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (881 <= nLottery && nLottery <= 890)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (891 <= nLottery && nLottery <= 900)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (901 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (926 <= nLottery && nLottery <= 940)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (941 <= nLottery && nLottery <= 955)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (956 <= nLottery && nLottery <= 970)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (971 <= nLottery && nLottery <= 985)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (986 <= nLottery && nLottery <= 995)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (996 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);

		}
	}
	else if (0 <= nGetTimer && nGetTimer <= 30)
	{
		if (g_nDelaySummon % 4 == 0)
		{
			g_fRandumLength = float(rand() % 1000 + 500);//召喚する位置

			if (0 <= nLottery && nLottery <= 870)
			{
				g_nType = ENEMY00_NOOBSLIME;//80%の確率で、弱スライムが登場
			}
			else if (871 <= nLottery && nLottery <= 875)
			{
				g_nType = ENEMY01_ANGRYSLIME;//8%の確率で怒りスライムが登場
			}
			else if (876 <= nLottery && nLottery <= 880)
			{
				g_nType = ENEMY02_SWORDSLIME;//5%の確率でソードスライムが登場
			}
			else if (881 <= nLottery && nLottery <= 885)
			{
				g_nType = ENEMY03_HAMMERSLIME;//5%の確率でハンマースライムが登場
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY04_ORANGESLIME;//5%の確率でオレンジスライムが登場
			}
			else if (886 <= nLottery && nLottery <= 895)
			{
				g_nType = ENEMY05_GREENSLIME;
			}
			else if (896 <= nLottery && nLottery <= 910)
			{
				g_nType = ENEMY06_WHITESLIME;
			}
			else if (911 <= nLottery && nLottery <= 925)
			{
				g_nType = ENEMY07_TURQUOISSLIME;
			}
			else if (926 <= nLottery && nLottery <= 945)
			{
				g_nType = ENEMY08_ENGELSLIME;
			}
			else if (946 <= nLottery && nLottery <= 965)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (966 <= nLottery && nLottery <= 990)
			{
				g_nType = ENEMY09_DARKSLIME;
			}
			else if (991 <= nLottery && nLottery <= 1000)
			{
				g_nType = ENEMY10_RAINBOWSLIME;
			}
			SetEnemy(D3DXVECTOR3(pPlayer->pos.x + sinf(-D3DX_PI * g_fRandumRot) * g_fRandumLength, pPlayer->pos.y, pPlayer->pos.z + cosf(-D3DX_PI * g_fRandumRot) * g_fRandumLength),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_nType);
		}
	}
}

void DrawSummon(void)
{
	EnemyEditor* pEnemyEditor = GetEnemyEditor();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();;//デバイスへのポインタと取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	bool bEditCheck = bGetEditCheck();

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].nSummonTime == pEnemyEditor->nSummonTime && g_aSummon[nCntSummon].bUse == true)
		{//使用状態であるかつ、召喚時間が、敵エディタの召喚時間と一致していたら描画を開始

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aSummon[nCntSummon].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSummon[nCntSummon].rot.y, g_aSummon[nCntSummon].rot.x, g_aSummon[nCntSummon].rot.z);

			D3DXMatrixMultiply(&g_aSummon[nCntSummon].mtxWorld, &g_aSummon[nCntSummon].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aSummon[nCntSummon].pos.x, g_aSummon[nCntSummon].pos.y, g_aSummon[nCntSummon].pos.z);
			D3DXMatrixMultiply(&g_aSummon[nCntSummon].mtxWorld, &g_aSummon[nCntSummon].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aSummon[nCntSummon].mtxWorld);


			//マテリアルへのポインタを取得（セットしたモデルと同じタイプ）
			pMat = (D3DXMATERIAL*)g_aSummonModelInfo[g_aSummon[nCntSummon].nType].pBuffMat->GetBufferPointer();

			int nNumTexture = 0;
			//セットされたモデルとタイプが同じもののモデルのマテリアルの数分読み込む。
			for (int nCntMat = 0; nCntMat < (int)g_aSummonModelInfo[g_aSummon[nCntSummon].nType].dwNumMat; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse = g_aSummon[nCntSummon].SummonModelInfo[g_aSummon[nCntSummon].nType].Diffuse[nCntMat];

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		       //テクスチャの設定
		       pDevice->SetTexture(0,NULL);

				//モデル（パーツ）の描画
				g_aSummonModelInfo[g_aSummon[nCntSummon].nType].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================
//召喚する敵の情報のセット
//==============================
void SetSummon(int nType, int nTime, int nNumSetEdit, bool bRemote, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntSummon = 0; nCntSummon < MAX_SUMMON; nCntSummon++)
	{
		if (g_aSummon[nCntSummon].bUse == false)
		{
			g_aSummon[nCntSummon].bUse = true;
			g_aSummon[nCntSummon].pos = pos;//位置
			g_aSummon[nCntSummon].rot = rot;//向き
			g_aSummon[nCntSummon].nType = nType;//召喚する敵の種類
			g_aSummon[nCntSummon].nSummonTime = nTime;//敵を召喚する時間
			g_aSummon[nCntSummon].nNumSetEdit = nNumSetEdit;//エディタで配置された敵の番号	
			g_aSummon[nCntSummon].bRemote = bRemote;//遠隔からの変更を受けるかどうか
			for (int nCntMat = 0; nCntMat < MAX_SUMMONMAT; nCntMat++)
			{
				g_aSummon[nCntSummon].SummonModelInfo[nType].Diffuse[nCntMat].a = 0.5f;//色合い
			}
			break;
		}
	}
}


//===================================
//構造体の情報を取得
//===================================
Summon* GetSummon(void)
{
	return &g_aSummon[0];
}

//==============================================================================================================================


