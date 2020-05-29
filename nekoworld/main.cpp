// AsoRockman
// 
// main.cpp
//
// 2019.11.01
//
// 1916009_Kato Toshiki


#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "scene.h"
#include "stage.h"
#include "player.h"
#include "player2.h"
#include "shot.h"
#include "shot2.h"
#include "effect.h"
#include"item.h"



// •Ï”
//--------------------------------------------------------------------------------------------
SCENE_ID sceneID;						// ¡‚Ì¼°İID
SCENE_ID scenePreID;					// ˆê‚Â‘O‚Ì¼°İID
int SceneCounter;		

int titleImage;
int gameoverImage;
int hitstartImage;
int winImage[2];
int drawImage;
int time;
int mtImage;
int logoRol;
float logoScl;
int aaaa;
int tlImage;
int catImage[4];
int haikei2image;
XY haikei1Pos;
XY haikeiturnPos;
int haikei1image;
int haikeiturnimage;
FILE_DATA fileData;
XY selectpos;
int selectflag;
int select2flag;
int seCNT;
int P1Image[4];
int P2Image[4];
// WinMain()
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----	‰Šú‰»ˆ—
	if (!SystemInit())
	{
		
		return -1;
	}

	////----- ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		

		ClsDrawScreen();	// ‰æ–ÊÁ‹

		// ¼°İ¶³İÀ‚Ì‰Šú‰»
		if (sceneID != scenePreID)
		{
			scenePreID = sceneID;
			SceneCounter = 0;
		}

		KeyCheck();

		// Ò²İˆ—
		switch (sceneID)
		{

			// ‰Šú‰»
		case SCENE_ID_INIT:
			
			InitScene();
			break;

			// À²ÄÙ
		case SCENE_ID_TITLE:
			// ‰æ–ÊØ‚è‘Ö‚¦´Ìª¸Ä
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// ´Ìª¸ÄI—¹Œãˆ—
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ´Ìª¸ÄI—¹Œãˆ—
					sceneID = SCENE_ID_SERECT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
		TitleScene();
			break;
		case SCENE_ID_SERECT:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// ´Ìª¸ÄI—¹Œãˆ—
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ´Ìª¸ÄI—¹Œãˆ—
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameSerectScene();
			break;

			// ¹Ş°Ñ
		case SCENE_ID_GAME:
			// ‰æ–ÊØ‚è‘Ö‚¦´Ìª¸Ä
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// ´Ìª¸ÄI—¹Œãˆ—
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ´Ìª¸ÄI—¹Œãˆ—
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameScene();
			break;

			// ¹Ş°Ñµ°ÊŞ°
		case SCENE_ID_GAMEOVER:
			// ‰æ–ÊØ‚è‘Ö‚¦´Ìª¸Ä
			if (fadeIn)
			{
				if (!FadeInScreen(5)) 
				{
					fadeOut = false;
				}// ´Ìª¸ÄI—¹Œãˆ—
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// ´Ìª¸ÄI—¹Œãˆ—
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}

			GameOverScene();
			break;

		}
		
		SceneCounter++;

		ScreenFlip(); // — ‰æ–Ê‚ğ•\‰æ–Ê‚ÉuŠÔºËß°
	}

	DxLib_End(); // DX×²ÌŞ×Ø‚ÌI—¹ˆ—

	return 0;
}

