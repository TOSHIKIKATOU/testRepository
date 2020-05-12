// AsoRockman
// 
// keycheck.cpp
//
// 2019.09.24
//
// 1916009_Kato Toshiki


#include "DxLib.h"
#include "main.h"
#include "keycheck.h"


// 変数
//--------------------------------------------------------------------------------------------
bool keyOld[KEY_ID_MAX];				// 前の入力
bool keyNew[KEY_ID_MAX];				// 現在の入力状態
bool keyDownTrigger[KEY_ID_MAX];		// ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
bool keyUpTrigger[KEY_ID_MAX];			// アップ時のﾄﾘｶﾞｰ

// ｷｰの初期化
void KeyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}

// ｷｰのﾁｪｯｸ
void KeyCheck(void)
{

	// Oldの準備
	for (int keyID = KEY_ID_SPACE; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}
	
	// 現在の状態を取得する
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	keyNew[KEY_ID_P1UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_ID_P2UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_ID_P1RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_ID_P2RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_ID_P1LEFT] = CheckHitKey(KEY_INPUT_A);
	keyNew[KEY_ID_P2LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_ID_P1SHOT] = CheckHitKey(KEY_INPUT_LCONTROL);
	keyNew[KEY_ID_P2SHOT] = CheckHitKey(KEY_INPUT_RCONTROL);
	
	
	
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
		// ﾀﾞｳﾝﾄﾘｶﾞｰ
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}
		// ｱｯﾌﾟﾄﾘｶﾞｰ
		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}

