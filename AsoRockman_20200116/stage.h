// AsoRockman
// 
// stage.h
//
// 2019.11.05
//
// 1916009_Kato Toshiki

//#pragma once

extern XY mapPos;

// �萔
//------------------------------------------------------------------
#define MAP_X	64
#define MAP_Y	15
#define CHIP_SIZE_X		32
#define CHIP_SIZE_Y		32
#define SCROLL_X_MIN 200
#define SCROLL_X_MAX 600

// �������ߐ錾
//------------------------------------------------------------------
bool StageSystemInit(void);			// �ð�ޏ��̏�����
void StageGameInit(void);			// �ð�ޏ��̹ްя�����
void StageGameDraw(void);			// �ð�ނ̕`��

XY Pos2Index(XY pos);				// �߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����B
XY Index2Pos(XY index);				// ϯ�ߔz����W�n�����߸�ٍ��W�n�ɕϊ�����B
bool IsPass(XY pos);				// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߂ł���
