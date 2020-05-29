#include"DxLib.h"
#include"main.h"
#include"stage.h"
#include"player.h"
#include "item.h"

//int itemImage[3];			//アイテム画像の格納
//CHARACTER item;
//XY map2Pos;
//int map2[MAP_Y][MAP_X] = 
//{
//{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  1, 1, 1, 1, 1, 1, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 2, 4, 4, 4, 2, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 1, 1, 1, 1, 1, 1, 1,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 1, 1, 1, 1, 1, 1, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4, 4, 4, 4, 4,4 },
//{ 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4 },
//};
//bool ItemSystemInit(void)
//{
//	/*for (int i = 0; i < ITEM_MAX; i++)
//	{
//		item[i].pos.x = 200;
//		item[i].pos.y = 200;
//		item[i].size.x = 32;
//		item[i].size.y = 32;
//		item[i].lifeMax = 30;
//		item[i].life = 0;
//		item[i].aniCnt = 0;
//	}
//	itemImage = LoadGraph("image/アイテム.png");
//	if (itemImage == -1)
//	{
//		AST();
//		return;
//	}*/
//
//	item.lifeMax = 30;
//	item.life = 0;
//	item.aniCnt = 0;
//	int ret;
//
//	ret = LoadDivGraph("image/アイテム.png", 3, 3, 1, ITEM_SIZE_X, ITEM_SIZE_Y, itemImage);
//	if (ret == -1)
//	{
//		AST();
//		return false;
//	}
//	return true;
//}
////アイテムの初期化ーーーーーーーーーーーーーーーーーーーーーー
//void ItemGameInit(void)
//{
//	item.life = item.lifeMax;
//	map2Pos.x = 0;
//	map2Pos.y = 0;
//}
//
//
//// ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する。
//XY Pos22Index(XY pos)
//{
//	XY tmp;
//
//	tmp.x = pos.x / ITEM_SIZE_X;//posのx座標を変換;
//	tmp.y = pos.y / ITEM_SIZE_Y;//posのy座標を変換;
//
//	// 変換した値を返す
//	return tmp;
//}
//
//// ﾏｯﾌﾟ配列座標系からﾋﾟｸｾﾙ座標系(左上)に変換する。
//XY Index22Pos(XY index)
//{
//
//	XY tmp;
//
//	tmp.x = index.x * ITEM_SIZE_X;//posのx座標を変換;
//	tmp.y = index.y * ITEM_SIZE_Y;//posのy座標を変換;
//
//								// 変換した値を返す
//	return tmp;
//}
//
//// 指定した座標が通過可能かを返す　true:通過できる
//bool Is2Pass(XY pos)
//{
//	XY indexPos;
//
//	indexPos = Pos22Index(pos);
//
//
//	switch (map2[indexPos.y][indexPos.x])
//	{
//
//		// 通れない
//	case 1:
//	case 0:
//	case 2:
//		return false;
//		break;
//	default:
//		break;
//	}
//	return true;
//
//}
////アイテムを生成ーーーーーーーーーーーーーーーーーーーーーー
//void CreateItem(XY ePos)
//{
//		if (item.life <= 0)
//		{
//			item.life = item.lifeMax;
//		}
//}
////アイテム操作ーーーーーーーーーーーーーーーーーーーーーー
//void ItemControl(void)
//{
//	/*for (int i = 0; i < ITEM_MAX; i++)
//	{
//		if (item[i].life < 0)
//		{
//			if (ItemHitCheck(item[i].pos, item[i].size))
//			{
//				item[i].life = 1;
//				ItemGameInit();
//			}
//		}
//	}*/
//}
////アイテム消失ーーーーーーーーーーーーーーーーーーーーーー
//void Deleteitem(void)
//{
//	if (item.life > 0)
//	{
//			item.life = 0;
//			ItemGameInit();
//	}
//}
//
////アイテムの描画ーーーーーーーーーーーーーーーーーーーーーー
//void ItemDraw(void)
//{
//	/*for (int i = 0; i < ITEM_MAX; i++)
//	{
//		item[i].aniCnt++;
//		if (item[i].life > 1)
//		{
//			DrawGraph(item[i].pos.x - 16 + mapPos.x
//				, item[i].pos.y - 16 + mapPos.y
//				, itemImage[3], true);
//		}
//	}*/
//	if(item.life > 0)
//	{
//		for (int y = 0; y < MAP_Y; y++)
//		{
//			for (int x = 0; x < MAP_X; x++)
//			{
//				DrawGraph(x * ITEM_SIZE_X + -mapPos.x
//					, y * ITEM_SIZE_Y + -mapPos.y
//					, itemImage[map2[y][x]], true);
//			}
//		}
//	}
//}

