//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"

//########## �}�N����` ##########
#define GAME_WIDTH			960	//��ʂ̉��̑傫��
#define GAME_HEIGHT			540	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0					//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"		//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60	//FPS�̐��l	

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE	129	//0x0000�`0x0080�܂�

//�L�[�{�[�h�̎��
#define KEY_CODE_KIND		256	//256���

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

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

#define IMG_SOUGEN				TEXT(".\\IMAGE\\sougen.png")		//�^�C�g����ʂ̔w�i
#define IMG_SORA				TEXT(".\\IMAGE\\sora.png")			//�v���C��ʂ̔w�i
#define IMG_MARU				TEXT(".\\IMAGE\\player.png")		//�v���C���[�̉摜
#define IMG_LOGO				TEXT(".\\IMAGE\\ParQuiz.png")			//���S�̉摜
#define IMG_LOGO_END			TEXT(".\\IMAGE\\logo_end.png")		//�G���h�̉摜
#define IMG_SPACE				TEXT(".\\IMAGE\\pressofspace.png")		//PRESS OF SPACEKEY�̉摜
#define IMG_ENTER				TEXT(".\\IMAGE\\pressofenter.png")		//PRESS OF ENTER�̉摜

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip3.png")		//�}�b�v�̉摜

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
#define MUSIC_END_PATH			TEXT(".\\MUSIC\\3.End.mp3")		//�G���h���BGM
#define MUSIC_KETTEI_PATH		TEXT(".\\MUSIC\\Kettei.mp3")	//������ʉ�
#define MUSIC_JANP_PATH			TEXT(".\\MUSIC\\Janp.mp3")		//�W�����v���ʉ�

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	b = 1,	//�u���b�N
	g = 2,	//�S�[��
	h = 3,	//�X�^�[
	d = 4,	//�g�Q(�_���[�W��d)
	t = 5,	//�ʘH
	s = 6	//�X�^�[�g
};	//�}�b�v�̎��

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 7,

};	//�L�����N�^�[�̃X�s�[�h

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

//########## �O���[�o���ϐ� ##########
//FPS�֘A
int StartTimeFps;				//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς����T���v����
int JumpPower = 0;				//�W�����v�X�s�[�h������
int Jumpflag = TRUE;			//�W�����v�t���O
int WJumpflag = FALSE;			//�Q�i�W�����v�t���O
int WKeyflag = FALSE;			//W�L�[�𗣂��Ă��邩�ǂ����̃t���O

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[KEY_CODE_KIND] = { '\0' };		//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };	//���ׂẴL�[�̏��(���O)������

//�}�E�X�̍��W���擾
MOUSE mouse;

//�Q�[���֘A
int GameScene;			//�Q�[���V�[�����Ǘ�

IMAGE ImageTitle;		//�^�C�g����ʂ̔w�i�摜
IMAGE ImagePlay;		//�v���C��ʂ̔w�i�摜
IMAGE ImageTitleROGO;	//���S�̉摜
IMAGE ImageTitleEND;	//�N���A�̉摜

IMAGE ImageSpace;		//�X�y�[�X�L�[�������Ă�������
IMAGE ImageEnter;		//�G���^�[�L�[�������Ă�������

CHARA player;			//�Q�[���̃L����

MUSIC BGM_START;		//�^�C�g�����BGM
MUSIC BGM_PLAY;			//�v���C���BGM
MUSIC BGM_END;			//�G���h���BGM
MUSIC BGM_KETTEI;		//����SE

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 0
		b,h,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 1
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 2
		b,t,t,t,t,t,t,t,t,d,t,t,t,t,t,b,	// 3
		b,t,t,t,h,t,t,t,b,b,b,t,t,t,t,b,	// 4
		b,t,t,t,t,d,t,t,t,t,t,t,b,t,t,b,	// 5
		b,t,t,t,b,b,b,t,t,t,t,t,b,t,t,b,	// 6
		b,s,t,t,t,t,t,t,t,t,t,h,b,t,g,b,	// 7
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 8
};	//�Q�[���̃}�b�v

//�Q�[���}�b�v�̏�����
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

