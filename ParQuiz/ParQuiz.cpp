//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

//########## マクロ定義 ##########
#define GAME_WIDTH			960	//画面の横の大きさ
#define GAME_HEIGHT			540	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0					//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"		//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

//マウスのボタン
#define MOUSE_BUTTON_CODE	129	//0x0000～0x0080まで

//キーボードの種類
#define KEY_CODE_KIND		256	//256種類

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//フォント
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")			//フォントの名前

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//閉じるボタンを押したとき
#define MSG_CLOSE_TITLE			TEXT("終了メッセージ")
#define MSG_CLOSE_CAPTION		TEXT("ゲームを終了しますか？")

#define GAME_MAP_TATE_MAX	9	//マップの縦の数
#define GAME_MAP_YOKO_MAX	16	//マップの横の数
#define GAME_MAP_KIND_MAX	2	//マップの種類の数

#define IMG_SOUGEN				TEXT(".\\IMAGE\\sougen.png")		//タイトル画面の背景
#define IMG_SORA				TEXT(".\\IMAGE\\sora.png")			//プレイ画面の背景
#define IMG_MARU				TEXT(".\\IMAGE\\player.png")		//プレイヤーの画像
#define IMG_LOGO				TEXT(".\\IMAGE\\ParQuiz.png")			//ロゴの画像
#define IMG_LOGO_END			TEXT(".\\IMAGE\\logo_end.png")		//エンドの画像
#define IMG_SPACE				TEXT(".\\IMAGE\\pressofspace.png")		//PRESS OF SPACEKEYの画像
#define IMG_ENTER				TEXT(".\\IMAGE\\pressofenter.png")		//PRESS OF ENTERの画像

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip3.png")		//マップの画像

#define MAP_DIV_WIDTH		60	//画像を分割する幅サイズ
#define MAP_DIV_HEIGHT		60	//画像を分割する高さサイズ
#define MAP_DIV_TATE		4	//画像を縦に分割する数
#define MAP_DIV_YOKO		4	//画像を横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//画像を分割する総数

//エラーメッセージ
#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

//終了ダイアログ用
#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

#define MUSIC_START_PATH		TEXT(".\\MUSIC\\1.Start.mp3")	//タイトル画面BGM
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\2.Play.mp3")	//プレイ画面BGM
#define MUSIC_END_PATH			TEXT(".\\MUSIC\\3.End.mp3")		//エンド画面BGM
#define MUSIC_KETTEI_PATH		TEXT(".\\MUSIC\\Kettei.mp3")	//決定効果音
#define MUSIC_JANP_PATH			TEXT(".\\MUSIC\\Janp.mp3")		//ジャンプ効果音

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)未定
	b = 1,	//ブロック
	g = 2,	//ゴール
	h = 3,	//スター
	d = 4,	//トゲ(ダメージのd)
	t = 5,	//通路
	s = 6	//スタート
};	//マップの種類

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 7,

};	//キャラクターのスピード

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化

}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る

}MOUSE;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	BOOL IsDraw = FALSE;		//描画できるか

}IMAGE;	//画像構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル

}MUSIC;	//音楽構造体

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y

	RECT coll;					//当たり判定
	iPOINT collBeforePt;		//当たる前の座標

}CHARA;	//キャラクター構造体

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割したマップの画像ハンドル
	int kind[MAP_DIV_NUM];				//マップの種類
	int width;							//幅
	int height;							//高さ

}MAPCHIP;	//MAP_IMAGE構造体

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//マップの種類
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}MAP;	//MAP構造体

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数
int JumpPower = 0;				//ジャンプスピード初期化
int Jumpflag = TRUE;			//ジャンプフラグ
int WJumpflag = FALSE;			//２段ジャンプフラグ
int WKeyflag = FALSE;			//Wキーを離しているかどうかのフラグ

//キーボードの入力を取得
char AllKeyState[KEY_CODE_KIND] = { '\0' };		//すべてのキーの状態が入る
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;

//ゲーム関連
int GameScene;			//ゲームシーンを管理

IMAGE ImageTitle;		//タイトル画面の背景画像
IMAGE ImagePlay;		//プレイ画面の背景画像
IMAGE ImageTitleROGO;	//ロゴの画像
IMAGE ImageTitleEND;	//クリアの画像

IMAGE ImageSpace;		//スペースキーを押してください
IMAGE ImageEnter;		//エンターキーを押してください

CHARA player;			//ゲームのキャラ

MUSIC BGM_START;		//タイトル画面BGM
MUSIC BGM_PLAY;			//プレイ画面BGM
MUSIC BGM_END;			//エンド画面BGM
MUSIC BGM_KETTEI;		//決定SE

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
};	//ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

//マップの当たり判定
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//ゴールの当たり判定
RECT goalColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

