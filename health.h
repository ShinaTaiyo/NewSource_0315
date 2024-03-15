//========================================================
//
//�P�O���X���F�A�N�V������UI�쐬[health.h]
//Author:ShinaTaiyo
//
//=========================================================
#ifndef _HEALTH_H_
#define _HEALTH_H_

#include "main.h"

//�v���g�^�C�v�錾
void InitHealth(void);
void UninitHealth(void);
void UpdateHealth(void);
void DrawHealth(void);
void SetHealth(int nDamage);
void SetHealing(int nHeal);
void DamageHealth(int nValue);
int GetHealth(void);


#endif