CHARACTER itemmaster[ITEM_TYPE_MAX];
CHARACTER sknmaster[SKANA_TYPE_MAX];
int itemImage[ITEM_TYPE_MAX];					//アイテム画像の格納
int sknImage[SKANA_TYPE_MAX];
CHARACTER item[ITEM_MAX];
CHARACTER skn[SKANA_MAX];
int mutekiCnt;

bool ItemSystemInit(void)
{
	sknmaster[SKANA_TYPE_A].chartype       = SKANA_TYPE_A;		//敵の種類	スライム
	sknmaster[SKANA_TYPE_A].pos.x          = 100;						//スライムのX座標
	sknmaster[SKANA_TYPE_A].pos.y          = 400;						//スライムのY座標
	sknmaster[SKANA_TYPE_A].size.x         = 30;						//スライムの横画像サイズ
	sknmaster[SKANA_TYPE_A].size.y         = 30;						//スライムの縦画像サイズ
	sknmaster[SKANA_TYPE_A].sizeOffset.x   = sknmaster[SKANA_TYPE_A].size.x / 2;
	sknmaster[SKANA_TYPE_A].sizeOffset.y   = sknmaster[SKANA_TYPE_A].size.y / 2;
	sknmaster[SKANA_TYPE_A].lifeMax        = 3;					//スライムの最大ライフ
	sknmaster[SKANA_TYPE_A].life           = sknmaster[SKANA_TYPE_A].lifeMax;
	sknmaster[SKANA_TYPE_A].point          = 10;
	sknmaster[SKANA_TYPE_A].ipos           = { 62,87 };

	sknmaster[SKANA_TYPE_B].chartype = SKANA_TYPE_B;		//敵の種類	スライム
	sknmaster[SKANA_TYPE_B].pos.x = 100;						//スライムのX座標
	sknmaster[SKANA_TYPE_B].pos.y = 400;						//スライムのY座標
	sknmaster[SKANA_TYPE_B].size.x = 30;						//スライムの横画像サイズ
	sknmaster[SKANA_TYPE_B].size.y = 30;						//スライムの縦画像サイズ
	sknmaster[SKANA_TYPE_B].sizeOffset.x = sknmaster[SKANA_TYPE_B].size.x / 2;
	sknmaster[SKANA_TYPE_B].sizeOffset.y = sknmaster[SKANA_TYPE_B].size.y / 2;
	sknmaster[SKANA_TYPE_B].lifeMax = 3;					//スライムの最大ライフ
	sknmaster[SKANA_TYPE_B].life = sknmaster[SKANA_TYPE_B].lifeMax;
	sknmaster[SKANA_TYPE_B].point = 50;
	sknmaster[SKANA_TYPE_B].ipos = { 62,87 };

	sknmaster[SKANA_TYPE_C].chartype = SKANA_TYPE_C;		//敵の種類	スライム
	sknmaster[SKANA_TYPE_C].pos.x = 100;						//スライムのX座標
	sknmaster[SKANA_TYPE_C].pos.y = 400;						//スライムのY座標
	sknmaster[SKANA_TYPE_C].size.x = 30;						//スライムの横画像サイズ
	sknmaster[SKANA_TYPE_C].size.y = 30;						//スライムの縦画像サイズ
	sknmaster[SKANA_TYPE_C].sizeOffset.x = sknmaster[SKANA_TYPE_C].size.x / 2;
	sknmaster[SKANA_TYPE_C].sizeOffset.y = sknmaster[SKANA_TYPE_C].size.y / 2;
	sknmaster[SKANA_TYPE_C].lifeMax = 3;					//スライムの最大ライフ
	sknmaster[SKANA_TYPE_C].life = sknmaster[SKANA_TYPE_C].lifeMax;
	sknmaster[SKANA_TYPE_C].point = 100;
	sknmaster[SKANA_TYPE_C].ipos = { 62,87 };


	itemmaster[ITEM_TYPE_NEKOKAN].chartype      = ITEM_TYPE_NEKOKAN;			//敵の種類	蜂
	itemmaster[ITEM_TYPE_NEKOKAN].pos.x         = 300;						//蜂のX座標
	itemmaster[ITEM_TYPE_NEKOKAN].pos.y         = 400;						//蜂のY座標
	itemmaster[ITEM_TYPE_NEKOKAN].size.x        = 30;						//蜂の横画像サイズ
	itemmaster[ITEM_TYPE_NEKOKAN].size.y        = 30;						//蜂の縦画像サイズ
	itemmaster[ITEM_TYPE_NEKOKAN].sizeOffset.x  = itemmaster[ITEM_TYPE_NEKOKAN].size.x / 2;
	itemmaster[ITEM_TYPE_NEKOKAN].sizeOffset.y  = itemmaster[ITEM_TYPE_NEKOKAN].size.y / 2;
	itemmaster[ITEM_TYPE_NEKOKAN].lifeMax       = 3;						//蜂の最大ライフ
	itemmaster[ITEM_TYPE_NEKOKAN].life          = itemmaster[ITEM_TYPE_NEKOKAN].lifeMax;
	itemmaster[ITEM_TYPE_NEKOKAN].ipos          = { 62,90 };

	itemmaster[ITEM_TYPE_MATATABI].chartype     = ITEM_TYPE_MATATABI;		//敵の種類	炎
	itemmaster[ITEM_TYPE_MATATABI].pos.x        = 200;						//炎のX座標
	itemmaster[ITEM_TYPE_MATATABI].pos.y        = 400;						//炎のY座標
	itemmaster[ITEM_TYPE_MATATABI].size.x       = 50;						//炎の横画像サイズ
	itemmaster[ITEM_TYPE_MATATABI].size.y       = 50;						//炎の縦画像サイズ
	itemmaster[ITEM_TYPE_MATATABI].sizeOffset.x = itemmaster[ITEM_TYPE_MATATABI].size.x / 2;
	itemmaster[ITEM_TYPE_MATATABI].sizeOffset.y = itemmaster[ITEM_TYPE_MATATABI].size.y / 2;
	itemmaster[ITEM_TYPE_MATATABI].lifeMax      = 5;					//炎の最大ライフ
	itemmaster[ITEM_TYPE_MATATABI].life         = itemmaster[ITEM_TYPE_MATATABI].lifeMax;
	itemmaster[ITEM_TYPE_MATATABI].ipos         = { 62,90 };

	sknImage[SKANA_TYPE_A] = LoadGraph("image/魚.png");
	if (sknImage[SKANA_TYPE_A] == -1)
	{
		AST();
		return false;
	}
	sknImage[SKANA_TYPE_B] = LoadGraph("image/魚(赤).png");
	if (sknImage[SKANA_TYPE_B] == -1)
	{
		AST();
		return false;
	}
	sknImage[SKANA_TYPE_C] = LoadGraph("image/魚(黄).png");
	if (sknImage[SKANA_TYPE_C] == -1)
	{
		AST();
		return false;
	}
	itemImage[ITEM_TYPE_MATATABI] = LoadGraph("image/またたび.png");
	if (itemImage[ITEM_TYPE_MATATABI] == -1)
	{
		AST();
		return false;
	}
	itemImage[ITEM_TYPE_NEKOKAN] = LoadGraph("image/猫缶.png");
	if (itemImage[ITEM_TYPE_NEKOKAN] == -1)
	{
		AST();
		return false;
	}

	for (int it = 0; it < ITEM_MAX; it++)
	{
		item[it].chartype     = itemmaster[it].chartype;
		item[it].pos.x        = itemmaster[it].pos.x;
		item[it].pos.y        = itemmaster[it].pos.y;
		item[it].size.x       = itemmaster[it].size.x;
		item[it].size.y       = itemmaster[it].size.y;
		item[it].lifeMax      = itemmaster[it].lifeMax;
		item[it].sizeOffset.x = itemmaster[it].sizeOffset.x;
		item[it].sizeOffset.y = itemmaster[it].sizeOffset.y;
		item[it].life         = itemmaster[it].lifeMax;
		item[it].aniCnt       = 0;
		item[it].ipos         = itemmaster[it].ipos;
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		skn[s].chartype = sknmaster[s].chartype;
		skn[s].pos.x = sknmaster[s].pos.x;
		skn[s].pos.y = sknmaster[s].pos.y;
		skn[s].size.x = sknmaster[s].size.x;
		skn[s].size.y = sknmaster[s].size.y;
		skn[s].lifeMax = sknmaster[s].lifeMax;
		skn[s].sizeOffset.x = sknmaster[s].sizeOffset.x;
		skn[s].sizeOffset.y = sknmaster[s].sizeOffset.y;
		skn[s].life = sknmaster[s].lifeMax;
		skn[s].aniCnt = 0;
		skn[s].point = sknmaster[s].point;
		skn[s].ipos = sknmaster[s].ipos;
	}

	for (int it = 0; it < ITEM_MAX; it++)
	{
		item[it]	   = itemmaster[GetRand(ITEM_TYPE_MAX-1)];
		item[it].pos.x = GetRand(CHIP_SIZE_X * MAP_X - CHIP_SIZE_X * 2)+ SCREEN_SIZE_Y / 2;
		item[it].pos.y = GetRand(SCREEN_SIZE_Y/4)+200;
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		skn[s] = sknmaster[GetRand(SKANA_TYPE_MAX)];
		skn[s].pos.x = GetRand(CHIP_SIZE_X * MAP_X - CHIP_SIZE_X * 2) + SCREEN_SIZE_Y / 2;
		skn[s].pos.y = GetRand(SCREEN_SIZE_Y / 4) + 200;
	}
	 return true;
}
//アイテムの初期化ーーーーーーーーーーーーーーーーーーーーーー
void ItemGameInit(void)
{
    for (int it = 0; it < ITEM_MAX; it++)
	{
		item[it].lifeMax = itemmaster[it].lifeMax;
		item[it].life    = itemmaster[it].lifeMax;
		item[it].aniCnt  = 0;
		item[it].ipos    = itemmaster[it].ipos;
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		skn[s].lifeMax = sknmaster[s].lifeMax;
		skn[s].life = sknmaster[s].lifeMax;
		skn[s].aniCnt = 0;
		skn[s].point = sknmaster[s].point;
		skn[s].ipos = sknmaster[s].ipos;
	}
	mutekiCnt = 0;
}
//アイテムを生成ーーーーーーーーーーーーーーーーーーーーーー

