// AsoRockman
// 
// stage.h
//
// 2019.11.05
//
// 1916009_Kato Toshiki

//#pragma once

extern XY mapPos;

// 定数
//------------------------------------------------------------------
#define MAP_X	64
#define MAP_Y	15
#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32
#define SCROLL_X_MIN 200
#define SCROLL_X_MAX 600

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//------------------------------------------------------------------
bool StageSystemInit(void);			// ｽﾃｰｼﾞ情報の初期化
void StageGameInit(void);			// ｽﾃｰｼﾞ情報のｹﾞｰﾑ初期化
void StageGameDraw(void);			// ｽﾃｰｼﾞの描画

XY Pos2Index(XY pos);				// ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する。
XY Index2Pos(XY index);				// ﾏｯﾌﾟ配列座標系からﾋﾟｸｾﾙ座標系に変換する。
bool IsPass(XY pos);				// 指定した座標が通過可能かを返す　true:通過できる
