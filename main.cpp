//========================================================
//
//�W���R�O���F�G�t�F�N�g������񌩒���[main.cpp]
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
#include "debugproc.h"
//�}�N����`
#define CLASS_NAME "WindowClass" //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "���`�̃W���X�e�B�X�@�`�������������j�`" //�E�C���h�E�̂Ȃ܂��i�L�����v�����ɕ\���j
#define MAX_MOTIONMODE (15)//���샂�[�h�̐�

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update();
void Draw(void);
void DrawFPS(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;//FPS�J�E���^
MODE g_mode = MODE_TITLE;//���݂̃��[�h

//============================================
//���C���֐�
//============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�啶�������������ŁA�������Ȃ��Ȃ�ꍇ������̂ł������菑�����B�������̑O��_In_�������Winmain�̔j����������B
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,//�E�C���h�E�̃X�^�C��
		WindowProc,//�E�C���h�E�v���V�[�W��
		0,//�O�ɂ���
		0,//�O�ɂ���@
		hInstance,//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�^�X�N�o�[�̃A�C�R��
	LoadCursor(NULL,IDC_ARROW),//�}�E�X�J�[�\��
	(HBRUSH)(COLOR_WINDOW + 1),//�N���C�A���g�̈�̔w�i�F
	NULL,//���j���[�o�[
	CLASS_NAME,//�E�C���h�E�N���X�̖��O
	LoadIcon(NULL,IDI_APPLICATION)//�t�@�C���̃A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//��ʃT�C�Y�̍\����

	HWND hWnd;//�E�C���h�E�n���h���i���ʎq�j
	MSG msg;//���b�Z�[�W���i�[����ϐ�

	//�E�C���h�E�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,//�g���E�C���h�E�X�^�C��
		CLASS_NAME,//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),	//�E�C���h�E�̕�
		(rect.bottom - rect.top),//�E�C���h�E�̍���
		NULL,//�e�E�C���h�E�̃n���h��
		NULL,//���j���[�n���h��
		hInstance,//�C���X�^���X�n���h��
		NULL);//�E�C���h�E�쐬�f�[�^

	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime;//�Ō�ɏ�����������
	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������


	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;//�i���̌�̏��������Ȃ��j
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;//����������
	dwExecLastTime = timeGetTime();//���ݎ������擾�i�ۑ��j
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);//�E�C���h�E�̕\����Ԃ�ݒ�B
	UpdateWindow(hWnd);//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);//�E�C���h�E�v���V�[�W���փ��b�Z�[�W��n�o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b���v��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A

			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//�U�O���̂P�b�o��
				dwExecLastTime = dwCurrentTime;//�����J�n�̎���
				//���ݎ�����ۑ�

			//�X�V����
				Update();
				//�`�揈��
				Draw();
				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();
	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}
//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//�Ԃ�l���i�[
	switch (uMsg)
	{
	case WM_DESTROY://�E�C���h�E�j���̃��b�Z�[�W
		//WM_QUIT���b�Z�[�W�𑗂�B
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://�G�X�P�[�v�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);//����������hWnd�ɂ���ƁA���̃E�C���h�E���e�i�I�[�i�[�j�ɂȂ�A���̃��b�Z�[�W�{�b�N�X���������Ȃ�����A�ق��̏������ł��Ȃ��B
			if (nID == IDYES)
			{
				//�E�C���h�E��j������B
				DestroyWindow(hWnd);//
			}

			break;
		}
		break;
	case WM_CLOSE://����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�C���h�E��j������B
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;//�O��Ԃ��Ȃ��ƏI�����Ă��܂��B
		}

	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����Ԃ��B
}