// ¼½ÃÑ‰Šú‰»
bool SystemInit(void)
{
	bool retFlag = true; // ŠÖ”‚Ì–ß‚è’l// ƒ[ƒJƒ‹•Ï”

	//----- ¼½ÃÑˆ—
	SetWindowText("1916009_Kato Toshiki");
	// ¼½ÃÑˆ—
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	
	KeyInit();			// ·°‚Ì‰Šú‰»
	EffectInit();		// ´Ìª¸Ä‚Ì‰Šú‰»

	if (!StageSystemInit()) return false;
	PlayerSystemInit();
	Player2SystemInit();
	ShotSystemInit();
	Shot2SystemInit();
	ItemSystemInit();
	if (!EffectSystemInit()) return false;

	//----- ¸Ş×Ì¨¯¸‚Ì“o˜^

	LoadDivGraph("image/run5.png", 4, 4, 1, 80, 80, catImage);
	titleImage = LoadGraph("image/title.png");
	if (titleImage == -1)
	{
		AST();
		retFlag = false;
	}

	hitstartImage = LoadGraph("image/hitstartkey.png");
	if (hitstartImage == -1)
	{
		AST();
		retFlag = false;
	}

	winImage[0] = LoadGraph("image/WIN1.png");
	if (winImage[0] == -1)
	{
		AST();
		retFlag = false;
	}

	winImage[1] = LoadGraph("image/WIN2.png");
	if (winImage[1] == -1)
	{
		AST();
		retFlag = false;
	}

	drawImage = LoadGraph("image/Draw.png");
	if (drawImage == -1)
	{
		AST();
		retFlag = false;
	}
	mtImage= LoadGraph("image/‚Ü‚½‚½‚Ñ.png");
	if (mtImage == -1)
	{
		AST();
		retFlag = false;
	}
	tlImage = LoadGraph("image/ƒ^ƒCƒgƒ‹.png");
	haikeiturnimage= LoadGraph("image/”wŒi.png");
	haikei1image = LoadGraph("image/”wŒi.png");
	haikei2image = LoadGraph("image/”wŒiu‘v.png");
	LoadDivGraph("image/run6.png", 4, 4, 1, 80, 80, P1Image);
	LoadDivGraph("image/run7.png", 4, 4, 1, 80, 80, P2Image);
	//P2Image = LoadGraph("image/’…’n.png");
	//P3Image = LoadGraph("image/Q‚é.png");
	//----- •Ï”‰Šú‰»
	SceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	scenePreID = SCENE_ID_MAX;
	
	aaaa = 0;

	return true;
}

// ‰Šú‰»—p¼°İ—p
void InitScene(void)
{
	sceneID = SCENE_ID_TITLE;
	StageGameInit();
	ShotGameInit();
	Shot2GameInit();
	PlayerGameInit();
	Player2GameInit();
	EffectGameInit();
	ItemGameInit();
	time = 60;
	haikei1Pos = {0,0};
	haikeiturnPos = { SCREEN_SIZE_X,0 };
	logoRol = 0;
	logoScl = 0.0f;
	fileData.score = 0;
	fileData.hiScore = 0;
	selectpos = {0,0};
	selectflag=false;
	select2flag = false;
	seCNT=0;

}

// À²ÄÙ¼°İ—p
void TitleScene(void)
{
	
	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}


	haikei1Pos.x -= 5;			// ”wŒi‚ÌƒXƒNƒ[ƒ‹

	if (haikei1Pos.x <= -SCREEN_SIZE_X)
	{
		haikei1Pos.x = SCREEN_SIZE_X;
	}

	


	haikeiturnPos.x -= 5;		//  ”½“]‚µ‚½”wŒi‚ÌƒXƒNƒ[ƒ‹

	if (haikeiturnPos.x <= -SCREEN_SIZE_X)
	{
		haikeiturnPos.x = SCREEN_SIZE_X;
	}
	
	TitleDraw();
}

