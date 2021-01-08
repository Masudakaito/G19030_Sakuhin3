//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include <math.h>

//########## �}�N����` ##########
#define GAME_WIDTH			960	//��ʂ̉��̑傫��
#define GAME_HEIGHT			540	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0					//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"		//�E�B���h�E�̃^�C�g��

#define GAME_PI							3.1415	//��
#define GAME_FPS						60	//FPS�̒l
#define GAME_HANKEI							30	//�~�̔��a

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129	//0x0000�`0x0080�܂�

//�L�[�{�[�h�̎��
#define KEY_CODE_KIND		256	//256���

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

#define TOGE_MOVE           2	//�g�Q����������
#define TOGE_SPEED          2	//�g�Q�̃X�s�[�h

//�t�H���g
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�G���[���b�Z�[�W
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

//����{�^�����������Ƃ�
#define MSG_CLOSE_TITLE			TEXT("�I�����b�Z�[�W")
#define MSG_CLOSE_CAPTION		TEXT("�Q�[�����I�����܂����H")

#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	16	//�}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�

#define IMG_SOUGEN				TEXT(".\\IMAGE\\sougen.png")			//�^�C�g����ʂ̔w�i
#define IMG_SORA				TEXT(".\\IMAGE\\sora.png")				//�v���C��ʂ̔w�i
#define IMG_MARU				TEXT(".\\IMAGE\\player2.png")			//�v���C���[�̉摜
#define IMG_LOGO				TEXT(".\\IMAGE\\ParQuiz.png")			//���S�̉摜
#define IMG_LOGO_CLEAR			TEXT(".\\IMAGE\\logo_end.png")			//�N���A�̉摜
#define IMG_LOGO_OVER			TEXT(".\\IMAGE\\logo_end2.png")			//�Q�[���I�[�o�[�̉摜
#define IMG_SPACE				TEXT(".\\IMAGE\\pressofspace.png")		//PRESS OF SPACEKEY�̉摜
#define IMG_ENTER				TEXT(".\\IMAGE\\pressofenter.png")		//PRESS OF ENTER�̉摜

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip1ver5.png")		//�}�b�v�̉摜

#define MAP_DIV_WIDTH		60	//�摜�𕪊����镝�T�C�Y
#define MAP_DIV_HEIGHT		60	//�摜�𕪊����鍂���T�C�Y
#define MAP_DIV_TATE		4	//�摜���c�ɕ������鐔
#define MAP_DIV_YOKO		4	//�摜�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�摜�𕪊����鑍��

//�G���[���b�Z�[�W
#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

//�I���_�C�A���O�p
#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")

#define MUSIC_START_PATH		TEXT(".\\MUSIC\\1.Start.mp3")	//�^�C�g�����BGM
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\2.Play.mp3")	//�v���C���BGM
#define MUSIC_CLEAR_PATH		TEXT(".\\MUSIC\\3.Clear.mp3")	//�N���A���BGM
#define MUSIC_OVER_PATH			TEXT(".\\MUSIC\\4.Over.mp3")	//�Q�[���I�[�o�[���BGM
#define MUSIC_KETTEI_PATH		TEXT(".\\MUSIC\\Kettei.mp3")	//������ʉ�
#define MUSIC_JUMP1_PATH		TEXT(".\\MUSIC\\Jump1.mp3")		//�W�����v���ʉ�
#define MUSIC_JUMP2_PATH		TEXT(".\\MUSIC\\Jump2.mp3")		//�W�����v�j�i�ڌ��ʉ�
#define MUSIC_STAR_PATH			TEXT(".\\MUSIC\\Star.mp3")		//�X�^�[���ʉ�

enum GAME_MAP_KIND
{
	m1 = -1,	//����
	m2 = -2,	//����
	m3 = -3,	//����
	b = 1,	//�u���b�N
	g = 2,	//�S�[��
	d = 3,	//�g�Q2(�f���W���[)
	n = 4,	//�g�Q(�j�[�h��)
	h1 = 5,	//��1
	h2 = 6,	//��2
	h3 = 7,	//��3
	m = 8,	//�g�Q(���[�u)
	a = 9,  //�����u���b�N
	t = 10,	//�ʘH
	s = 11	//�X�^�[�g
};	//�}�b�v�̎��

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum GAME_STAGE {
	GAME_STAGE_1,
	GAME_STAGE_2,
	GAME_STAGE_3,
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 7,

};	//�L�����N�^�[�̃X�s�[�h

enum GAME_END {
	GAME_END_CLEAR,	//�N���A
	GAME_END_OVER	//�Q�[���I�[�o�[
};	//�Q�[���̏I�����

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;	//���W��������
	int y = -1;	//���W��������

}iPOINT;

//�}�E�X�\����
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInput�̒l������
	int WheelValue = 0;	//�}�E�X�z�C�[���̉�]��(���̓v���X�l / ��O�̓}�C�i�X�l)
	iPOINT Point;		//�}�E�X�̍��W������
	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^������(���O)������
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//�}�E�X�̃{�^�����͂�����

}MOUSE;

