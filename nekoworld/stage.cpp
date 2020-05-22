// AsoRockman
// 
// stage.cpp
//
// 2019.11.05
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

int map[MAP_Y][MAP_X] = {
{ 12, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 8, 8, 8, 9, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 8, 8, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 8, 8, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 8, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 8, 8, 8, 8, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 8, 0, 0, 0, 0,  0, 8, 0, 0, 0, 0, 0,12 },

{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 8, 8,  9, 0, 0, 0, 0, 0, 0, 0,  0, 8, 8, 9, 0, 0, 0, 0,  0, 0, 0, 8, 0, 0, 0, 0,  0, 8, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,12 },
{ 12, 0, 0, 0, 0, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 8, 9, 0, 0, 0, 0, 0,  0, 8, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  8, 0, 0, 0, 0, 0, 8, 0,  0, 0, 0, 0, 8, 0, 0,12 },
{ 12, 0, 0, 0, 0, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 8, 9, 0, 0, 0, 0, 0,  0, 8, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,  8, 0, 0, 0, 0, 0, 8, 0,  0, 0, 0, 0, 8, 0, 0,12 },
{ 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12 },

};


// ｽﾃｰｼﾞ情報の初期化
bool StageSystemInit(void)
{
	int ret;

	ret = LoadDivGraph("image/bg.png"
		, 13, 13, 1
		, CHIP_SIZE_X, CHIP_SIZE_X
		, chipImage);
	if (ret == -1)
	{
		AST();
		return false;
	}

	haikeiimage = LoadGraph("image/haikeiii.png");

	return true;
}

// ｽﾃｰｼﾞ情報のｹﾞｰﾑ初期化
void StageGameInit(void)
{

	// 変数の初期化
	mapPos.x = 0;
	mapPos.y = 0;

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
	case 8:
	case 9:
	case 12:
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
	
	
	

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + -mapPos.x
				, y * CHIP_SIZE_Y + -mapPos.y
				, chipImage[map[y][x]], true);
		}
	}

	DrawGraph(0
		, 0
		, haikeiimage, true);

}