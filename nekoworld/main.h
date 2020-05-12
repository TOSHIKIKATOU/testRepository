// AsoRockman
// 
// main.h
//
// 201911.01
//
// 1916009_Kato Toshiki

//#pragma once

//���Ă̒�`
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "�A�T�[�g�\��", MB_OK);\
	}
#else
#define AST()
#endif


// �萔
//------------------------------------------------------------------
#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	480
#define ACC_G			10	// �d�͉����x
#define FRAME_TIME		0.3f	// [s]




// �񋓌^�̒�`
//------------------------------------------------------------------
// ��݊Ǘ��p
enum SCENE_ID
{
	SCENE_ID_INIT,			// ���������
	SCENE_ID_TITLE,			// ���ټ��
	SCENE_ID_GAME,			// �ްѼ��
	SCENE_ID_GAMEOVER,		// �ްѵ��ް���
	SCENE_ID_MAX,
};

// ��ڲ԰�Ǘ��p
enum PLAYER {
	PLAYER1
	, PLAYER2
	, PLAYER_MAX
};

enum DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

struct XY {
	int x;
	int y;
};

struct XY_F {
	float x;
	float y;
};

struct CHARACTER {
	DIR moveDir;	//�����Ă������
	XY pos;			//�L�����N�^�̈ʒu�i���S�j
	XY size;		//�L�����N�^�摜�̃T�C�Y
	XY sizeOffset;		//�L�����N�^��������̍���ʒu
	XY hitPosS;		//�����蔻��p�̍���
	XY hitPosE;		//�����蔻��p�̉E��
	bool runFlag;		//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	bool jumpFlag;		//�L�����N�^�̏�ԁi�W�����v���Ă��邩�H�j
	bool shotFlag;		//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	bool damageFlag;	//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	XY_F velocity;		// ��׸��̑��x
	int moveSpeed;		//�L�����N�^�̈ړ���
	int life;		//�L�����N�^�̗̑�
	int lifeMax;		//�L�����N�^�̗͍̑ő�
	int animCnt;		//�L�����N�^�̃A�j���[�V�����p�J�E���^
	int imgLockCnt;		//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	bool visible;		//�\�����
	int type;			//���炩�̑������i�[�ł���B
};


// �������ߐ錾
//------------------------------------------------------------------
bool SystemInit(void);							// ���я�����
void InitScene(void);							// �������p��ݗp
// ���ټ��
void TitleScene(void);							// ���ټ�ݗp
void TitleDraw(void);							// ���ټ�݂̕`��
// �ްѼ��
void GameScene(void);							// �ްѼ�ݗp
void GameSceneDraw(void);						// �ްѼ�݂̕`��
// �ްѵ��ް���
void GameOverScene(void);						// �ްѵ��ް��ݗp
void GameOverDraw(void);						// �ްѵ��ް��݂̕`��



