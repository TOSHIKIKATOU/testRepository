//#pragma once
#define ITEM_MAX 50			//最大アイテム数
#define SKANA_MAX 100	
#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 50
#define ITEM_BRAND 3



enum SKANA_TYPE
{
	SKANA_TYPE_A,
	SKANA_TYPE_B,
	SKANA_TYPE_C,
	SKANA_TYPE_MAX
};
enum ITEM_TYPE
{	
	ITEM_TYPE_NEKOKAN,			
	ITEM_TYPE_MATATABI,	
	ITEM_TYPE_MAX
};

bool ItemSystemInit(void);//弾の初期化
void ItemGameInit(void);
void CreateItem(void);
void ItemControl(void);//弾の捜査
void ItemDraw(void);//弾の描画
void Deleteitem(void);


//XY Pos22Index(XY pos);				// ﾋﾟｸｾﾙ座標系からﾏｯﾌﾟ配列座標系に変換する。
//XY Index22Pos(XY index);				// ﾏｯﾌﾟ配列座標系からﾋﾟｸｾﾙ座標系に変換する。
//bool Is2Pass(XY pos);				// 指定した座標が通過可能かを返す　true:通過できる