//�}�b�v�̏ꏊ���Ǘ�
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�X�^�[�g�̈ʒu
iPOINT startPt{ -1,-1 };

//�}�b�v�̓����蔻��
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//�S�[���̓����蔻��
RECT goalColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

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

VOID MY_END(VOID);					//�G���h���
VOID MY_END_PROC(VOID);				//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);				//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);			//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);			//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);			//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);			//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT);	//�S�[���ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_BLOCK_PLAYER_COLL(RECT);	//�u���b�N�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_STAR_PLAYER_COLL(RECT);	//�X�^�[�ƃv���C���[�̓����蔻�������֐�
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
	SetWindowIconID(IDI_ICON1);							//�A�C�R���t�@�C����Ǎ�
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
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
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

	//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(BGM_START.handle) != 0)
		{
			StopSoundMem(BGM_START.handle);	//BGM���~�߂�
		}

		ChangeVolumeSoundMem(255 * 30 / 100, BGM_KETTEI.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_KETTEI.handle, DX_PLAYTYPE_BACK);

		MY_PLAY_INIT();	//�Q�[��������

		player.image.x = startPt.x - 30;
		player.CenterX = startPt.x;
		player.image.y = startPt.y - 40;
		player.CenterY = startPt.y - 10;

		//�Q�[���̃V�[�����v���C��ʂɂ���
		GameScene = GAME_SCENE_PLAY;

		return;
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
	// ��ʂ�����������
	ClearDrawScreen();

	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

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

	/*�������������������������������W�����v�̏���������������������������������*/

	//�W�����v�t���O��TRUE��W�L�[�������Ă��ăv���C���[�ƃu���b�N���������Ă�����W�����v
	if (Jumpflag==TRUE && CheckHitKey(KEY_INPUT_W) == TRUE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
	{
		JumpPower = 11;			//��1�u���b�N���̃W�����v
		Jumpflag = FALSE;		//�W�����v�t���O��FALSE�ɂ���
		WKeyflag = TRUE;		//W�L�[�t���O��TRUE�ɂ���
	}

	//��i�W�����v�t���O��TRUE��W�L�[�������Ă�����󒆃W�����v
	if (WJumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE)
	{
		JumpPower = 11;			//�Q�u���b�N���̃W�����v
		WJumpflag = FALSE;		//��i�W�����v�t���O��FALSE�ɂ���
		WKeyflag = FALSE;		//W�L�[�t���O��TRUE�ɂ���
	}

	//W�L�[�𗣂��ăv���C���[���n�ʂɂ���
	if (CheckHitKey(KEY_INPUT_W) == FALSE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
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

	/*�������������������������������W�����v�̏���������������������������������*/

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

	//�����蔻��
	player.coll.left = player.CenterX - mapChip.width / 2 + 1;
	player.coll.top = player.CenterY - mapChip.height / 2 + 1;
	player.coll.right = player.CenterX + mapChip.width / 2 - 1;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 1;

	//�v���C���[�ƃS�[�����������Ă�����
	if (MY_CHECK_GOAL_PLAYER_COLL(player.coll) == TRUE)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGM���~�߂�
		}

		//�Q�[���̃V�[�����G���h��ʂɂ���
		GameScene = GAME_SCENE_END;
	}

	//�v���C���[�ƃu���b�N���������Ă����璼�O�̈ʒu�֖߂�
	if (MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
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
	if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == TRUE)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//map[tate][yoko].kind = t;
				//map[tate][yoko].x = 0;
				//map[tate][yoko].y = 0;
				//map[tate][yoko].width = 0;
				//map[tate][yoko].height = 0;
			}
		}
	}

	//�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	// ��ʂ�����������
	ClearDrawScreen();

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{

	//�v���C��ʔw�i��`�悷��
	DrawGraph(ImagePlay.x, ImagePlay.y, ImagePlay.handle, TRUE);

	//�v���C���[��`�悷��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v��`��
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	//�����蔻��̕`��i�f�o�b�O�p�j
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData[tate][yoko] == b)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}

			//�S�[���Ȃ��
			if (mapData[tate][yoko] == g)
			{
				DrawBox(goalColl[tate][yoko].left, goalColl[tate][yoko].top, goalColl[tate][yoko].right, goalColl[tate][yoko].bottom, GetColor(0, 255,0), FALSE);
			}

			//�X�^�[�Ȃ��
			if (mapData[tate][yoko] == h)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 0, 255), FALSE);
			}

		}
	}

	//�v���[���[�����蔻��̕`��i�f�o�b�O�p�j
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);


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
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(BGM_END.handle) == 0)
	{
		//BGM�̉��ʂ�������
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_END.handle);	//50%�̉��ʂɂ���
		PlaySoundMem(BGM_END.handle, DX_PLAYTYPE_LOOP);
	}

	//�G���^�[�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_END.handle) != 0)
		{
			StopSoundMem(BGM_END.handle);	//BGM���~�߂�
		}

		//�X�^�[�g��ʂɂ���
		GameScene = GAME_SCENE_START;
	}

	// ��ʂ�����������
	ClearDrawScreen();

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();	//�v���C��ʂ�`��

	//GAME CLEAR!!!��`��
	DrawGraph(ImageTitleEND.x, ImageTitleEND.y, ImageTitleEND.handle, TRUE);

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
	strcpy_s(ImageTitleEND.path, IMG_LOGO_END);						//�p�X�̐ݒ�
	ImageTitleEND.handle = LoadGraph(ImageTitleEND.path);				//�ǂݍ���
	if (ImageTitleEND.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMG_LOGO_END, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleEND.handle, &ImageTitleEND.width, &ImageTitleEND.height);	//�摜�̕��ƍ������擾
	ImageTitleEND.x = GAME_WIDTH / 2 - ImageTitleEND.width / 2;		//���E��������
	ImageTitleEND.y = GAME_HEIGHT / 2 - ImageTitleEND.height / 2;	//�㉺��������

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
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��
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
	DeleteGraph(ImageTitleEND.handle);
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

	//�G���h���BGM�̓ǂݍ���
	strcpy_s(BGM_END.path, MUSIC_END_PATH);			//�p�X�̐ݒ�
	BGM_END.handle = LoadSoundMem(BGM_END.path);	//�ǂݍ���
	if (BGM_END.handle == -1)
	{
		//	�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), MUSIC_END_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
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

	return TRUE;
}

//���y���܂Ƃ߂č폜����֐�
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_START.handle);
	DeleteSoundMem(BGM_PLAY.handle);
	DeleteSoundMem(BGM_END.handle);
	DeleteSoundMem(BGM_KETTEI.handle);

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
BOOL MY_CHECK_BLOCK_PLAYER_COLL(RECT player)
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
				if (map[tate][yoko].kind == b) { return TRUE; }
			}
		}
	}

	return FALSE;

}

//�v���C���[�ƃX�^�[�̓����蔻�������֐�
BOOL MY_CHECK_STAR_PLAYER_COLL(RECT player)
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
				if (map[tate][yoko].kind == h) { return TRUE; }
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