void CreateItem(void)
{
	for (int it = 0; it < ITEM_MAX; it++)
	{
		if (item[it].life <= 0)
		{
			item[it].pos.x = GetRand(CHIP_SIZE_X * MAP_X - CHIP_SIZE_X * 2)+ SCREEN_SIZE_X;
			item[it].pos.y = GetRand(SCREEN_SIZE_Y / 4) + 200;
			item[it].life = item[it].lifeMax;
		}
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		if (skn[s].life <= 0)
		{
			skn[s].pos.x = GetRand(CHIP_SIZE_X * MAP_X - CHIP_SIZE_X * 2) + SCREEN_SIZE_X;
			skn[s].pos.y = GetRand(SCREEN_SIZE_Y / 4) + 200;
			skn[s].life = skn[s].lifeMax;
		}
	}
}

//アイテム操作ーーーーーーーーーーーーーーーーーーーーーー
void ItemControl(void)
{
	
	for (int it = 0; it < ITEM_MAX; it++)
	{
		item[it].pos.x -= 5;			// 背景のスクロール

		if (item[it].pos.x <= -SCREEN_SIZE_X)
		{
			item[it].pos.x = SCREEN_SIZE_X;
		}
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		//if (skn[s].life > 0)
		//{
		//	/*if (ItemHitCheck(skn[s].pos, skn[s].size))
		//	{
		//		switch (skn[s].chartype)
		//		{
		//		case SKANA_TYPE_A:
		//			AddScore(10);
		//			break;
		//		case SKANA_TYPE_B:
		//			AddScore(50);
		//			break;
		//		case SKANA_TYPE_C:
		//			AddScore(100);
		//			break;
		//		}
		//	}*/
		//}
		skn[s].pos.x -= 5;			// 背景のスクロール

		if (skn[s].pos.x <= -SCREEN_SIZE_X)
		{
			skn[s].pos.x = SCREEN_SIZE_X;
		}
	}
	if (mutekiCnt > 0)//当たった時の無敵時間
	{
		mutekiCnt--;
		if (mutekiCnt <= 0)
		{
			mutekiCnt = 0;
		}
	}
}