//�t�H���g�\����
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//�p�X
	char name[NAME_MAX];		//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
	double radian;				//���W�A��(�p�x)
	BOOL IsDraw = FALSE;		//�`��ł��邩

}IMAGE;	//�摜�\����

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��

}MUSIC;	//���y�\����

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE�\����
	int speed;					//����
	int CenterX;				//���SX
	int CenterY;				//���SY

	double radian;				//���W�A��(�p�x)

	RECT coll;					//�����蔻��
	iPOINT collBeforePt;		//������O�̍��W

}CHARA;	//�L�����N�^�[�\����

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP_DIV_NUM];			//���������}�b�v�̉摜�n���h��
	int kind[MAP_DIV_NUM];				//�}�b�v�̎��
	int width;							//��
	int height;							//����

}MAPCHIP;	//MAP_IMAGE�\����

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//�}�b�v�̎��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}MAP;	//MAP�\����

struct MY_CIRCLE
{
	int x;		//���̈ʒu
	int y;		//�c�̈ʒu
	int radius;	//���a
};	//�~�̍\����

//########## �O���[�o���ϐ� ##########
//FPS�֘A
int StartTimeFps;				//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς����T���v����

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[KEY_CODE_KIND] = { '\0' };		//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };	//���ׂẴL�[�̏��(���O)������

//�}�E�X�̍��W���擾
MOUSE mouse;

//�Q�[���֘A
int GameScene;			//�Q�[���V�[�����Ǘ�

int GameStage;			//�Q�[���̃X�e�[�W���Ǘ�

int GameEndKind;		//�Q�[���̏I�����

int JumpPower = 0;				//�W�����v�X�s�[�h������
int Jumpflag = TRUE;			//�W�����v�t���O
int WJumpflag = FALSE;			//�Q�i�W�����v�t���O
int WKeyflag = FALSE;			//W�L�[�𗣂��Ă��邩�ǂ����̃t���O
int Answer = 0;					//������X�^�[������ϐ�
int Toge = TOGE_MOVE;			//�g�Q����������
int TogeSpeed = TOGE_SPEED;		//�g�Q�̃X�s�[�h
int Togeflag = TRUE;			//�����g�Q�̐؂�Ԃ��̃t���O	
int TogeMove = 0;				//�g�Q�������������𑪂�ϐ�
int Cntm = 0;					//�����g�Q�̃J�E���^�[

IMAGE ImageTitle;		//�^�C�g����ʂ̔w�i�摜
IMAGE ImagePlay;		//�v���C��ʂ̔w�i�摜
IMAGE ImageTitleROGO;	//���S�̉摜
IMAGE ImageTitleCLEAR;	//�N���A�̉摜
IMAGE ImageTitleOVER;	//�Q�[���I�[�o�[�̉摜

IMAGE ImageSpace;		//�X�y�[�X�L�[�������Ă�������
IMAGE ImageEnter;		//�G���^�[�L�[�������Ă�������

CHARA player;			//�Q�[���̃L����

MUSIC BGM_START;		//�^�C�g�����BGM
MUSIC BGM_PLAY;			//�v���C���BGM
MUSIC BGM_CLEAR;		//�N���A���BGM
MUSIC BGM_OVER;			//�Q�[���I�[�o�[���BGM
MUSIC BGM_KETTEI;		//����SE
MUSIC BGM_JUMP1;		//�W�����vSE
MUSIC BGM_JUMP2;		//�j�i�W�����vSE
MUSIC BGM_STAR;			//�X�^�[SE

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 0
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 1
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 2
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 3
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 4
		b,t,t,t,h1,t,t,h2,t,t,h3,t,t,t,t,b,	// 5
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 6
		b,s,t,t,t,t,t,t,t,t,t,t,t,t,g,b,	// 7
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 8
};	//�Q�[���̃}�b�v

GAME_MAP_KIND mapData2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 0
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 1
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 2
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 3
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 4
		b,t,t,t,h1,t,t,b,t,t,b,t,t,t,t,b,	// 5
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 6
		b,s,t,t,t,t,t,t,t,t,t,t,t,t,g,b,	// 7
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 8
};	//�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapData2Init[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�̏ꏊ���Ǘ�
MAP map2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };

//�}�b�v�̓����蔻��
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�S�[���̓����蔻��
RECT goalColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MY_CIRCLE en;

//########## �v���g�^�C�v�錾 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int);				//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int, int);		//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����

BOOL MY_FONT_INSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);			//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);			//�t�H���g���폜����

VOID MY_START(VOID);				//�X�^�[�g���
VOID MY_START_PROC(VOID);			//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);			//�X�^�[�g��ʂ̕`��

VOID MY_PLAY_INIT(VOID);			//�v���C��ʏ�����
VOID MY_PLAY(VOID);					//�v���C���
VOID MY_PLAY_PROC(VOID);			//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);			//�v���C��ʂ̕`��

VOID MY_PLAY_PROC_STAGE2(VOID);			//�v���C��ʂ̏���
VOID MY_PLAY_DRAW_STAGE2(VOID);			//�v���C��ʂ̕`��

