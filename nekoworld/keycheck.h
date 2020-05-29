// AsoRockman
// 
// keycheck.h
//
// 2019.09.24
//
// 1916009_Kato Toshiki

//#pragma once


// 列挙型の定義
//------------------------------------------------------------------
// 入力情報用
enum KEY_ID
{
	KEY_ID_SPACE,			// ｽﾍﾟｰｽｷｰ
	KEY_ID_PAUSE,
	KEY_ID_P1UP,
	KEY_ID_P2UP,
	KEY_ID_P1RIGHT,
	KEY_ID_P2RIGHT,
	KEY_ID_DOWN,
	KEY_ID_P1LEFT,
	KEY_ID_P2LEFT,
	KEY_ID_P1SHOT,
	KEY_ID_P2SHOT,
	KEY_ID_ENTER,
	KEY_ID_MAX
};

// extern宣言
//-------------------------------------------------------------------
extern bool keyOld[KEY_ID_MAX];					// 前の入力
extern bool keyNew[KEY_ID_MAX];					// 現在の入力状態
extern bool keyDownTrigger[KEY_ID_MAX];			// ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
extern bool keyUpTrigger[KEY_ID_MAX];			// アップ時のﾄﾘｶﾞｰ

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//-------------------------------------------------------------------
void KeyInit(void);								// ｷｰの初期化
void KeyCheck(void);							// ｷｰのﾁｪｯｸ
