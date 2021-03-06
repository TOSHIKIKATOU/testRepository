// AsoRockman
// 
// shot2.cpp
//
// 2019.12.13
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot2.h"
#include "shot.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// 変数
//-------------------------------------------------------------------


CHARACTER shot2[SHOT_MAX];
int shot2Image;
XY Shot2PosHit[SHOT_MAX];



// ｼｮｯﾄ情報の初期化
void Shot2SystemInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ｷｬﾗｸﾀの種類
		shot2[sh].moveDir = DIR_DOWN;					// ｷｬﾗｸﾀの向き
		shot2[sh].pos.x = 100;								// ｷｬﾗｸﾀの地図上のX座標
		shot2[sh].pos.y = 100;								// ｷｬﾗｸﾀの地図上のY座標
		shot2[sh].size.x = 16;							// ｷｬﾗｸﾀが画像のｻｲｽﾞ
		shot2[sh].size.y = 16;							// ｷｬﾗｸﾀが画像のｻｲｽﾞ
		shot2[sh].sizeOffset.x = shot2[sh].size.x / 2;	// ｷｬﾗｸﾀのｵﾌｾｯﾄ
		shot2[sh].sizeOffset.y = shot2[sh].size.y / 2;	// ｷｬﾗｸﾀのｵﾌｾｯﾄ
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;							// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
		shot2[sh].life = 0;					// ｷｬﾗｸﾀの体力最大値
		shot2[sh].lifeMax = SHOT2_LIFE_MAX;
		shot2[sh].animCnt = 0;							// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
		Shot2PosHit[sh] = shot2[sh].sizeOffset;
		shot2[sh].imgLockCnt = 0;


	}

	shot2Image = LoadGraph("image/shot2.png");


}



// 弾を生成する
void CreateShot2(XY pPos, DIR pDir)
{
	// 弾の数分撃っていない弾がないかをﾁｪｯｸし
	// 撃っていない弾があれば一発弾を発射する。

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].imgLockCnt++;

		// 撃っていない弾を探す。
		if (shot2[sh].life <= 0)
		{
			// 撃っていない弾があったので発射。
			// 弾の場所
			shot2[sh].pos.x = pPos.x;
			shot2[sh].pos.y = pPos.y + 6;
			// 弾の進むべき方向
			shot2[sh].moveDir = pDir;
			// 弾を撃ったことにする

			shot2[sh].life = shot2[sh].lifeMax;

			break;
		}


	}
}

// ｼｮｯﾄ情報のｹﾞｰﾑ初期化
void Shot2GameInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].visible = false;
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;						// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
		shot2[sh].life = 0;								// ｷｬﾗｸﾀの体力最大値
		shot2[sh].animCnt = 0;							// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	}
}

// ｼｮｯﾄの操作
void Shot2Control(void)
{

	// 弾を動かす処理
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{

		shot2[sh].animCnt++;
		// 撃っている弾を探す
		if (shot2[sh].life > 0)
		{
			switch (shot2[sh].moveDir)
			{
			case DIR_RIGHT:
				// 弾を移動させる。
				shot2[sh].pos.x += shot2[sh].moveSpeed;
				break;

			case DIR_LEFT:
				// 弾を移動させる。
				shot2[sh].pos.x -= shot2[sh].moveSpeed;
				break;
			}

			// 寿命を減らす

			shot2[sh].life--;


			if (!IsPass(shot2[sh].pos))
			{
				shot2[sh].life = 0;
				SetBlockEffect(shot2[sh].pos, EFFECT_C_MAGENTA);
			}
		}

	}


}

// ｼｮｯﾄの描画
void Shot2GameDraw(void)
{


	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{
			DrawGraph(shot2[sh].pos.x - shot2[sh].sizeOffset.x + -mapPos.x
				, shot2[sh].pos.y - shot2[sh].sizeOffset.y + -mapPos.y
				, shot2Image
				, true);
		}
	}



}



// 弾を消滅させる
void DeleteShot2(void)
{
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{


			if (Player1HitCheck(shot2[sh].pos, shot2[sh].size)) shot2[sh].life = 0;

			if (Player1ShotHitCheck(shot2[sh].pos, shot2[sh].size))
			{
				SetTobichiriEffect(shot2[sh].pos, EFFECT_C_CYAN);

				shot2[sh].life = 0;
			}



		}
	}



}


