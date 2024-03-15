//========================================================
//
//９月２６日：ハッカソンの基盤作り[Particle.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "particle.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "shadow.h"
#include "enemy.h"
#include "damage.h"

#define Particle_SCALE (10.0f)
//グローバル変数
PDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle[NUM_PARTICLE] = {};//テクスチャへのポインタ
D3DXVECTOR3 g_posParticle;//位置
//D3DXVECTOR3 g_rotParticle;//向き
D3DXMATRIX g_mtxWorldParticle;//ワールドマトリックス(float4*4)

Particle g_aParticle[MAX_PARTICLE];//弾の構造体情報



//タイトル画面の初期化処理
void InitParticle(void)
{


	//bFadeFlag = false;

	//g_nCntTime = 0;

	//g_nColorChange = 255;//カラーの初期化（白色）

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureParticle[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ChainFire.png",
		&g_pTextureParticle[1]);

	g_posParticle = D3DXVECTOR3(0.0f, 50.0f, 100.0f);//位置の初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,//頂点の数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
		g_aParticle[nCntParticle].nLife = 0;//体力
		g_aParticle[nCntParticle].fRWidth = 0.0f;//幅（半径）
		g_aParticle[nCntParticle].fRHeight = 0.0f;//高さ（半径）
		g_aParticle[nCntParticle].nType = 0;//種類
		g_aParticle[nCntParticle].bUse = false;//使用しているかどうか
		g_aParticle[nCntParticle].nIdxShadow = -1;//影のインデックス
		g_aParticle[nCntParticle].fScale = 0.0f;//大きさ
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//色
		g_aParticle[nCntParticle].fRedution = 0.0f;//エフェクトを小さくするスピード
		g_aParticle[nCntParticle].fRotMove = 0.0f;//動く向きの数値を決める
		g_aParticle[nCntParticle].nType = 0;//パーティクルの種類
		g_aParticle[nCntParticle].nTexType;//パーティクルのテクスチャの種類
		g_aParticle[nCntParticle].nAnimationPattern = 0;//アニメーションパターン
		g_aParticle[nCntParticle].nAnimaitonCount = 0;//アニメーションカウント
	}




	////タイトル画面BGMの設定
	//PlaySound(SOUND_LABEL_BGM000);

	VERTEX_3D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//頂点座標の設定（初期位置）
		pVtx[0].pos = D3DXVECTOR3(-Particle_SCALE, Particle_SCALE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Particle_SCALE, Particle_SCALE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-Particle_SCALE, -Particle_SCALE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Particle_SCALE, -Particle_SCALE, 0.0f);

		//norの設定（初期設定）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLORは、0.0f〜1.0fの間の数値で色を変える。
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLORは、0.0f〜1.0fの間の数値で色を変える。
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLORは、0.0f〜1.0fの間の数値で色を変える。
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//D3DXCOLORは、0.0f〜1.0fの間の数値で色を変える。

		//テクスチャ座標の設定（初期設定）
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//ポインタを進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//==============================
//タイトル画面の終了処理
//==============================
void UninitParticle(void)
{
	for (int nCnt = 0; nCnt < NUM_PARTICLE; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureParticle[nCnt] != NULL)
		{
			g_pTextureParticle[nCnt]->Release();
			g_pTextureParticle[nCnt] = NULL;
		}
		
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}
//============================
//タイトル画面の更新処理
//============================
void UpdateParticle(void)
{
	VERTEX_3D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{

		if (g_aParticle[nCntParticle].bUse == true)
		{
			Enemy* pEnemy = GetEnemy();

			g_aParticle[nCntParticle].nLife -= 1;

			g_aParticle[nCntParticle].fScale -= g_aParticle[nCntParticle].fRedution;

			

			if (g_aParticle[nCntParticle].nType == PARTICLETYPE_GRAVITY)
			{
				g_aParticle[nCntParticle].move.y += -1.0f;
			}

			if (g_aParticle[nCntParticle].nTexType == PARTICLETEX_NORMAL)
			{
				//テクスチャ座標の設定（初期設定）
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aParticle[nCntParticle].nTexType == PARTICLETEX_CHAINFIRE)
			{

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fScale >= pEnemy->pos.x - pEnemy->Size.x / 2 &&
							g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fScale <= pEnemy->pos.x + pEnemy->Size.x / 2 &&
							g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fScale >= pEnemy->pos.y - pEnemy->Size.y / 2 &&
							g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fScale <= pEnemy->pos.y + pEnemy->Size.y / 2 &&
							g_aParticle[nCntParticle].pos.z + g_aParticle[nCntParticle].fScale >= pEnemy->pos.z - pEnemy->Size.z / 2 &&
							g_aParticle[nCntParticle].pos.z - g_aParticle[nCntParticle].fScale <= pEnemy->pos.z + pEnemy->Size.z / 2)
						{
							pEnemy->nHp -= 8;
							g_aParticle[nCntParticle].bUse = false;
							SetDamage(8, 100, pEnemy->pos, 10.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

							for (int nCnt = 0; nCnt < 10; nCnt++)
							{
								float fRandumRot = float(rand() % 200 + 1) / 100;
								float fRandumSpeed = float(rand() % 50) / 10;
								float fRandumMove = float(rand() % 21 - 10);
								float fLength = float(rand() % 100 + 100);
								float fRandumPos = float(rand() % 100 + 50);

								int nFlag = rand() % 2 + 1;

								float fSave = fRandumPos;

								if (nFlag == 2)
								{
									fRandumPos = -fSave;
								}
								 
								SetParticle(PARTICLETYPE_NORMAL, 100, 30.0f, 0.4f, 
									D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + sinf(-D3DX_PI * fRandumRot) * fLength,g_aParticle[nCntParticle].pos.y + fRandumPos,g_aParticle[nCntParticle].pos.z +  cosf(-D3DX_PI * fRandumRot) * fLength),
									D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed,fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
									D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), 0.0f, PARTICLETEX_CHAINFIRE);

							/*	SetParticle(PARTICLETYPE_NORMAL, 100, 30.0f, 0.1f,
								    g_aParticle[nCntParticle].pos,
									D3DXVECTOR3(sinf(-D3DX_PI * fRandumRot) * fRandumSpeed, fRandumMove, cosf(-D3DX_PI * fRandumRot) * fRandumSpeed),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, PARTICLETEX_CHAINFIRE);*/
							}
						}
					}
				}

				g_aParticle[nCntParticle].nAnimaitonCount++;

				if (g_aParticle[nCntParticle].nAnimaitonCount % 5 == 0)
				{
					g_aParticle[nCntParticle].nAnimationPattern++;
					if (g_aParticle[nCntParticle].nAnimationPattern >= 5)
					{
						g_aParticle[nCntParticle].nAnimationPattern = 0;
					}
				}


				//テクスチャ座標の設定（初期設定）
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.2f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f + (0.2f * g_aParticle[nCntParticle].nAnimationPattern), 1.0f);
			}


			//頂点座標の設定（初期位置）
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fScale, g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fScale, g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fScale, -g_aParticle[nCntParticle].fScale, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fScale, -g_aParticle[nCntParticle].fScale, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			g_aParticle[nCntParticle].pos.x += g_aParticle[nCntParticle].move.x;
			g_aParticle[nCntParticle].pos.y += g_aParticle[nCntParticle].move.y;
			g_aParticle[nCntParticle].pos.z += g_aParticle[nCntParticle].move.z;

			if (g_aParticle[nCntParticle].nLife <= 0 || g_aParticle[nCntParticle].fScale <= 0.0f)
			{
				g_aParticle[nCntParticle].bUse = false;//体力が０になったらfalseにする
			}
		}

		pVtx += 4;//ポインタを進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}