VOID MY_END(VOID);					//�G���h���
VOID MY_END_PROC(VOID);				//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);				//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);			//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);			//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);			//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);			//���y���܂Ƃ߂č폜����֐�

VOID PLAYER_JUMP(VOID);				//�v���C���[�̓����̏����̊֐�

BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT);	//�S�[���ƃv���C���[�̓����蔻�������֐�
int MY_CHECK_BLOCK_PLAYER_COLL(RECT);	//�u���b�N�ƃv���C���[�̓����蔻�������֐�
int MY_CHECK_STAR_PLAYER_COLL(RECT);	//�X�^�[�ƃv���C���[�̓����蔻�������֐�
int MY_CHECK_TOGE_PLAYER_COLL(RECT);	//�g�Q�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//�̈�̓����蔻�������֐�

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(444);								//�A�C�R���t�@�C����Ǎ�
	SetWindowUserCloseEnableFlag(FALSE);				//����{�^���ŁA����ɃE�B���h�E�����Ȃ��悤�ɂ���

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	GameStage = GAME_STAGE_2;

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�v���C���[�̍ŏ��̈ʒu���A�X�^�[�g�ʒu�ɂ���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�X�^�[�g�ʒu��T��
			if (mapData[tate][yoko] == s)
			{
				//�X�^�[�g�ʒu���v�Z
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//���SX���W���擾
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//���SY���W���擾
				break;
			}
		}
		//�X�^�[�g�����܂��Ă���΁A���[�v�I��
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}

	//�X�^�[�g�����܂��Ă��Ȃ����
	if (startPt.x == -1 && startPt.y == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//m(�����g�Q)���J�E���g����
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			if (map[tate][yoko].kind == m)
			{
				Cntm++;
			}
		}
	}

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		//��ʂ̕���{�^���������ꂽ�Ƃ�
		if (GetWindowUserCloseFlag(TRUE))
		{
			//�I���_�C�A���O��\��
			int Ret = MessageBox(GetMainWindowHandle(), MSG_CLOSE_CAPTION, MSG_CLOSE_TITLE, MB_YESNO | MB_ICONASTERISK);
			if (Ret == IDYES) { break; }	//YES�Ȃ�A�Q�[���𒆒f����
		}

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	//�t�H���g�n���h����j��
	MY_FONT_DELETE();

	//�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	MY_FONT_UNINSTALL_ONCE();

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{

	//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����
	char TempKey[KEY_CODE_KIND];

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�GAME_FPS
	}
}

//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
//���@���Fint�F�L�[�����������鎞��
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}


//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//�t�H���g��ǂݍ��ފ֐�
//���@���Fconst char *�F�ǂݍ��ރt�H���g�̖��O
//���@���Fint�@�F�t�H���g�̑傫��
//���@���Fint�@�F�t�H���g�̑���
//���@���Fint�@�F�t�H���g�̃^�C�v
//�߂�l�FBOOL �F�G���[����FALSE / ���펞��TRUE
BOOL MY_FONT_CREATE(VOID)
{
	return TRUE;
}

//�t�H���g���폜����֐�
VOID MY_FONT_DELETE(VOID)
{

	return;
}

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM_START.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 80 / 100, BGM_START.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_START.handle, DX_PLAYTYPE_LOOP);
	}

	//�X�y�[�X�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		MY_PLAY_INIT();	//�Q�[��������

		if (CheckSoundMem(BGM_START.handle) != 0)
		{
			StopSoundMem(BGM_START.handle);	//BGM���~�߂�
		}

		ChangeVolumeSoundMem(255 * 30 / 100, BGM_KETTEI.handle);	//30%�̉��ʂɂ���
		PlaySoundMem(BGM_KETTEI.handle, DX_PLAYTYPE_BACK);

		//�Q�[���̏I����Ԃ�����������
		GameEndKind = GAME_END_OVER;

		GameStage = GAME_STAGE_2;

		//�Q�[���̃V�[�����v���C��ʂɂ���
		GameScene = GAME_SCENE_PLAY;

	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	//�X�^�[�g��ʔw�i��`�悷��
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);

	//�^�C�g���w�i��`�悷��
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);

	//PRESS OF SPACEKEY��`�悷��
	DrawGraph(ImageSpace.x, ImageSpace.y, ImageSpace.handle, TRUE);	//PRESS OF SPACEKEY�̕`��

	return;
}