VOID MY_START(VOID);				//スタート画面
VOID MY_START_PROC(VOID);			//スタート画面の処理
VOID MY_START_DRAW(VOID);			//スタート画面の描画

VOID MY_PLAY_INIT(VOID);			//プレイ画面初期化
VOID MY_PLAY(VOID);					//プレイ画面
VOID MY_PLAY_PROC(VOID);			//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);			//プレイ画面の描画

VOID MY_END(VOID);					//エンド画面
VOID MY_END_PROC(VOID);				//エンド画面の処理
VOID MY_END_DRAW(VOID);				//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);			//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);			//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);			//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);			//音楽をまとめて削除する関数

BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT);	//ゴールとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_BLOCK_PLAYER_COLL(RECT);	//ブロックとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_STAR_PLAYER_COLL(RECT);	//スターとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//領域の当たり判定をする関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(FALSE);				//Log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(IDI_ICON1);							//アイコンファイルを読込
	SetWindowUserCloseEnableFlag(FALSE);				//閉じるボタンで、勝手にウィンドウが閉じないようにする

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }


	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から
	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

		//プレイヤーの最初の位置を、スタート位置にする
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//スタート位置を探す
			if (mapData[tate][yoko] == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
				break;
			}
		}
		//スタートが決まっていれば、ループ終了
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}

	//スタートが決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		//画面の閉じるボタンを押されたとき
		if (GetWindowUserCloseFlag(TRUE))
		{
			//終了ダイアログを表示
			int Ret = MessageBox(GetMainWindowHandle(), MSG_CLOSE_CAPTION, MSG_CLOSE_TITLE, MB_YESNO | MB_ICONASTERISK);
			if (Ret == IDYES) { break; }	//YESなら、ゲームを中断する
		}

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{

	//一時的に、現在のキーの入力状態を格納する
	char TempKey[KEY_CODE_KIND];

	//直前のキー入力をとっておく
	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}


//フォントをこのソフト用に、一時的にインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントをこのソフト用に、一時的にアンインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントを読み込む関数
//引　数：const char *：読み込むフォントの名前
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：BOOL ：エラー時はFALSE / 正常時はTRUE
BOOL MY_FONT_CREATE(VOID)
{
	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(BGM_START.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 80 / 100, BGM_START.handle);	//50%の音量にする
		PlaySoundMem(BGM_START.handle, DX_PLAYTYPE_LOOP);
	}

	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(BGM_START.handle) != 0)
		{
			StopSoundMem(BGM_START.handle);	//BGMを止める
		}

		ChangeVolumeSoundMem(255 * 30 / 100, BGM_KETTEI.handle);	//50%の音量にする
		PlaySoundMem(BGM_KETTEI.handle, DX_PLAYTYPE_BACK);

		MY_PLAY_INIT();	//ゲーム初期化

		player.image.x = startPt.x - 30;
		player.CenterX = startPt.x;
		player.image.y = startPt.y - 40;
		player.CenterY = startPt.y - 10;

		//ゲームのシーンをプレイ画面にする
		GameScene = GAME_SCENE_PLAY;

		return;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//スタート画面背景を描画する
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);

	//タイトル背景を描画する
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);

	//PRESS OF SPACEKEYを描画する
	DrawGraph(ImageSpace.x, ImageSpace.y, ImageSpace.handle, TRUE);	//PRESS OF SPACEKEYの描画

	return;
}

