// AsoRockman
// 
// shot2.h
//
// 2019.12.13
//
// 1916009_Kato Toshiki

//#pragma once

// 定数
//------------------------------------------------------------------
#define SHOT_MAX 50
#define SHOT_DEF_SPEED  12
#define SHOT_LIFE_MAX 40

#define SHOT2_MAX 50
#define SHOT2_DEF_SPEED  12
#define SHOT2_LIFE_MAX 40

// extern宣言
//-------------------------------------------------------------------
// extern CHARACTER shot[SHOT_MAX];

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//---------------------------------------------------------------------

void Shot2SystemInit(void);								// ｼｮｯﾄ情報の初期化
void Shot2GameInit(void);								// ｼｮｯﾄ情報のｹﾞｰﾑ初期化
void Shot2Control(void);								// ｼｮｯﾄの操作
void Shot2GameDraw(void);								// ｼｮｯﾄの描画
void CreateShot2(XY pPos, DIR pDir);					// 弾を生成する
void DeleteShot2(void);									// 弾を消滅させる

bool Player2ShotHitCheck(XY sPos, XY sSize);			// 1P弾と2P弾との当たり判定 (true:1P弾が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大きさ