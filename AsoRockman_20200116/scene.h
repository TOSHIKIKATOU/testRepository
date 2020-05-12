// AsoRockman
// 
// scene.h
//
// 2019.09.25
//
// 1916009_Kato Toshiki

//#pragma once

// extern宣言
//-------------------------------------------------------------------
// 画面切り替えｴﾌｪｸﾄ
extern int fadeCnt;						// ﾌｪｰﾄﾞのｶｳﾝﾄ
extern bool fadeIn;						// ﾌｪｰﾄﾞｲﾝ
extern bool fadeOut;					// ﾌｪｰﾄﾞｱｳﾄ
// 一時停止ｴﾌｪｸﾄ
extern bool pauseFlag;					// ﾎﾟｰｽﾞのFlag


// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//------------------------------------------------------------------
void EffectInit(void);					// ｴﾌｪｸﾄの初期化
bool FadeInScreen(int fadeStep);		// ﾌｪｰﾄﾞｲﾝ処理
bool FadeOutScreen(int fadeStep);		// ﾌｪｰﾄﾞｱｳﾄ処理