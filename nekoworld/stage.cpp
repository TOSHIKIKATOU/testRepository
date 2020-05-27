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


// •Ï”
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


// ½Ã°¼Şî•ñ‚Ì‰Šú‰»
bool StageSystemInit(void)
{
	int ret;

	ret = LoadDivGraph("image/áŠQ•¨.png"
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

// ½Ã°¼Şî•ñ‚Ì¹Ş°Ñ‰Šú‰»
void StageGameInit(void)
{

	// •Ï”‚Ì‰Šú‰»
	mapPos.x = 0;
	mapPos.y = 0;
	haikeiPos = { 0, 0};
	haikeiturnPos = { SCREEN_SIZE_X, 0 };
	haikeispeed = 1;
	haikeicnt = 0;

}

// Ëß¸¾ÙÀ•WŒn‚©‚çÏ¯Ìß”z—ñÀ•WŒn‚É•ÏŠ·‚·‚éB
XY Pos2Index(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;//pos‚ÌxÀ•W‚ğ•ÏŠ·;
	tmp.y = pos.y / CHIP_SIZE_Y;//pos‚ÌyÀ•W‚ğ•ÏŠ·;

								// •ÏŠ·‚µ‚½’l‚ğ•Ô‚·
	return tmp;
}

// Ï¯Ìß”z—ñÀ•WŒn‚©‚çËß¸¾ÙÀ•WŒn(¶ã)‚É•ÏŠ·‚·‚éB
XY Index2Pos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;//pos‚ÌxÀ•W‚ğ•ÏŠ·;
	tmp.y = index.y * CHIP_SIZE_Y;//pos‚ÌyÀ•W‚ğ•ÏŠ·;

								// •ÏŠ·‚µ‚½’l‚ğ•Ô‚·
	return tmp;
}

// w’è‚µ‚½À•W‚ª’Ê‰ß‰Â”\‚©‚ğ•Ô‚·@true:’Ê‰ß‚Å‚«‚é
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
		// ’Ê‚ê‚È‚¢
		return false;
		break;
	default:
		break;
	}
	return true;
	
}

// ½Ã°¼Ş‚Ì•`‰æ
void StageGameDraw(void)
{
	haikeicnt++;

	if (haikeicnt % 1800 == 0)
	{
		haikeispeed++;
	}
		
	
	

	// ”wŒi‰æ‘œ‚Ì•`‰æ
	DrawGraph(haikeiPos.x
		, 0
		, haikeiimage, true);

	// ”½“]‚µ‚½”wŒi‰æ‘œ‚Ì•`‰æ
	DrawGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);

	haikeiturnPos.x -= haikeispeed;		//  ”½“]‚µ‚½”wŒi‚ÌƒXƒNƒ[ƒ‹

	haikeiPos.x -= haikeispeed;			// ”wŒi‚ÌƒXƒNƒ[ƒ‹

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