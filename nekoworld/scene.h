// AsoRockman
// 
// scene.h
//
// 2019.09.25
//
// 1916009_Kato Toshiki

//#pragma once

// externéŒ¾
//-------------------------------------------------------------------
// ‰æ–ÊØ‚è‘Ö‚¦´Ìª¸Ä
extern int fadeCnt;						// Ìª°ÄŞ‚Ì¶³İÄ
extern bool fadeIn;						// Ìª°ÄŞ²İ
extern bool fadeOut;					// Ìª°ÄŞ±³Ä
// ˆê’â~´Ìª¸Ä
extern bool pauseFlag;					// Îß°½Ş‚ÌFlag


// ÌßÛÄÀ²ÌßéŒ¾
//------------------------------------------------------------------
void EffectInit(void);					// ´Ìª¸Ä‚Ì‰Šú‰»
bool FadeInScreen(int fadeStep);		// Ìª°ÄŞ²İˆ—
bool FadeOutScreen(int fadeStep);		// Ìª°ÄŞ±³Äˆ—