//========================================================
//
//９月２６日：ハッカソンの基盤作り[Camera.cpp]
//Author:ShinaTaiyo
//
//=========================================================

#include "camera.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
//グローバル変数
//PDIRECT3DVERTEXBUFFER9 g_pVtxBuffCamera = NULL;//頂点バッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureCamera = NULL;//テクスチャへのポインタ
//D3DXVECTOR3 g_posCamera;//位置
//D3DXVECTOR3 g_rotCamera;//向き
//D3DXMATRIX g_mtxWorldCamera;//ワールドマトリックス(float4*4)

Camera g_Camera;//カメラの情報

float g_fCameraPosVX;//カメラのXの支点の位置を変える
float g_fCameraPosVY;//カメラのYの支点の位置を変える
float g_fCameraPosVZ;//カメラのZの支点の位置を変える

float g_fLength;//カメラとプレイヤーの距離
float g_fAngle;//カメラとプレイヤーの角度

//タイトル画面の初期化処理
void InitCamera(void)
{
	Player* pPlayer = GetPlayer();

	g_fLength = 0.0f;
	g_fAngle = 0.0f;
	g_fCameraPosVX = 0.0f;//カメラのXの支点の位置を変える
	g_fCameraPosVY = 350.0f;//カメラのYの支点の位置を変える
	g_fCameraPosVZ = 0.0f;//カメラのZの支点の位置を変える

	g_Camera.PosV = D3DXVECTOR3(pPlayer->pos.x, 200.0f,400.0f);//支点
	g_Camera.PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//注視点
	g_Camera.targetPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的のカメラの視点
	g_Camera.targetPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//目的のカメラの注視点
	g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//法線
	g_Camera.Decayrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fXVaim = 0.0f;
	g_Camera.fZVaim = 0.0f;
	//posV.yとposV.zが注視点からの距離になるため（カメラは中止点の後ろから見るから）、posV.yとposV.zをsqrtfして,ちゃんとした距離を求める。
	g_Camera.fLength = 550.0f /*sqrtf(g_Camera.PosV.y * g_Camera.PosV.y + g_Camera.PosV.z * g_Camera.PosV.z) / 2*/;
	g_Camera.nMode = CAMERAMODE_REVOLUTION;//公転モードに初期化する
}

//==============================
//タイトル画面の終了処理
//==============================
void UninitCamera(void)
{
	
}
//============================
//タイトル画面の更新処理
//============================
void UpdateCamera(void)
{
	//==================================
	//取得している情報
	//==================================
	Player* pPlayer = GetPlayer();

	//============================================================

	//========================
	//カメラの操作
	//========================
	ControlCamera();

	//============================================================

	g_Camera.Decayrot.y += (0.0f - g_Camera.Decayrot.y) * 0.5f;

	g_Camera.rot.y += g_Camera.Decayrot.y;

	//==============================================
	//通常カメラモード
	//==============================================
	if (g_Camera.nMode == CAMERAMODE_REVOLUTION)
	{
		g_Camera.targetPosR = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);//注視点
		g_Camera.targetPosV = D3DXVECTOR3(sinf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosR.x,
			200.0f + g_Camera.PosR.y + g_fCameraPosVY,
			cosf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosR.z);//視点

		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向ベクトル

        //=============
		//慣性移動処理
		//===============
		g_Camera.PosR += (g_Camera.targetPosR - g_Camera.PosR) * 0.1f;
		g_Camera.PosV += (g_Camera.targetPosV - g_Camera.PosV) * 0.1f;

		//==========================================================================
	}

	//=============================================================================================================================
	
	//================================================
	//回転カメラモード
	//================================================
	if (g_Camera.nMode == CAMERAMODE_ROTATION)
	{
		g_Camera.PosR = D3DXVECTOR3(sinf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosV.x,
		    0.0f,
			cosf(D3DX_PI + g_Camera.rot.y) * g_Camera.fLength + g_Camera.PosV.z);
		g_Camera.PosV = g_Camera.PosV;
		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向ベクトル
	}

	//===========================================================================================================
}



//================================
//タイトル画面の描画処理
//================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		4500.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&g_Camera.PosV,
		&g_Camera.PosR,
		&g_Camera.VecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}

void ControlCamera(void)
{

	if (GetKeyboardPress(DIK_O) == true)
	{//上へ移動
		g_fCameraPosVY += 5.0f;
	}
	if (GetKeyboardPress(DIK_L) == true)
	{//下へ移動
		g_fCameraPosVY -= 5.0f;
	}
	if (GetKeyboardPress(DIK_U) == true || GetJoypadPress(JOYKEY_R1) == true)
	{//カメラを右に回転
		g_Camera.Decayrot.y += 0.1f;
	}
	if (GetKeyboardPress(DIK_J) == true || GetJoypadPress(JOYKEY_L1) == true)
	{//カメラを左に回転
		g_Camera.Decayrot.y += -0.1f;
	}
	if (GetKeyboardTrigger(DIK_C) == true)
	{//カメラモード変更
		g_Camera.nMode++;

		if (g_Camera.nMode == 2)
		{
			g_Camera.nMode = 0;
		}
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{//注視点との距離を遠くする
		g_Camera.fLength += 10.0f;
	}
	if (GetKeyboardPress(DIK_X) == true)
	{//注視点の距離を短くする
		g_Camera.fLength -= 10.0f;
	}
}

//====================
//カメラ情報の取得
//====================
Camera* GetCamera(void)
{
	return &g_Camera;
}