//================================
//タイトル画面の描画処理
//================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

		//デバイスの取得
	pDevice = GetDevice();

	

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			D3DXMATRIX mtxTrans;//計算用マトリックス

			D3DXMATRIX mtxView;//ビューマトリックス取得用

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldParticle);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldParticle, NULL, &mtxView);

			//逆行列を求める
			g_mtxWorldParticle._41 = 0.0f;
			g_mtxWorldParticle._42 = 0.0f;
			g_mtxWorldParticle._43 = 0.0f;

			////向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotParticle.y, g_rotParticle.x, g_rotParticle.z);

			//D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldParticle, &g_mtxWorldParticle, &mtxTrans);

			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldParticle);

		


			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));//頂点バッファへのポインタと頂点情報の構造体のサイズ

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ライトを無効にする
			

			//aブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			for (int nCnt = 0; nCnt < NUM_PARTICLE; nCnt++)
			{
				if (g_aParticle[nCntParticle].nTexType== nCnt)
				{
					//テクスチャの設定
					pDevice->SetTexture(0, g_pTextureParticle[nCnt]);
				}
			}
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntParticle * 4, 2);//0は、描画する最初の頂点インデックスで、2は、描画するプリミティブ

			//aブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

void SetParticle(int nType, int nLife, float fScale, float fRedution, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRotMove, int nTexType)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].bUse = true;//使用しているかどうか
			g_aParticle[nCntParticle].pos = pos;//位置
			g_aParticle[nCntParticle].move = move;//移動量
			g_aParticle[nCntParticle].col = col;//色
			g_aParticle[nCntParticle].fRotMove = fRotMove;//動く向きの数値を決める
			g_aParticle[nCntParticle].nLife = nLife;//体力
			g_aParticle[nCntParticle].nType = nType;//種類
			g_aParticle[nCntParticle].nTexType = nTexType;//パーティクルのテクスチャの種類
			g_aParticle[nCntParticle].fScale = fScale;//大きさ
			g_aParticle[nCntParticle].fRedution = fRedution;//エフェクトを小さくするスピード
			g_aParticle[nCntParticle].nAnimationPattern = 0;//アニメーションパターン
			g_aParticle[nCntParticle].nAnimaitonCount = 0;//アニメーションカウント

			break;
		}
	}
}