// À²ÄÙ¼°İ‚Ì•`‰æ
void TitleDraw(void)
{
	

	//DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", SceneCounter, true);
	// ”wŒi‰æ‘œ‚Ì•`‰æ
	DrawGraph(haikei1Pos.x
		, 0
		, haikei1image, true);
	// ”½“]‚µ‚½”wŒi‰æ‘œ‚Ì•`‰æ
	DrawTurnGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);
	DrawGraph(200
		, SCREEN_SIZE_Y-170
		, catImage[(SceneCounter / 10 % 4)], true);
	DrawGraph(haikei1Pos.x, 0, haikei2image, true);
	DrawTurnGraph(haikeiturnPos.x, 0, haikei2image, true);
	//DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);

	//DrawGraph(0, 0, titleImage, true);
	DrawGraph(0, 0, tlImage, true);
	DrawGraph(300, 430, hitstartImage, true);

}
void GameSerectScene(void)
{
	
	GameSerectSceneDraw();
		
		if (selectflag == false)
		{
			if (selectpos.y < 100)
			{
				if (keyDownTrigger[KEY_ID_P2RIGHT])
				{
					selectpos.y += 50;
				}
			}
			if (selectpos.y > 0)
			{
				if (keyDownTrigger[KEY_ID_P2LEFT])
				{
					selectpos.y -= 50;
				}
			}
		}
		if (selectflag == true)
		{
			if (selectpos.x > 250)
			{
				if (keyDownTrigger[KEY_ID_P2LEFT])
				{
					selectpos.x -= 250;
				}
			}
			if (selectpos.x < 500)
			{
				if (keyDownTrigger[KEY_ID_P2RIGHT])
				{
					selectpos.x += 250;
				}
			}
		}
		DrawMenu();
		switch (selectpos.y)
		{
		case 0:	
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}
			break;
		case 50:
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}
			break;
		case 100:
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}

			break;
		}

	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}
}
void GameSerectSceneDraw(void)
{
	// ”wŒi‰æ‘œ‚Ì•`‰æ
	DrawGraph(haikei1Pos.x
		, 0
		, haikei1image, true);
	// ”½“]‚µ‚½”wŒi‰æ‘œ‚Ì•`‰æ
	DrawTurnGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);
	DrawGraph(haikei1Pos.x, 0, haikei2image, true);
	DrawTurnGraph(haikeiturnPos.x, 0, haikei2image, true);
	//DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);
}
void DrawMenu(void)
{
	if (selectpos.y == 0)
	{
		DrawBox(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);
		DrawExtendGraph(100, SCREEN_SIZE_Y / 2-100, 300, SCREEN_SIZE_Y/2+100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
		//DrawGraph(400, SCREEN_SIZE_Y / 2 - 50, P2Image, true);
		//DrawGraph(600, SCREEN_SIZE_Y / 2 - 50, P3Image, true);
	}
	else if (selectpos.y == 50)
	{
		DrawBox(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);

		DrawExtendGraph(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
	}
	else if (selectpos.y == 100)
	{

		DrawBox(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);

		DrawExtendGraph(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
	}
}
// ¹Ş°Ñ¼°İ—p
void GameScene(void)
{

	if (Player1Dawn() == true || Player2Dawn()  == true || time ==  0)
	{
		
		fadeOut = true;
	}

	// Pause‹@”\
	if (keyUpTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;
	}

	if (pauseFlag == true)
	{
		SetDrawBright(128, 128, 128);
	}
	else
	{
		aaaa++;	// Šeíˆ—
		DeleteShot();
		DeleteShot2();
		PlayerControl();
		Player2Control();
		/*StageGame();*/
		ShotControl();
		Shot2Control();
		EffectControl();
		ItemControl();
		Deleteitem();
		
		if (SceneCounter % 60 == 59)
		{
			time--;
		}
	}


	GameSceneDraw();

	if (pauseFlag == true)
	{
		SetDrawBright(255, 255, 255);
		DrawString(280 , 230, "‚o‚`‚t‚r‚d", GetColor(255, 255, 255), true);
	}


	return;
}
// ¹Ş°Ñ¼°İ‚Ì•`‰æ
void GameSceneDraw(void)
{
	StageGameDraw();
	ShotGameDraw();

	Shot2GameDraw();
	PlayerGameDraw();
	ItemDraw();
	
	EffectGameDraw();
	DrawFormatString(0, 0, 0xFFFFFF, "%d", fileData.score);
	if (time >= 10)
	{
		SetFontSize(35);
		DrawFormatString(365, 0, GetColor(0, 0, 0), "%d", time);
	}
	else if (time <= 9)
	{
		SetFontSize(60);
		DrawFormatString(370, 0, GetColor(255, 0, 0), "%d", time);
	}

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
}

// ¹Ş°Ñµ°ÊŞ°¼°İ—p
void GameOverScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	// ”wŒiÒ¯¾°¼Ş‚Ì‰ñ“]‚Æ•`‰æ
	logoRol += 6;
	if (logoRol >= 360) logoRol = 360;
	logoScl += 0.02f;
	if (logoScl > 1.0f) logoScl = 1.0f;

	GameOverDraw();
}

// ¹Ş°Ñµ°ÊŞ°¼°İ‚Ì•`‰æ
void GameOverDraw(void)
{

	GameSceneDraw();

	// Œ‹‰Ê‚ğ‚à‚Æ‚É•`‰æ
	if (Player1Dawn() == false && Player2Dawn() == true)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl,
			logoScl, (DX_PI_F / 180)*logoRol, winImage[0], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == false)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl
			, logoScl, (DX_PI_F / 180)*logoRol, winImage[1], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == true || time <= 0 )
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl
			, logoScl, (DX_PI_F / 180)*logoRol, drawImage, true);
	}

	//DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}


void AddScore(int point)
{
	fileData.score += point;
	if (fileData.hiScore < fileData.score)
	{
		fileData.hiScore = fileData.score;
	}
}