//プレイ画面初期化
VOID MY_PLAY_INIT(VOID)
{
	// 画面を初期化する
	ClearDrawScreen();

	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{	

	//BGMが流れていないなら
	if (CheckSoundMem(BGM_PLAY.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 30 / 100, BGM_PLAY.handle);	//50%の音量にする
		PlaySoundMem(BGM_PLAY.handle, DX_PLAYTYPE_LOOP);

	}

	/*▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ジャンプの処理▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/

	//ジャンプフラグがTRUEでWキーを押していてプレイヤーとブロックがあたっていたらジャンプ
	if (Jumpflag==TRUE && CheckHitKey(KEY_INPUT_W) == TRUE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
	{
		JumpPower = 11;			//約1ブロック分のジャンプ
		Jumpflag = FALSE;		//ジャンプフラグをFALSEにする
		WKeyflag = TRUE;		//WキーフラグをTRUEにする
	}

	//二段ジャンプフラグがTRUEでWキーを押していたら空中ジャンプ
	if (WJumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE)
	{
		JumpPower = 11;			//２ブロック分のジャンプ
		WJumpflag = FALSE;		//二段ジャンプフラグをFALSEにする
		WKeyflag = FALSE;		//WキーフラグをTRUEにする
	}

	//Wキーを離してプレイヤーが地面につくと
	if (CheckHitKey(KEY_INPUT_W) == FALSE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
	{
		Jumpflag = TRUE;		//ジャンプフラグをTRUEにし、ジャンプができるようになる
	}

	//WキーフラグがTRUEかつWキーを離すと
	if (WKeyflag == TRUE && CheckHitKey(KEY_INPUT_W) == FALSE)
	{
		WJumpflag = TRUE;		//二段ジャンプフラグをTRUEにし、二段ジャンプができるようになる
	}

	// 落下処理
	player.CenterY -= JumpPower;
	player.image.y -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 1;

	/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ジャンプの処理▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/

	//Dキーで右へ進む
	if (CheckHitKey(KEY_INPUT_D) == TRUE)
	{
		player.image.x += player.speed;
		player.CenterX += player.speed;
	}

	//Aキーで左へ進む
	if (CheckHitKey(KEY_INPUT_A) == TRUE)
	{
		player.image.x -= player.speed;
		player.CenterX -= player.speed;
	}

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 1;
	player.coll.top = player.CenterY - mapChip.height / 2 + 1;
	player.coll.right = player.CenterX + mapChip.width / 2 - 1;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 1;

	//プレイヤーとゴールがあたっていたら
	if (MY_CHECK_GOAL_PLAYER_COLL(player.coll) == TRUE)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGMを止める
		}

		//ゲームのシーンをエンド画面にする
		GameScene = GAME_SCENE_END;
	}

	//プレイヤーとブロックが当たっていたら直前の位置へ戻る
	if (MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == TRUE)
	{
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		player.image.x = player.collBeforePt.x - 30;
		player.image.y = player.collBeforePt.y - 30;
		JumpPower = 0;
		WJumpflag = FALSE;	//二段ジャンプフラグをFALSE
		WKeyflag = FALSE;	//WキーフラグをFALSE
	}

	//プレイヤーとスターがあたっていたらマップ上のすべてのスターを消す
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

	//プレイヤーの当たる以前の位置を設定する
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	// 画面を初期化する
	ClearDrawScreen();

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{

	//プレイ画面背景を描画する
	DrawGraph(ImagePlay.x, ImagePlay.y, ImagePlay.handle, TRUE);

	//プレイヤーを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップを描画
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	//当たり判定の描画（デバッグ用）
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (mapData[tate][yoko] == b)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//通路ならば
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}

			//ゴールならば
			if (mapData[tate][yoko] == g)
			{
				DrawBox(goalColl[tate][yoko].left, goalColl[tate][yoko].top, goalColl[tate][yoko].right, goalColl[tate][yoko].bottom, GetColor(0, 255,0), FALSE);
			}

			//スターならば
			if (mapData[tate][yoko] == h)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 0, 255), FALSE);
			}

		}
	}

	//プレーヤー当たり判定の描画（デバッグ用）
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);


	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画

	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(BGM_END.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_END.handle);	//50%の音量にする
		PlaySoundMem(BGM_END.handle, DX_PLAYTYPE_LOOP);
	}

	//エンターキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_END.handle) != 0)
		{
			StopSoundMem(BGM_END.handle);	//BGMを止める
		}

		//スタート画面にする
		GameScene = GAME_SCENE_START;
	}

	// 画面を初期化する
	ClearDrawScreen();

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();	//プレイ画面を描画

	//GAME CLEAR!!!を描画
	DrawGraph(ImageTitleEND.x, ImageTitleEND.y, ImageTitleEND.handle, TRUE);

	DrawGraph(ImageEnter.x, ImageEnter.y, ImageEnter.handle, TRUE);	//PRESS OF ENTERKEYの描画
	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//背景画像
	strcpy_s(ImageTitle.path, IMG_SOUGEN);		//パスの設定
	ImageTitle.handle = LoadGraph(ImageTitle.path);	//読み込み
	if (ImageTitle.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SOUGEN, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);	//画像の幅と高さを取得
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;		//左右中央揃え
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;	//上下中央揃え

	//背景画像
	strcpy_s(ImagePlay.path, IMG_SORA);		//パスの設定
	ImagePlay.handle = LoadGraph(ImagePlay.path);	//読み込み
	if (ImagePlay.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SORA, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePlay.handle, &ImagePlay.width, &ImagePlay.height);	//画像の幅と高さを取得
	ImagePlay.x = GAME_WIDTH / 2 - ImagePlay.width / 2;		//左右中央揃え
	ImagePlay.y = GAME_HEIGHT / 2 - ImagePlay.height / 2;	//上下中央揃え

	//タイトルロゴ
	strcpy_s(ImageTitleROGO.path, IMG_LOGO);						//パスの設定
	ImageTitleROGO.handle = LoadGraph(ImageTitleROGO.path);				//読み込み
	if (ImageTitleROGO.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_LOGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.handle, &ImageTitleROGO.width, &ImageTitleROGO.height);	//画像の幅と高さを取得
	ImageTitleROGO.x = GAME_WIDTH / 2 - ImageTitleROGO.width / 2;		//左右中央揃え
	ImageTitleROGO.y = GAME_HEIGHT / 2 - ImageTitleROGO.height / 2;	//上下中央揃え

	//エンド画面(GAME CLEAR)の画像
	strcpy_s(ImageTitleEND.path, IMG_LOGO_END);						//パスの設定
	ImageTitleEND.handle = LoadGraph(ImageTitleEND.path);				//読み込み
	if (ImageTitleEND.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_LOGO_END, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleEND.handle, &ImageTitleEND.width, &ImageTitleEND.height);	//画像の幅と高さを取得
	ImageTitleEND.x = GAME_WIDTH / 2 - ImageTitleEND.width / 2;		//左右中央揃え
	ImageTitleEND.y = GAME_HEIGHT / 2 - ImageTitleEND.height / 2;	//上下中央揃え

	//PRESS OF SPACEKEY!!!の画像
	strcpy_s(ImageSpace.path, IMG_SPACE);						//パスの設定
	ImageSpace.handle = LoadGraph(ImageSpace.path);				//読み込み
	if (ImageSpace.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SPACE, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageSpace.handle, &ImageSpace.width, &ImageSpace.height);	//画像の幅と高さを取得
	ImageSpace.x = GAME_WIDTH / 2 - ImageSpace.width / 2;		//左右中央揃え
	ImageSpace.y = GAME_HEIGHT / 2 + ImageSpace.height + 30;	//上下中央揃え

	//PRESS OF SPACEKEY!!!の画像
	strcpy_s(ImageEnter.path, IMG_ENTER);						//パスの設定
	ImageEnter.handle = LoadGraph(ImageEnter.path);				//読み込み
	if (ImageEnter.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_ENTER, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEnter.handle, &ImageEnter.width, &ImageEnter.height);	//画像の幅と高さを取得
	ImageEnter.x = GAME_WIDTH / 2 - ImageEnter.width / 2;		//左右中央揃え
	ImageEnter.y = GAME_HEIGHT / 2 + ImageEnter.height + 30;	//上下中央揃え

	//プレイヤーの画像
	strcpy_s(player.image.path, IMG_MARU);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_MARU, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_HIGH;								//スピードを設定

		//マップの画像を分割する
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//マップチップのパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//マップチップを分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割する幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//ゴールの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//ゴールの当たり判定を設定
			goalColl[tate][yoko].left = (yoko + 0) * mapChip.width + 10;
			goalColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			goalColl[tate][yoko].right = (yoko + 1) * mapChip.width - 10;
			goalColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}


	return TRUE;
}

//画像をまとめて削除する関数
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

//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{
	//スタート画面BGMの読み込み
	strcpy_s(BGM_START.path, MUSIC_START_PATH);		//パスの設定
	BGM_START.handle = LoadSoundMem(BGM_START.path);	//読み込み
	if (BGM_START.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイ画面BGMの読み込み
	strcpy_s(BGM_PLAY.path, MUSIC_PLAY_PATH);		//パスの設定
	BGM_PLAY.handle = LoadSoundMem(BGM_PLAY.path);	//読み込み
	if (BGM_PLAY.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//エンド画面BGMの読み込み
	strcpy_s(BGM_END.path, MUSIC_END_PATH);			//パスの設定
	BGM_END.handle = LoadSoundMem(BGM_END.path);	//読み込み
	if (BGM_END.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_END_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//決定SEの読み込み
	strcpy_s(BGM_KETTEI.path, MUSIC_KETTEI_PATH);		//パスの設定
	BGM_KETTEI.handle = LoadSoundMem(BGM_KETTEI.path);	//読み込み
	if (BGM_KETTEI.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_KETTEI_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM_START.handle);
	DeleteSoundMem(BGM_PLAY.handle);
	DeleteSoundMem(BGM_END.handle);
	DeleteSoundMem(BGM_KETTEI.handle);

	return;
}

//プレイヤーとゴールの当たり判定をする関数
BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとゴールが当たっているとき
			if (MY_CHECK_RECT_COLL(player, goalColl[tate][yoko]) == TRUE)
			{
				//ゴールのときは、TRUEを返す
				if (map[tate][yoko].kind == g) { return TRUE; }
			}

		}
	}

	return FALSE;
}

//プレイヤーとブロックの当たり判定をする関数
BOOL MY_CHECK_BLOCK_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとブロックが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//ブロックのときは、TRUEを返す
				if (map[tate][yoko].kind == b) { return TRUE; }
			}
		}
	}

	return FALSE;

}

//プレイヤーとスターの当たり判定をする関数
BOOL MY_CHECK_STAR_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとスターが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//スターのときは、TRUEを返す
				if (map[tate][yoko].kind == h) { return TRUE; }
			}
		}
	}

	return FALSE;

}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)

	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}
