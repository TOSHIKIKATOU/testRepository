// AsoRockman
// 
// scene.cpp
//
// 2019.09.25
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "scene.h"

// �ϐ�
//--------------------------------------------------------------------------------------------
// ��ʐ؂�ւ��̪��
int fadeCnt;		// ̪��ނ̶���
bool fadeIn;		// ̪��޲�
bool fadeOut;		// ̪��ޱ��
// �ꎞ��~�̪��
bool pauseFlag;		// �߰�ނ�Flag

// �̪�Ă̏�����
void EffectInit(void)
{
	fadeCnt = 0;
	fadeIn = true;
	fadeOut = false;
	pauseFlag = false;
}

// ̪��޲ݏ���
bool FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeCnt = 255;
		fadeIn = false;
		return false;
	}
}

// ̪��ޱ�ď���
bool FadeOutScreen(int fadeStep)
{
	fadeCnt -= fadeStep;
	if (fadeCnt >= 0)
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeCnt = 0;
		fadeOut = false;
		return false;
	}
}