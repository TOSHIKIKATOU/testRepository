// AsoRockman
// 
// scene.cpp
//
// 2019.09.25
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "scene.h"

// 変数
//--------------------------------------------------------------------------------------------
// 画面切り替えｴﾌｪｸﾄ
int fadeCnt;		// ﾌｪｰﾄﾞのｶｳﾝﾄ
bool fadeIn;		// ﾌｪｰﾄﾞｲﾝ
bool fadeOut;		// ﾌｪｰﾄﾞｱｳﾄ
// 一時停止ｴﾌｪｸﾄ
bool pauseFlag;		// ﾎﾟｰｽﾞのFlag

// ｴﾌｪｸﾄの初期化
void EffectInit(void)
{
	fadeCnt = 0;
	fadeIn = true;
	fadeOut = false;
	pauseFlag = false;
}

// ﾌｪｰﾄﾞｲﾝ処理
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

// ﾌｪｰﾄﾞｱｳﾄ処理
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