//=================================================
//����������
//=================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^

	//DirectX3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	////���݂̃f�B�X�v���C���[�h���擾
	//if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	//{
	//	return E_FAIL;
	//}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��

	//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs��
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);


	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if(FAILED(InitKeyboard(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h���̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	srand((unsigned int)time(NULL));//�Q�[�����J�n�������Ԗ��ɗ����̎��ݒ�

	//�T�E���h�̏���������
	InitSound(hWnd);

	InitDebugProc();


	//���[�h�̐ݒ�
	SetMode(g_mode);
	return S_OK;
}

//================================================
//�I������
//================================================
void Uninit(void)
{
	//�T�E���h�̏I������
	UninitSound();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�f�o�b�O�\���̏I������
	UninitDebugProc();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	UninitKeyboard();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//====================================================
//�X�V����
//====================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�h�̍X�V����
	UpdateJoypad();

	//�f�o�b�O�\���̍X�V����
	UpdateDebugProc();
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UpdateTitle();
		break;
	case MODE_TUTORIAL://�`���[�g���A�����
		UpdateTutorial();
		break;
	case MODE_GAME://�Q�[�����
		UpdateGame();
		break;
	case MODE_RESULT://���U���g���
		UpdateResult();
		break;
	case MODE_RANKING://�����L���O���
		UpdateRanking();
		break;

	}
	
	//�t�F�[�h�̍X�V
	UpdateFade();

}

//=====================================================
//�`�揈��
//=====================================================
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		switch (g_mode)//���[�h�I��
		{
		case MODE_TITLE://�^�C�g�����
			DrawTitle();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();//�`���[�g���A�����
			break;
		case MODE_GAME://�Q�[�����
			DrawGame();
			break;
		case MODE_RESULT://���U���g���
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();
			break;

		}

		//FPS�̕\��
#ifdef _DEBUG
		DrawFPS();//�f�o�b�N�i�r���h�j�������\��
#endif 
		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�f�o�b�O�\���̕`�揈��
		DrawDebugProc();

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//======================================
//�f�o�C�X�̎擾
//======================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//============================================
//FPS�̕\���A�f�o�b�N�\��
//============================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_MOTIONMODE][256];
	int nCount;

	Camera* pCamera = GetCamera();

	//������ɑ��
	wsprintf(&aStr[0][0], "FPS:%d", g_nCountFPS);
	snprintf(&aStr[1][0],256,"\n���_���璍���_�̋��� :%.3f",pCamera->fLength);//�usnprintf�v�ŕ\�����s���ƁA�����������g����
	snprintf(&aStr[2][0], 256, "\n\n���_�̈ʒu :(X:%.3f Y:%.3f Z:%.3f", pCamera->PosV.x,pCamera->PosV.y,pCamera->PosV.z);//�usnprintf�v�ŕ\�����s���ƁA�����������g����
	snprintf(&aStr[3][0], 256, "\n\n\n�����_�̈ʒu :(X:%.3f Y:%.3f Z:%.3f", pCamera->PosR.x, pCamera->PosR.y, pCamera->PosR.z);//�usnprintf�v�ŕ\�����s���ƁA�����������g����
	wsprintf(&aStr[4][0], "\n\n\n\n���]�A���]���[�h�؂�ւ��FC");
	wsprintf(&aStr[5][0], "\n\n\n\n\n�J������]�FU,J");
	snprintf(&aStr[6][0], 256, "\n\n\n\n\n\n�J�����̌���:%.3f",pCamera->rot.y);//�J�����̌���
	wsprintf(&aStr[7][0], "\n\n\n\n\n\n\n���f���̔z�u:ENTER");
	wsprintf(&aStr[8][0], "\n\n\n\n\n\n\n\n�ݒu�������f���̏���ۑ�����F�G�f�B�b�g���[�h����F10");
	wsprintf(&aStr[9][0], "\n\n\n\n\n\n\n\n\n�J�����㏸�F��AO�A���AL");
	wsprintf(&aStr[10][0], "\n\n\n\n\n\n\n\n\n\n�J�����Y�[���C���FZ�A�J�����Y�[���A�E�g�FX");
	wsprintf(&aStr[11][0], "\n\n\n\n\n\n\n\n\n\n\n�ړ��^�C�v�ύX�FF2");
	wsprintf(&aStr[12][0], "\n\n\n\n\n\n\n\n\n\n\n\n�z�u�^�C�v�ύX�FF3");
	wsprintf(&aStr[13][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n�U���{�^���FM");
	wsprintf(&aStr[14][0], "\n\n\n\n\n\n\n\n\n\n\n\n\n\n�X�L���ύX�FN");




	

	//wsprintf(&aStr[2][0], "\n�x�_�̈ʒu X�F%f",pCamera->PosV.x);
	//wsprintf(&aStr[3][0], "\n\n\n��]���˂�F3�L�[");
	//wsprintf(&aStr[4][0], "\n\n\n\n�ϓ���]���˂�F4�L�[");
	//wsprintf(&aStr[5][0], "\n\n\n\n\n�t�ϓ���]���˂�F5�L�[");
	//wsprintf(&aStr[6][0], "\n\n\n\n\n\n�������������������z�[�~���O��H�L�[�I����������������");
	//wsprintf(&aStr[7][0], "\n\n\n\n\n\n\n�����^�Tway�e��F7�L�[�i�p�x�����u���L�[�A���L�[�v)");
	//wsprintf(&aStr[8][0], "\n\n\n\n\n\n\n\n�X�L���̎g�p�́uJ�v�L�[");
	//wsprintf(&aStr[9][0], "\n\n\n\n\n\n\n\n\n�X�L���̑I���́uI�v�L�[�A�uK�v�L�[");
	//wsprintf(&aStr[10][0], "\n\n\n\n\n\n\n\n\n\n�G���j��%d",pDefeat->DefeatEnemyCount);

	//�e�L�X�g�̕`��
	for (nCount = 0; nCount < MAX_MOTIONMODE; nCount++)
	{
	/*	switch (nCount)
		{
		case 0:
			wsprintf(&aStr[nCount][0], "FPS:%d", g_nCountFPS);
			break;
			
		case 1:
			wsprintf(&aStr[nCount][0], "\n���_�ƒ����_�̋��� :%f", pCamera->fLength);
			break;
		}*/

		g_pFont->DrawText(NULL, &aStr[nCount][0], -1, &rect, DT_LEFT,
			D3DCOLOR_RGBA(0, 0, 0, 255));
	}
}

//=======================================
//���[�h�ύX���s���֐�
//=======================================
void SetMode(MODE mode)
{
	//���݂̉�ʁi���[�h�j�̏I������
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();//�`���[�g���A�����
		break;
	case MODE_GAME://�Q�[�����
		UninitGame();
		break;
	case MODE_RESULT://���U���g���
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;

	}

	//�t�F�[�h�̏I��
	UninitFade();

//�V������ʁi���[�h�j�̏���������
	switch (mode)
	{
	case MODE_TITLE://�^�C�g�����
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();//�`���[�g���A�����
		break;
	case MODE_GAME://�Q�[�����
		InitGame();
		break;
	case MODE_RESULT://���U���g���
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();
		break;
	}

	//�t�F�[�h�̏�����
	InitFade();

	//�V������ʁi���[�h�j�̏���������

	g_mode = mode;//���݂̉�ʁi���[�h�j��؂�ւ���
}

//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}


