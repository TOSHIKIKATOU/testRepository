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



// •Ï”
//--------------------------------------------------------------------------------------------
SCENE_ID sceneID;						// ¡‚Ì¼°ÝID
SCENE_ID scenePreID;					// ˆê‚Â‘O‚Ì¼°ÝID
int SceneCounter;		

int titleImage;
int gameoverImage;
int hitstartImage;
int winImage[2];
int drawImage;

int time;

int logoRol;
float logoScl;

int aaaa;

// WinMain()
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----	‰Šú‰»ˆ—
	if (!SystemInit())
	{
		
		return -1;
	}

	////----- ¹Þ°ÑÙ°Ìß
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		

		ClsDrawScreen();	// ‰æ–ÊÁ‹Ž

		// ¼°Ý¶³ÝÀ‚Ì‰Šú‰»
		if (sceneID != scenePreID)
		{
			scenePreID = sceneID;
			SceneCounter = 0;
		}

		KeyCheck();

		// Ò²Ýˆ—
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
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
		TitleScene();
			break;

			// ¹Þ°Ñ
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

			// ¹Þ°Ñµ°ÊÞ°
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

		ScreenFlip(); // — ‰æ–Ê‚ð•\‰æ–Ê‚ÉuŠÔºËß°
	}

	DxLib_End(); // DX×²ÌÞ×Ø‚ÌI—¹ˆ—

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
	if (!EffectSystemInit()) return false;

	//----- ¸Þ×Ì¨¯¸‚Ì“o˜^

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

	//----- •Ï”‰Šú‰»
	SceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	scenePreID = SCENE_ID_MAX;
	
	aaaa = 0;

	return true;
}

// ‰Šú‰»—p¼°Ý—p
void InitScene(void)
{
	sceneID = SCENE_ID_TITLE;
	StageGameInit();
	ShotGameInit();
	Shot2GameInit();
	PlayerGameInit();
	Player2GameInit();
	EffectGameInit();

	time = 600;

	logoRol = 0;

	logoScl = 0.0f;
}

// À²ÄÙ¼°Ý—p
void TitleScene(void)
{
	
	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}

	
	TitleDraw();
}

// À²ÄÙ¼°Ý‚Ì•`‰æ
void TitleDraw(void)
{
	

	//DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", SceneCounter, true);

	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);

	DrawGraph(0, 0, titleImage, true);

	DrawGraph(200, 430, hitstartImage, true);

}

// ¹Þ°Ñ¼°Ý—p
void GameScene(void)
{

	/*if (Player1Dawn() == true || Player2Dawn()  == true || time ==  0)
	{
		
		fadeOut = true;
	}*/
	

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
		aaaa++;	// ŠeŽíˆ—
		DeleteShot();
		DeleteShot2();
		PlayerControl();
		Player2Control();
		ShotControl();
		Shot2Control();
		EffectControl();
		
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

// ¹Þ°Ñ¼°Ý‚Ì•`‰æ
void GameSceneDraw(void)
{

	StageGameDraw();

	ShotGameDraw();

	Shot2GameDraw();

	PlayerGameDraw();

	Player2GameDraw();

	EffectGameDraw();

	//DrawFormatString(0, 0, 0xFFFFFF, "GameScene : %d", SceneCounter, true);


	//DrawFormatString(32, 32, 0xFFFFFF, " %d ", aaaa, true);

	if (time >= 30)
	{
		SetFontSize(35);
		DrawFormatString(365, 0, GetColor(0, 0, 0), "%d", time);
	}
	else if (time <= 29)
	{
		SetFontSize(60);
		DrawFormatString(370, 0, GetColor(255, 0, 0), "%d", time);
	}

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);

	
}

// ¹Þ°Ñµ°ÊÞ°¼°Ý—p
void GameOverScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	// ”wŒiÒ¯¾°¼Þ‚Ì‰ñ“]‚Æ•`‰æ
	logoRol += 6;
	if (logoRol >= 360) logoRol = 360;
	logoScl += 0.02f;
	if (logoScl > 1.0f) logoScl = 1.0f;

	GameOverDraw();
}

// ¹Þ°Ñµ°ÊÞ°¼°Ý‚Ì•`‰æ
void GameOverDraw(void)
{

	GameSceneDraw();

	// Œ‹‰Ê‚ð‚à‚Æ‚É•`‰æ
	if (Player1Dawn() == false && Player2Dawn() == true)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, winImage[0], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == false)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, winImage[1], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == true || time <= 0 )
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, drawImage, true);
	}

	//DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}



