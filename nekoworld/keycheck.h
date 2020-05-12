// AsoRockman
// 
// keycheck.h
//
// 2019.09.24
//
// 1916009_Kato Toshiki

//#pragma once


// �񋓌^�̒�`
//------------------------------------------------------------------
// ���͏��p
enum KEY_ID
{
	KEY_ID_SPACE,			// ��߰���
	KEY_ID_PAUSE,
	KEY_ID_P1UP,
	KEY_ID_P2UP,
	KEY_ID_P1RIGHT,
	KEY_ID_P2RIGHT,
	KEY_ID_DOWN,
	KEY_ID_P1LEFT,
	KEY_ID_P2LEFT,
	KEY_ID_P1SHOT,
	KEY_ID_P2SHOT,
	KEY_ID_MAX
};

// extern�錾
//-------------------------------------------------------------------
extern bool keyOld[KEY_ID_MAX];					// �O�̓���
extern bool keyNew[KEY_ID_MAX];					// ���݂̓��͏��
extern bool keyDownTrigger[KEY_ID_MAX];			// �޳ݎ����ضް
extern bool keyUpTrigger[KEY_ID_MAX];			// �A�b�v�����ضް

// �������ߐ錾
//-------------------------------------------------------------------
void KeyInit(void);								// ���̏�����
void KeyCheck(void);							// ��������
