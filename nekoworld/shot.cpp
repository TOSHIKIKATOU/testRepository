// AsoRockman
// 
// shot.cpp
//
// 2019.11.21
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot.h"
#include "shot2.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// 変数
//-------------------------------------------------------------------
CHARACTER shot[SHOT_MAX];
int shotImage;
XY ShotPosHit[SHOT_MAX];


// ｼｮｯﾄ情報の初期化
void ShotSystemInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ｷｬﾗｸﾀの種類
		shot[sh].moveDir = DIR_DOWN;					// ｷｬﾗｸﾀの向き
		shot[sh].pos.x = 150;								// ｷｬﾗｸﾀの地図上のX座標
		shot[sh].pos.y = 150;								// ｷｬﾗｸﾀの地図上のY座標
		shot[sh].size.x = 16;							// ｷｬﾗｸﾀが画像のｻｲｽﾞ
		shot[sh].size.y = 16;							// ｷｬﾗｸﾀが画像のｻｲｽﾞ
		shot[sh].sizeOffset.x = shot[sh].size.x / 2;	// ｷｬﾗｸﾀのｵﾌｾｯﾄ
		shot[sh].sizeOffset.y = shot[sh].size.y / 2;	// ｷｬﾗｸﾀのｵﾌｾｯﾄ
		shot[sh].moveSpeed = SHOT_DEF_SPEED;							// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
		shot[sh].life = 0;					// ｷｬﾗｸﾀの体力最大値
		shot[sh].lifeMax = SHOT_LIFE_MAX;
		shot[sh].animCnt = 0;							// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
		ShotPosHit[sh] = shot[sh].sizeOffset;
		shot[sh].imgLockCnt = 0;

	}

	

	shotImage = LoadGraph("image/shot1.png");


}

// 弾を生成する
void CreateShot(XY pPos, DIR pDir)
{
	// 弾の数分撃っていない弾がないかをﾁｪｯｸし
	// 撃っていない弾があれば一発弾を発射する。
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].imgLockCnt++;

		// 撃っていない弾を探す。
		if (shot[sh].life <= 0)
		{
			// 撃っていない弾があったので発射。
			// 弾の場所
			shot[sh].pos.x = pPos.x;
			shot[sh].pos.y = pPos.y + 6;
			// 弾の進むべき方向
			shot[sh].moveDir = pDir;
			// 弾を撃ったことにする

			shot[sh].life = shot[sh].lifeMax;

			break;
		}

	}


}

// ｼｮｯﾄ情報のｹﾞｰﾑ初期化
void ShotGameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].visible = false;
		shot[sh].moveSpeed = SHOT_DEF_SPEED;						// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
		shot[sh].life = 0;								// ｷｬﾗｸﾀの体力最大値
		shot[sh].animCnt = 0;							// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ

	}


}

// ｼｮｯﾄの操作
void ShotControl(void)
{
	

	// 弾を動かす処理
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		XY shotPosCopy = shot[sh].pos;
		XY shotPosOffset = shotPosCopy;

		shot[sh].animCnt++;
		// 撃っている弾を探す
		if (shot[sh].life > 0)
		{
			switch (shot[sh].moveDir)
			{
			case DIR_RIGHT:
				// 弾を移動させる。
				shotPosCopy.x += shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;

			case DIR_LEFT:
				// 弾を移動させる。
				shotPosCopy.x -= shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;
			}

			// 寿命を減らす
			shot[sh].life--;


			if (!IsPass(shotPosOffset))
			{
				SetBlockEffect(shot[sh].pos, EFFECT_C_YELLOW);
			}
		}

	}

	


}

// ｼｮｯﾄの描画
void ShotGameDraw(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			DrawGraph(shot[sh].pos.x - shot[sh].sizeOffset.x + -mapPos.x
				, shot[sh].pos.y - shot[sh].sizeOffset.y + -mapPos.y
				, shotImage
				, true);



		}


	}
}

// 弾を消滅させる
void DeleteShot(void)
{
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			if (Player2HitCheck(shot[sh].pos, shot[sh].size))shot[sh].life = 0;

			/*if (Player2ShotHitCheck(shot[sh].pos, shot[sh].size))
			{
				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				
			}*/
		}

	}



}

// 1P弾と2P弾との当たり判定 (true:1P弾が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大きさ
bool Player1ShotHitCheck(XY sPos, XY sSize)
{
	// 全ての敵に当たり判定を実施する
	
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{

		if (shot[sh].life > 0)
		{
			// 当たりは判定方法は自由 (矩形でも良いし、点との距離でもよい。)
			if (((shot[sh].pos.x - shot[sh].size.x / 2) < (sPos.x + sSize.x / 2))
				&& ((shot[sh].pos.x + shot[sh].size.x / 2) > (sPos.x - sSize.x / 2))
				&& ((shot[sh].pos.y - shot[sh].size.y / 2) < (sPos.y + sSize.y / 2))
				&& ((shot[sh].pos.y + shot[sh].size.y / 2) > (sPos.y - sSize.y / 2)))
			{
				// 当たった時

				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				shot[sh].life = 0;

				return true;
			}
		}
		

	}


	return false;

}
