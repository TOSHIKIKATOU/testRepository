// AsoRockman
// 
// scene.h
//
// 2019.09.25
//
// 1916009_Kato Toshiki

//#pragma once

// extern�錾
//-------------------------------------------------------------------
// ��ʐ؂�ւ��̪��
extern int fadeCnt;						// ̪��ނ̶���
extern bool fadeIn;						// ̪��޲�
extern bool fadeOut;					// ̪��ޱ��
// �ꎞ��~�̪��
extern bool pauseFlag;					// �߰�ނ�Flag


// �������ߐ錾
//------------------------------------------------------------------
void EffectInit(void);					// �̪�Ă̏�����
bool FadeInScreen(int fadeStep);		// ̪��޲ݏ���
bool FadeOutScreen(int fadeStep);		// ̪��ޱ�ď���