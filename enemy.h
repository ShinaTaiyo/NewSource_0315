//========================================================
//
//１１月７日：Xファイルを読み込む[Enemy.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define NUM_ENEMY (11)//敵の種類
#define MAX_ENEMY (1024)//読み込む敵の最大数
#define ENEMYSET "data\\TEXTFILE\\Enemy.txt"
#define MAX_ENEMYTEXTURE (100)

typedef struct
{
	LPD3DXMESH pMesh;//メッシュ（頂点情報）へのポインタ（モデルの種類数分）
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;//マテリアルの数
	LPDIRECT3DTEXTURE9 apTextureEnemy[MAX_ENEMYTEXTURE];//テクスチャへのポインタ
}EnemyModelInfo;


typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 posOld;//1F前の位置
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 vtxMinEnemy;//それぞれの座標の敵の位置の最小値
	D3DXVECTOR3 vtxMaxEnemy;//それぞれの座標の敵の位置の最大値
	D3DXMATRIX mtxWorld;    //マトリックス

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ
	int nType;//種類
	int nIdxShadow;//影のインデックス
	bool bUse;//使用しているかどうか
	bool bIsLanding;//地面にいるかどうか

	int nHp;//体力
	int nAttack;//攻撃力
	int nDefeatScore;//倒したときにもらえるスコア
	float fSpeed;//速さ

	float fVXaim;//X方向のベクトル
	float fVYaim;//Y方向のベクトル
	float fVZaim;//Z方向のベクトル
	float fVaim;//総合したベクトル
	float fVaimY1;//総合したY方向のベクトル
	float fVaimY2;
	float fVaim3;

	float fPenduram;//振り子のように弾を発射させる変数
	bool bPenduramFlag;

	D3DXVECTOR3 Size;//敵の大きさ
}Enemy;

typedef enum
{
	ENEMY00_NOOBSLIME = 0,//弱いスライム
	ENEMY01_ANGRYSLIME,//怒りスライム
	ENEMY02_SWORDSLIME,//剣スライム
	ENEMY03_HAMMERSLIME,//ハンマースライム
	ENEMY04_ORANGESLIME,//オレンジスライム
	ENEMY05_GREENSLIME,//グリーンスライム
	ENEMY06_WHITESLIME,//ホワイトスライム
	ENEMY07_TURQUOISSLIME,//ターコイズスライム
	ENEMY08_ENGELSLIME,//エンジェルスライム
	ENEMY09_DARKSLIME,//ダークスライム
	ENEMY10_RAINBOWSLIME,//レインボースライム
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


//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
Enemy* GetEnemy(void);//敵構造体の情報を取得する

void SetDamageEnemy(int nDamage,int nNumEnemy);

#endif


