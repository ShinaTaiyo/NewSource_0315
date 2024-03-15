//========================================================
//
//�X���P�T���F�W���C�p�b�h�̃g���K�[����������[input.cpp]
//Author:ShinaTaiyo
//
//=========================================================


#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X�i�L�[�{�[�h�j�̃|�C���^

BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//�L�[�{�[�h�̃g���K�[���i�ꔭ���e�����悤�ɂ���j

XINPUT_STATE g_joykeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joykeyStateTrigger;//�W���C�p�b�h�̃g���K�[���
//�L�[�{�[�h�̏���������
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput,
		NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,
		&g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=================================
//�W���C�p�b�h�̏���������
//=================================
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	return S_OK;
}

//=================================
//�L�[�{�[�h�̏I������
//=================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̔j��

	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����
		g_pDevKeyboard->Release();
		g_pDevKeyboard=NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//===============================
//�W���C�p�b�h�̏I������
//===============================
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//===================================
//�L�[�{�[�h�̍X�V����
//===================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState
	(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{

			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
		
	}
	else
	{
		g_pDevKeyboard->Acquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//================================
//�W���C�p�b�h�̍X�V����
//================================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joykeyState.Gamepad.wButtons;
		g_joykeyStateTrigger.Gamepad.wButtons = ~OldButton & Button;//�g���K�[����
		g_joykeyState = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}
}

//=======================================
//�L�[�{�[�h�̃v���X�����擾
//=======================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) != 0;
	//return ((g_aKeyState[nKey] & 0x80 != 0) ? true : false);
}

//===========================================
//�W���C�p�b�h�̃v���X�����擾
//===========================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key)) != 0;
}

//======================================
//�L�[�{�[�h�̃g���K�[�����擾
//======================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) != 0;
	//return ((g_aKeyStateTrigger[nKey] & 0x80 != 0) ? true : false);
}
//======================================
//�W���C�p�b�h�̃g���K�[�����擾
//======================================
bool GetJoyPadTrigger(JOYKEY key)
{
	return (g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) != 0;
}