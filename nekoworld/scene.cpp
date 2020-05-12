// AsoRockman
// 
// scene.cpp
//
// 2019.09.25
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "scene.h"

// •Ï”
//--------------------------------------------------------------------------------------------
// ‰æ–ÊØ‚è‘Ö‚¦´Ìª¸Ä
int fadeCnt;		// Ìª°ÄŞ‚Ì¶³İÄ
bool fadeIn;		// Ìª°ÄŞ²İ
bool fadeOut;		// Ìª°ÄŞ±³Ä
// ˆê’â~´Ìª¸Ä
bool pauseFlag;		// Îß°½Ş‚ÌFlag

// ´Ìª¸Ä‚Ì‰Šú‰»
void EffectInit(void)
{
	fadeCnt = 0;
	fadeIn = true;
	fadeOut = false;
	pauseFlag = false;
}

// Ìª°ÄŞ²İˆ—
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

// Ìª°ÄŞ±³Äˆ—
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