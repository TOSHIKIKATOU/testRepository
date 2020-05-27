// AsoRockman
// 
// stage.cpp
//
// 1419.11.05
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "main.h"
#include "stage.h"


// 変数
//--------------------------------------------------------------------------------------------
int chipImage[13];
XY mapPos;
int haikeiimage;
XY haikeiPos;
int haikeiturnimage;
XY haikeiturnPos;
int haikeispeed;
int haikeicnt;


int map[MAP_Y][MAP_X] = {
{ 14, 14, 14, 14, 14, 14, 14, 14,	14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20 },
};


// ｽﾃｰｼﾞ情報の初期化
bool StageSystemInit(void)
{
	int ret;

	ret = LoadDivGraph("image/障害物.png"
		, 14, 5, 4
		, CHIP_SIZE_X, CHIP_SIZE_X
		, chipImage);
	if (ret == -1)
	{
		AST();
		return false;
	}

	haikeiimage = LoadGraph("image/haikeiii.png");
	haikeiturnimage = LoadGraph("image/haikeiturn.png");

	haikeispeed = 1;
	haikeicnt = 0;

	return true;
}

// ｽﾃｰｼﾞ情報のｹﾞｰﾑ初期化
void StageGameInit(void)
{

	// 変数の初期化
	mapPos.x = 0;
	mapPos.y = 0;
	haikeiPos = { 0, 0};
	haikeiturnPos = { SCREEN_SIZE_X, 0 };
	haikeispeed = 1;
	haikeicnt = 0;

}

// ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する。
XY Pos2Index(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;//posのx座標を変換;
	tmp.y = pos.y / CHIP_SIZE_Y;//posのy座標を変換;

								// 変換した値を返す
	return tmp;
}

// ﾏｯﾌﾟ配列座標系からﾋﾟｸｾﾙ座標系(左上)に変換する。
XY Index2Pos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;//posのx座標を変換;
	tmp.y = index.y * CHIP_SIZE_Y;//posのy座標を変換;

								// 変換した値を返す
	return tmp;
}

// 指定した座標が通過可能かを返す　true:通過できる
bool IsPass(XY pos)
{
	XY indexPos;

	indexPos = Pos2Index(pos);


	switch (map[indexPos.y][indexPos.x])
	{
	/*case 8:
	case 9:
	case 12:*/
	case 14:
		// 通れない
		return false;
		break;
	default:
		break;
	}
	return true;
	
}

// ｽﾃｰｼﾞの描画
void StageGameDraw(void)
{
	haikeicnt++;

	if (haikeicnt % 1800 == 0)
	{
		haikeispeed++;
	}
		
	
	

	// 背景画像の描画
	DrawGraph(haikeiPos.x
		, 0
		, haikeiimage, true);

	// 反転した背景画像の描画
	DrawGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);

	haikeiturnPos.x -= haikeispeed;		//  反転した背景のスクロール

	haikeiPos.x -= haikeispeed;			// 背景のスクロール

	if (haikeiPos.x <= -SCREEN_SIZE_X)
	{
		haikeiPos.x = haikeiturnPos.x + SCREEN_SIZE_X;
	}

	if (haikeiturnPos.x <= -SCREEN_SIZE_X)
	{
		haikeiturnPos.x = haikeiPos.x + SCREEN_SIZE_X;
	}

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + -mapPos.x
				, y * CHIP_SIZE_Y + -mapPos.y
				, chipImage[map[y][x]], true);
		}
	}

}