//�v���C��ʏ�����
VOID MY_PLAY_INIT(VOID)
{

	//�v���C���[���X�^�[�g�ʒu�ɕ`��
	player.image.x = startPt.x - 30;
	player.CenterX = startPt.x;
	player.image.y = startPt.y - 40;
	player.CenterY = startPt.y - 10;

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			//�X�^�[�����ɖ߂�
			if (map[tate][yoko].kind == m1)
			{
				map[tate][yoko].kind = h1;
			}
			if (map[tate][yoko].kind == m2)
			{
				map[tate][yoko].kind = h2;
			}

			if (map[tate][yoko].kind == m3)
			{
				map[tate][yoko].kind = h3;
			}

			//�����g�Q�̈ʒu��������
			if (map[tate][yoko].kind == m)
			{

				if (TogeMove < 0)
				{
					map[tate][yoko].x -= TogeMove / Cntm;
					mapColl[tate][yoko].left -= TogeMove / Cntm;
					mapColl[tate][yoko].right -= TogeMove / Cntm;
				}

				if (TogeMove > 0)
				{
					map[tate][yoko].x -= TogeMove / Cntm;
					mapColl[tate][yoko].left -= TogeMove / Cntm;
					mapColl[tate][yoko].right -= TogeMove / Cntm;
				}
			}

		}
	}

	Answer = 0;			//�����Ă���񓚂�����
	Togeflag = TRUE;	//�g�Q���E�ɓ����悤�ɂ���
	TogeMove = 0;		//TogeMove��������

	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	switch (GameStage)
	{
	case GAME_STAGE_1:
		MY_PLAY_PROC();	//�v���C��ʂ̏���
		MY_PLAY_DRAW();	//�v���C��ʂ̕`��
		break;
	case GAME_STAGE_2:
		MY_PLAY_PROC_STAGE2();	//�v���C��ʂ̏���
		MY_PLAY_DRAW_STAGE2();	//�v���C��ʂ̕`��
		break;
	}
	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM_PLAY.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 30 / 100, BGM_PLAY.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_PLAY.handle, DX_PLAYTYPE_LOOP);

	}

	//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	PLAYER_JUMP();		//�v���C���[�̓����̏���

	//�����蔻��
	player.coll.left = player.CenterX - mapChip.width / 2;
	player.coll.top = player.CenterY - mapChip.height / 2;
	player.coll.right = player.CenterX + mapChip.width / 2 - 10;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 10;

	//�v���C���[�ƃu���b�N���������Ă����璼�O�̈ʒu�֖߂�
	if (MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		player.image.x = player.collBeforePt.x - 30;
		player.image.y = player.collBeforePt.y - 30;
		JumpPower = 0;
		WJumpflag = FALSE;	//��i�W�����v�t���O��FALSE
		WKeyflag = FALSE;	//W�L�[�t���O��FALSE
	}

	//�v���C���[�ƃX�^�[���������Ă�����}�b�v��̂��ׂẴX�^�[������
	if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
	{

		//�X�^�[SE�𗬂�
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_STAR.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_STAR.handle, DX_PLAYTYPE_BACK);

		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//�X�^�[1�ɓ������Ă�����Answer��1������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1)
				{
					Answer = 1;
				}

				//�X�^�[2�ɓ������Ă�����Answer��2������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2)
				{
					Answer = 2;
				}

				//�X�^�[3�ɓ������Ă�����Answer��3������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
				{
					Answer = 3;
				}

				//�X�^�[1������
				if (map[tate][yoko].kind == h1)
				{
					map[tate][yoko].kind = m1;
				}

				//�X�^�[2������
				if (map[tate][yoko].kind == h2)
				{
					map[tate][yoko].kind = m2;
				}

				//�X�^�[3������
				if (map[tate][yoko].kind == h3)
				{
					map[tate][yoko].kind = m3;
				}

			}
		}
	}

	//�����g�Q�̏���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (map[tate][yoko].kind == m)
			{
				//Toge�̐��������ꂽ��Togeflag��FALSE�ɂ���
				if (TogeMove == Toge * 60 * Cntm)
				{
					Togeflag = FALSE;
				}

				//Toge�̐��������ꂽ��Togeflag��TRUE�ɂ���
				if (TogeMove == Toge * -60 * Cntm)
				{
					Togeflag = TRUE;
				}

				//Togeflag��TRUE�Ȃ�E�ɓ���
				if (Togeflag == TRUE)
				{
					map[tate][yoko].x += TogeSpeed;
					mapColl[tate][yoko].left += TogeSpeed;
					mapColl[tate][yoko].right += TogeSpeed;
					TogeMove += TogeSpeed;
				}

				//Togeflag��FALSE�Ȃ�E�ɓ���
				if (Togeflag == FALSE)
				{
					map[tate][yoko].x -= TogeSpeed;
					mapColl[tate][yoko].left -= TogeSpeed;
					mapColl[tate][yoko].right -= TogeSpeed;
					TogeMove -= TogeSpeed;
				}
			}
		}
	}

	//�v���C���[�ƃg�Q���������Ă�����Q�[���I�[�o�[��ʂɑJ��
	if (MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 1 || MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 2)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGM���~�߂�
		}

		GameEndKind = GAME_END_OVER;	//�Q�[���I�[�o�[�I

		//�Q�[���̃V�[�����G���h��ʂɂ���
		GameScene = GAME_SCENE_END;

	}

	//�v���C���[�ƃS�[�����������Ă�����Q�[���N���A��ʂɑJ��
	if (MY_CHECK_GOAL_PLAYER_COLL(player.coll) == TRUE)
	{

		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGM���~�߂�
		}

		if (Answer == 1)
		{
			GameEndKind = GAME_END_CLEAR;	//�Q�[���N���A�I
		}

		else
		{
			GameEndKind = GAME_END_OVER;
		}

		//�Q�[���̃V�[�����G���h��ʂɂ���
		GameScene = GAME_SCENE_END;

	}

	return;

}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC_STAGE2(VOID)
{

	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM_PLAY.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 30 / 100, BGM_PLAY.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_PLAY.handle, DX_PLAYTYPE_LOOP);

	}

	//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	PLAYER_JUMP();		//�v���C���[�̓����̏���

	//�����蔻��
	player.coll.left = player.CenterX - mapChip.width / 2;
	player.coll.top = player.CenterY - mapChip.height / 2;
	player.coll.right = player.CenterX + mapChip.width / 2 - 10;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 10;

	//�v���C���[�ƃu���b�N���������Ă����璼�O�̈ʒu�֖߂�
	if (MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		player.image.x = player.collBeforePt.x - 30;
		player.image.y = player.collBeforePt.y - 30;
		JumpPower = 0;
		WJumpflag = FALSE;	//��i�W�����v�t���O��FALSE
		WKeyflag = FALSE;	//W�L�[�t���O��FALSE
	}

	//�v���C���[�ƃX�^�[���������Ă�����}�b�v��̂��ׂẴX�^�[������
	if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
	{

		//�X�^�[SE�𗬂�
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_STAR.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_STAR.handle, DX_PLAYTYPE_BACK);

		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//�X�^�[1�ɓ������Ă�����Answer��1������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1)
				{
					Answer = 1;
				}

				//�X�^�[2�ɓ������Ă�����Answer��2������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2)
				{
					Answer = 2;
				}

				//�X�^�[3�ɓ������Ă�����Answer��3������
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
				{
					Answer = 3;
				}

				//�X�^�[1������
				if (map2[tate][yoko].kind == h1)
				{
					map2[tate][yoko].kind = m1;
				}

				//�X�^�[2������
				if (map2[tate][yoko].kind == h2)
				{
					map2[tate][yoko].kind = m2;
				}

				//�X�^�[3������
				if (map2[tate][yoko].kind == h3)
				{
					map2[tate][yoko].kind = m3;
				}

			}
		}
	}

	//�����g�Q�̏���
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (map2[tate][yoko].kind == m)
			{
				//Toge�̐��������ꂽ��Togeflag��FALSE�ɂ���
				if (TogeMove == Toge * 60 * Cntm)
				{
					Togeflag = FALSE;
				}

				//Toge�̐��������ꂽ��Togeflag��TRUE�ɂ���
				if (TogeMove == Toge * -60 * Cntm)
				{
					Togeflag = TRUE;
				}

				//Togeflag��TRUE�Ȃ�E�ɓ���
				if (Togeflag == TRUE)
				{
					map2[tate][yoko].x += TogeSpeed;
					mapColl[tate][yoko].left += TogeSpeed;
					mapColl[tate][yoko].right += TogeSpeed;
					TogeMove += TogeSpeed;
				}

				//Togeflag��FALSE�Ȃ�E�ɓ���
				if (Togeflag == FALSE)
				{
					map2[tate][yoko].x -= TogeSpeed;
					mapColl[tate][yoko].left -= TogeSpeed;
					mapColl[tate][yoko].right -= TogeSpeed;
					TogeMove -= TogeSpeed;
				}
			}
		}
	}

	//�v���C���[�ƃg�Q���������Ă�����Q�[���I�[�o�[��ʂɑJ��
	if (MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 1 || MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 2)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGM���~�߂�
		}

		GameEndKind = GAME_END_OVER;	//�Q�[���I�[�o�[�I

		//�Q�[���̃V�[�����G���h��ʂɂ���
		GameScene = GAME_SCENE_END;

	}

	//�v���C���[�ƃS�[�����������Ă�����Q�[���N���A��ʂɑJ��
	if (MY_CHECK_GOAL_PLAYER_COLL(player.coll) == TRUE)
	{

		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGM���~�߂�
		}

		if (Answer == 1)
		{
			GameEndKind = GAME_END_CLEAR;	//�Q�[���N���A�I
		}

		else
		{
			GameEndKind = GAME_END_OVER;
		}

		//�Q�[���̃V�[�����G���h��ʂɂ���
		GameScene = GAME_SCENE_END;

	}

	return;

}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{

	//�v���C��ʔw�i��`�悷��
	DrawGraph(ImagePlay.x, ImagePlay.y, ImagePlay.handle, TRUE);

	//�v���C���[��`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//�}�b�v�`�b�v��`�悷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW_STAGE2(VOID)
{

	//�v���C��ʔw�i��`�悷��
	DrawGraph(ImagePlay.x, ImagePlay.y, ImagePlay.handle, TRUE);

	//�v���C���[��`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//�}�b�v�`�b�v��`�悷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map2[tate][yoko].kind],
				TRUE);
		}
	}

	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��

	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	switch (GameEndKind)
	{
	case GAME_END_CLEAR:
		//�Q�[���N���A�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_CLEAR.handle) == 0)
		{

			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_CLEAR.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_CLEAR.handle, DX_PLAYTYPE_LOOP);
		}
		break;

	case GAME_END_OVER:
		//�Q�[���I�[�o�[�̂Ƃ�

		//BGM������Ă��Ȃ��Ȃ�
		if (CheckSoundMem(BGM_OVER.handle) == 0)
		{

			//BGM�̉��ʂ�������
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_OVER.handle);	//50%�̉��ʂɂ���
			PlaySoundMem(BGM_OVER.handle, DX_PLAYTYPE_LOOP);
		}
		break;
	}

	//�G���^�[�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_CLEAR.handle) != 0)
		{
			StopSoundMem(BGM_CLEAR.handle);	//BGM���~�߂�
		}

		if (CheckSoundMem(BGM_OVER.handle) != 0)
		{
			StopSoundMem(BGM_OVER.handle);	//BGM���~�߂�
		}

		//�X�^�[�g��ʂɂ���
		GameScene = GAME_SCENE_START;

	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();	//�v���C��ʂ�`��

	//�Q�[���̏I����Ԃɂ��A�`���ς���
	switch (GameEndKind)
	{
	case GAME_END_CLEAR:
		//�R���v���[�g�̂Ƃ�

			//�R���v���[�g�̕`��
		DrawGraph(ImageTitleCLEAR.x, ImageTitleCLEAR.y, ImageTitleCLEAR.handle, TRUE);
		break;

	case GAME_END_OVER:
		//�t�H�[���g�̂Ƃ�

			//�t�H�[���g�̕`��
		DrawGraph(ImageTitleOVER.x, ImageTitleOVER.y, ImageTitleOVER.handle, TRUE);
		break;
	}

	DrawGraph(ImageEnter.x, ImageEnter.y, ImageEnter.handle, TRUE);	//PRESS OF ENTERKEY�̕`��
	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�w�i�摜
	strcpy_s(ImageTitle.path, IMG_SOUGEN);		//�p�X�̐ݒ�
	ImageTitle.handle = LoadGraph(ImageTitle.path);	//�ǂݍ���
	if (ImageTitle.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_SOUGEN, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);	//�摜�̕��ƍ������擾
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;		//���E��������
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;	//�㉺��������

	//�w�i�摜
	strcpy_s(ImagePlay.path, IMG_SORA);		//�p�X�̐ݒ�
	ImagePlay.handle = LoadGraph(ImagePlay.path);	//�ǂݍ���
	if (ImagePlay.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_SORA, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePlay.handle, &ImagePlay.width, &ImagePlay.height);	//�摜�̕��ƍ������擾
	ImagePlay.x = GAME_WIDTH / 2 - ImagePlay.width / 2;		//���E��������
	ImagePlay.y = GAME_HEIGHT / 2 - ImagePlay.height / 2;	//�㉺��������

	//�^�C�g�����S
	strcpy_s(ImageTitleROGO.path, IMG_LOGO);						//�p�X�̐ݒ�
	ImageTitleROGO.handle = LoadGraph(ImageTitleROGO.path);				//�ǂݍ���
	if (ImageTitleROGO.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_LOGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.handle, &ImageTitleROGO.width, &ImageTitleROGO.height);	//�摜�̕��ƍ������擾
	ImageTitleROGO.x = GAME_WIDTH / 2 - ImageTitleROGO.width / 2;		//���E��������
	ImageTitleROGO.y = GAME_HEIGHT / 2 - ImageTitleROGO.height / 2;	//�㉺��������

	//�G���h���(GAME CLEAR)�̉摜
	strcpy_s(ImageTitleCLEAR.path, IMG_LOGO_CLEAR);						//�p�X�̐ݒ�
	ImageTitleCLEAR.handle = LoadGraph(ImageTitleCLEAR.path);			//�ǂݍ���
	if (ImageTitleCLEAR.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_LOGO_CLEAR, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleCLEAR.handle, &ImageTitleCLEAR.width, &ImageTitleCLEAR.height);	//�摜�̕��ƍ������擾
	ImageTitleCLEAR.x = GAME_WIDTH / 2 - ImageTitleCLEAR.width / 2;		//���E��������
	ImageTitleCLEAR.y = GAME_HEIGHT / 2 - ImageTitleCLEAR.height / 2;	//�㉺��������

	//�G���h���(GAME OVER)�̉摜
	strcpy_s(ImageTitleOVER.path, IMG_LOGO_OVER);						//�p�X�̐ݒ�
	ImageTitleOVER.handle = LoadGraph(ImageTitleOVER.path);				//�ǂݍ���
	if (ImageTitleOVER.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_LOGO_OVER, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleOVER.handle, &ImageTitleOVER.width, &ImageTitleOVER.height);	//�摜�̕��ƍ������擾
	ImageTitleOVER.x = GAME_WIDTH / 2 - ImageTitleOVER.width / 2;		//���E��������
	ImageTitleOVER.y = GAME_HEIGHT / 2 - ImageTitleOVER.height / 2;	//�㉺��������

	//PRESS OF SPACEKEY!!!�̉摜
	strcpy_s(ImageSpace.path, IMG_SPACE);						//�p�X�̐ݒ�
	ImageSpace.handle = LoadGraph(ImageSpace.path);				//�ǂݍ���
	if (ImageSpace.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_SPACE, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageSpace.handle, &ImageSpace.width, &ImageSpace.height);	//�摜�̕��ƍ������擾
	ImageSpace.x = GAME_WIDTH / 2 - ImageSpace.width / 2;		//���E��������
	ImageSpace.y = GAME_HEIGHT / 2 + ImageSpace.height + 30;	//�㉺��������

	//PRESS OF SPACEKEY!!!�̉摜
	strcpy_s(ImageEnter.path, IMG_ENTER);						//�p�X�̐ݒ�
	ImageEnter.handle = LoadGraph(ImageEnter.path);				//�ǂݍ���
	if (ImageEnter.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_ENTER, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEnter.handle, &ImageEnter.width, &ImageEnter.height);	//�摜�̕��ƍ������擾
	ImageEnter.x = GAME_WIDTH / 2 - ImageEnter.width / 2;		//���E��������
	ImageEnter.y = GAME_HEIGHT / 2 + ImageEnter.height + 30;	//�㉺��������

	//�v���C���[�̉摜
	strcpy_s(player.image.path, IMG_MARU);		//�p�X�̐ݒ�
	player.image.handle = LoadGraph(player.image.path);	//�ǂݍ���
	if (player.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_MARU, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//���E��������
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//�㉺��������
	player.speed = CHARA_SPEED_HIGH;								//�X�s�[�h��ݒ�

	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//�}�b�v�`�b�v�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�}�b�v�`�b�v�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊����镝�ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�f�[�^�������p�ɏ����R�s�[
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//�}�b�v�̎�ނ��R�s�[
			map[tate][yoko].kind = mapData[tate][yoko];

			//�}�b�v�̕��ƍ������R�s�[
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//�}�b�v�̍��W��ݒ�
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;

		}
	}

	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//�S�[���̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�S�[���̓����蔻���ݒ�
			goalColl[tate][yoko].left = (yoko + 0) * mapChip.width + 10;
			goalColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			goalColl[tate][yoko].right = (yoko + 1) * mapChip.width - 10;
			goalColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}


	return TRUE;
}

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageTitle.handle);
	DeleteGraph(ImagePlay.handle);
	DeleteGraph(ImageTitleROGO.handle);
	DeleteGraph(ImageTitleCLEAR.handle);
	DeleteGraph(ImageTitleOVER.handle);
	DeleteGraph(ImageSpace.handle);
	DeleteGraph(ImageEnter.handle);

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//���y���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_MUSIC(VOID)
{
	//�X�^�[�g���BGM�̓ǂݍ���
	strcpy_s(BGM_START.path, MUSIC_START_PATH);		//�p�X�̐ݒ�
	BGM_START.handle = LoadSoundMem(BGM_START.path);	//�ǂݍ���
	if (BGM_START.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�v���C���BGM�̓ǂݍ���
	strcpy_s(BGM_PLAY.path, MUSIC_PLAY_PATH);		//�p�X�̐ݒ�
	BGM_PLAY.handle = LoadSoundMem(BGM_PLAY.path);	//�ǂݍ���
	if (BGM_PLAY.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�N���A���BGM�̓ǂݍ���
	strcpy_s(BGM_CLEAR.path, MUSIC_CLEAR_PATH);			//�p�X�̐ݒ�
	BGM_CLEAR.handle = LoadSoundMem(BGM_CLEAR.path);	//�ǂݍ���
	if (BGM_CLEAR.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_CLEAR_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�Q�[���I�[�o�[���BGM�̓ǂݍ���
	strcpy_s(BGM_OVER.path, MUSIC_OVER_PATH);			//�p�X�̐ݒ�
	BGM_OVER.handle = LoadSoundMem(BGM_OVER.path);	//�ǂݍ���
	if (BGM_OVER.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_OVER_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//����SE�̓ǂݍ���
	strcpy_s(BGM_KETTEI.path, MUSIC_KETTEI_PATH);		//�p�X�̐ݒ�
	BGM_KETTEI.handle = LoadSoundMem(BGM_KETTEI.path);	//�ǂݍ���
	if (BGM_KETTEI.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_KETTEI_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�W�����vSE�̓ǂݍ���
	strcpy_s(BGM_JUMP1.path, MUSIC_JUMP1_PATH);			//�p�X�̐ݒ�
	BGM_JUMP1.handle = LoadSoundMem(BGM_JUMP1.path);	//�ǂݍ���
	if (BGM_JUMP1.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_JUMP1_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//��i�W�����vSE�̓ǂݍ���
	strcpy_s(BGM_JUMP2.path, MUSIC_JUMP2_PATH);		    //�p�X�̐ݒ�
	BGM_JUMP2.handle = LoadSoundMem(BGM_JUMP2.path);	//�ǂݍ���
	if (BGM_JUMP2.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_JUMP2_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�X�^�[SE�̓ǂݍ���
	strcpy_s(BGM_STAR.path, MUSIC_STAR_PATH);		    //�p�X�̐ݒ�
	BGM_STAR.handle = LoadSoundMem(BGM_STAR.path);	//�ǂݍ���
	if (BGM_STAR.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_STAR_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_START.handle);
	DeleteSoundMem(BGM_PLAY.handle);
	DeleteSoundMem(BGM_CLEAR.handle);
	DeleteSoundMem(BGM_OVER.handle);
	DeleteSoundMem(BGM_KETTEI.handle);
	DeleteSoundMem(BGM_JUMP1.handle);
	DeleteSoundMem(BGM_JUMP2.handle);
	DeleteSoundMem(BGM_STAR.handle);

	return;
}

//�v���C���[�ƃS�[���̓����蔻�������֐�
BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT player)
{
	//�}�b�v�`�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃS�[�����������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, goalColl[tate][yoko]) == TRUE)
			{
				//�S�[���̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == g) { return TRUE; }
			}

		}
	}

	return FALSE;
}

//�v���C���[�ƃu���b�N�̓����蔻�������֐�
int MY_CHECK_BLOCK_PLAYER_COLL(RECT player)
{
	//�}�b�v�`�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃu���b�N���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�u���b�N�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == b) { return 1; }

				//�u���b�N�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == a) { return 2; }

			}
		}
	}

	return FALSE;

}

//�v���C���[�ƃX�^�[�̓����蔻�������֐�
int MY_CHECK_STAR_PLAYER_COLL(RECT player)
{
	//�}�b�v�`�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃX�^�[���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�X�^�[�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == h1) { return 1; }

				//�X�^�[�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == h2) { return 2; }

				//�X�^�[�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == h3) { return 3; }

			}
		}
	}

	return FALSE;

}

//�v���C���[�ƃg�Q�̓����蔻�������֐�
int MY_CHECK_TOGE_PLAYER_COLL(RECT player)
{
	//�}�b�v�`�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃg�Q���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�g�Q�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == n) { return 1; }

				//�g�Q�̂Ƃ��́ATRUE��Ԃ�
				if (map[tate][yoko].kind == m) { return 2; }

			}
		}
	}

	return FALSE;

}

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)

	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
}