//アイテム消失ーーーーーーーーーーーーーーーーーーーーーー
void Deleteitem(void)
{
	for (int it = 0; it < ITEM_MAX; it++)
	{
		if (item[it].life > 0)
		{
			if (ItemHitCheck(item[it].pos, item[it].size))
			{
				item[it].life = 0;
				switch (item[it].chartype)
				{
				case ITEM_TYPE_NEKOKAN:
					Muteki();
					mutekiCnt = MUTEKI_TIME;
					break;
				case ITEM_TYPE_MATATABI:
					if (mutekiCnt == 0)
					{
						player1.life = 0;
					}
					break;
				}
				CreateItem();
			}
		}
	}


	for (int s = 0; s < SKANA_MAX; s++)
	{
		if (skn[s].life > 0)
		{
			if (ItemHitCheck(skn[s].pos, skn[s].size))
			{
				skn[s].life = 0;
				switch (skn[s].chartype)
				{
				case SKANA_TYPE_A:
					AddScore(sknmaster[SKANA_TYPE_A].point);
					break;
				case SKANA_TYPE_B:
					AddScore(sknmaster[SKANA_TYPE_B].point);
					break;
				case SKANA_TYPE_C:
					AddScore(sknmaster[SKANA_TYPE_C].point);
					break;
				}
				CreateItem();
			}
		}
	}
}

//アイテムの描画ーーーーーーーーーーーーーーーーーーーーーー
void ItemDraw(void)
{
	for (int it = 0; it < ITEM_MAX; it++)
	{
		if (item[it].life > 0)
		{
			DrawGraph(item[it].pos.x - item[it].sizeOffset.x + mapPos.x
				, item[it].pos.y - item[it].sizeOffset.y + mapPos.y
				, itemImage[item[it].chartype], true);
		}
	}
	for (int s = 0; s < SKANA_MAX; s++)
	{
		if (skn[s].life > 0)
		{
			DrawGraph(skn[s].pos.x - skn[s].sizeOffset.x + mapPos.x
				, skn[s].pos.y - skn[s].sizeOffset.y + mapPos.y
				, sknImage[skn[s].chartype], true);
		}
	}
	
}