//�v���C���[�̓����̏����̊֐�
VOID PLAYER_JUMP(VOID)
{

	//�W�����v�t���O��TRUE��W�L�[�������Ă��ăv���C���[�ƃu���b�N���������Ă�����W�����v
	if (Jumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		//�W�����vSE�𗬂�
		ChangeVolumeSoundMem(255 * 60 / 100, BGM_JUMP1.handle);	//80%�̉��ʂɂ���
		PlaySoundMem(BGM_JUMP1.handle, DX_PLAYTYPE_BACK);

		JumpPower = 13;			//��1�u���b�N���̃W�����v
		Jumpflag = FALSE;		//�W�����v�t���O��FALSE�ɂ���
		WKeyflag = TRUE;		//W�L�[�t���O��TRUE�ɂ���
	}

	//��i�W�����v�t���O��TRUE��W�L�[�������Ă�����󒆃W�����v
	if (WJumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE)
	{
		//��i�W�����vSE�𗬂�
		ChangeVolumeSoundMem(255 * 60 / 100, BGM_JUMP2.handle);	//80%�̉��ʂɂ���
		PlaySoundMem(BGM_JUMP2.handle, DX_PLAYTYPE_BACK);

		JumpPower = 13;			//�Q�u���b�N���̃W�����v
		WJumpflag = FALSE;		//��i�W�����v�t���O��FALSE�ɂ���
		WKeyflag = FALSE;		//W�L�[�t���O��TRUE�ɂ���
	}

	//W�L�[�𗣂��ăv���C���[���n�ʂɂ���
	if (CheckHitKey(KEY_INPUT_W) == FALSE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		Jumpflag = TRUE;		//�W�����v�t���O��TRUE�ɂ��A�W�����v���ł���悤�ɂȂ�
	}

	//W�L�[�t���O��TRUE����W�L�[�𗣂���
	if (WKeyflag == TRUE && CheckHitKey(KEY_INPUT_W) == FALSE)
	{
		WJumpflag = TRUE;		//��i�W�����v�t���O��TRUE�ɂ��A��i�W�����v���ł���悤�ɂȂ�
	}

	// ��������
	player.CenterY -= JumpPower;
	player.image.y -= JumpPower;

	// ���������x��������
	JumpPower -= 1;

	//D�L�[�ŉE�֐i��
	if (CheckHitKey(KEY_INPUT_D) == TRUE)
	{
		player.image.x += player.speed;
		player.CenterX += player.speed;
	}

	//A�L�[�ō��֐i��
	if (CheckHitKey(KEY_INPUT_A) == TRUE)
	{
		player.image.x -= player.speed;
		player.CenterX -= player.speed;
	}

}