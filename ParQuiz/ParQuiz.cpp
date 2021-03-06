//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <math.h>

//########## マクロ定義 ##########
#define GAME_WIDTH			1200//画面の横の大きさ
#define GAME_HEIGHT			660	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0					//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"		//ウィンドウのタイトル

#define GAME_FPS						60	//FPSの値

//マウスのボタン
#define MOUSE_BUTTON_CODE	129	//0x0000〜0x0080まで

//キーボードの種類
#define KEY_CODE_KIND		256	//256種類

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

#define TOGE_MOVE           2	//トゲが動く距離(1なら左右に1マスずつ。真ん中も合わせて計3マス動く)
#define TOGE_SPEED          2	//トゲのスピード

//フォントのパスの長さ
#define FONT_PATH_MAX			255	//255文字まで

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

#define GAME_MAP_TATE_MAX	11	//マップの縦の数
#define GAME_MAP_YOKO_MAX	20	//マップの横の数
#define GAME_MAP_KIND_MAX	2	//マップの種類の数

#define IMG_SOUGEN				TEXT(".\\IMAGE\\sougen.png")			//タイトル画面の背景
#define IMG_SORA				TEXT(".\\IMAGE\\sora.png")				//プレイ画面の背景
#define IMG_MARU				TEXT(".\\IMAGE\\player2.png")			//プレイヤーの画像
#define IMG_LOGO				TEXT(".\\IMAGE\\ParQuiz.png")			//ロゴの画像
#define IMG_LOGO_CLEAR			TEXT(".\\IMAGE\\logo_end.png")			//クリアの画像
#define IMG_LOGO_OVER			TEXT(".\\IMAGE\\logo_end2.png")			//ゲームオーバーの画像
#define IMG_SPACE				TEXT(".\\IMAGE\\key_playtospacekey.png")	//PLAY TO SPACEKEYの画像
#define IMG_SPACE2				TEXT(".\\IMAGE\\key_retrytospacekey.png")	//RETRY TO SPACEKEYの画像
#define IMG_SPACE3				TEXT(".\\IMAGE\\key_nexttospacekey.png")	//NEXT TO SPACEKEYの画像
#define IMG_ENTER				TEXT(".\\IMAGE\\key_titletoenterkey.png")	//TITLE TO ENTERの画像
#define IMG_QUESTION_0			TEXT(".\\IMAGE\\Question0.png")			//クイズ4の画像
#define IMG_QUESTION_1			TEXT(".\\IMAGE\\Question1.png")			//クイズ1の画像
#define IMG_QUESTION_2			TEXT(".\\IMAGE\\Question2.png")			//クイズ2の画像
#define IMG_QUESTION_3			TEXT(".\\IMAGE\\Question3.png")			//クイズ3の画像
#define IMG_QUESTION_4			TEXT(".\\IMAGE\\Question4.png")			//クイズ4の画像

#define IMAGE_QUIZ_ROTA			0.05	//拡大率
#define IMAGE_QUIZ_ROTA_MAX		1		//拡大率MAX
#define IMAGE_QUIZ_X_SPEED		1		//X移動速度

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\mapchip.png")		//マップチップの画像

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
#define MUSIC_CLEAR_PATH		TEXT(".\\MUSIC\\3.Clear.mp3")	//クリア画面BGM
#define MUSIC_OVER_PATH			TEXT(".\\MUSIC\\4.Over.mp3")	//ゲームオーバー画面BGM
#define MUSIC_KETTEI_PATH		TEXT(".\\MUSIC\\Kettei.mp3")	//決定効果音
#define MUSIC_JUMP1_PATH		TEXT(".\\MUSIC\\Jump1.mp3")		//ジャンプ効果音
#define MUSIC_JUMP2_PATH		TEXT(".\\MUSIC\\Jump2.mp3")		//ジャンプニ段目効果音
#define MUSIC_STAR_PATH			TEXT(".\\MUSIC\\Star.mp3")		//スター効果音

enum GAME_MAP_KIND
{
	m1 = -1,	//星1を取った時m1に変換
	m2 = -2,	//星2を取った時m2に変換
	m3 = -3,	//星3を取った時m3に変換
	b = 1,	//ブロック
	g = 2,	//ゴール
	//d = 3,	//トゲ2(デンジャー)
	n = 4,	//トゲ(ニードル)
	h1 = 5,	//星1
	h2 = 6,	//星2
	h3 = 7,	//星3
	m = 8,	//動くトゲ
	v = 9,	//縦に動くトゲ
	a = 10,  //動くブロック
	t = 11,	//通路
	s = 12	//スタート
};	//マップの種類

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_QUIZ,
};	//ゲームのシーン

enum GAME_STAGE {
	GAME_STAGE_0,
	GAME_STAGE_1,
	GAME_STAGE_2,
	GAME_STAGE_3,
	GAME_STAGE_4,
};	//ゲームのステージ

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 7,

};	//キャラクターのスピード

enum GAME_END {
	GAME_END_CLEAR,	//クリア
	GAME_END_OVER	//ゲームオーバー
};	//ゲームの終了状態

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

typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ

}FONT; //フォント構造体

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	double radian;				//ラジアン(角度)
	double angle;				//回転率
	double angleMAX;			//回転率MAX
	double rate;				//拡大率
	double rateMAX;				//拡大率MAX
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

}MAPCHIP;	//MAPCHIP構造体

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

//キーボードの入力を取得
char AllKeyState[KEY_CODE_KIND] = { '\0' };		//すべてのキーの状態が入る
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;

//ゲーム関連
int GameScene;					//ゲームシーンを管理

int GameStage;					//ゲームのステージを管理

int GameEndKind;				//ゲームの終了状態

int Dead = 0;					//ゲームオーバーになった数

int JumpPower = 0;				//ジャンプスピード初期化
int Jumpflag = TRUE;			//ジャンプフラグ(TRUEならジャンプできる)
int WJumpflag = FALSE;			//２段ジャンプフラグ(TRUEなら二段ジャンプできる)
int WKeyflag = FALSE;			//Wキーを離しているかどうかのフラグ(二段ジャンプのときに使う)
int Answer = 0;					//取ったスターを入れる変数

int Toge = TOGE_MOVE;			//トゲが動く距離
int TogeSpeed = TOGE_SPEED;		//トゲのスピード
int Togeflag = TRUE;			//動くトゲの切り返しのフラグ(TRUEのときは右に動く)	
int TogeMove = 0;				//トゲが動いた距離を測る変数
int Cntm = 0;					//動くトゲのカウンター(トゲが増えるほど増えていく)

int Togeflag2 = TRUE;			//縦に動くトゲの切り返しのフラグ(TRUEのときは右に動く)	
int TogeMove2 = 0;				//縦のトゲが動いた距離を測る変数
int Cntm2 = 0;					//縦に動くトゲのカウンター(トゲが増えるほど増えていく)

int Clearflag = TRUE;			//クリアしたかどうかのフラグ(プレイ画面の初期化に使用)
int Quizflag = TRUE;			//クイズが表示されているかどうかのフラグ
int Mapflag = TRUE;				//マップを変えるためのフラグ

int MapAnswer[] = {1,2,1,2,3};	//ステージごとの答え

IMAGE ImageTitle;				//タイトル画面の背景画像
IMAGE ImagePlay;				//プレイ画面の背景画像
IMAGE ImageTitleROGO;			//ロゴの画像
IMAGE ImageTitleCLEAR;			//クリアの画像
IMAGE ImageTitleOVER;			//ゲームオーバーの画像
IMAGE ImageQuestion;			//クイズの画像

IMAGE ImageSpace;				//スペースキーでプレイ画面
IMAGE ImageSpace2;				//スペースキーでリトライ
IMAGE ImageSpace3;				//スペースキーで次のステージ
IMAGE ImageEnter;				//エンターキーでタイトル画面

CHARA player;					//ゲームのキャラ

FONT FontTanu32;	//たぬき油性マジック：大きさ32　のフォント構造体

MUSIC BGM_START;				//タイトル画面BGM
MUSIC BGM_PLAY;					//プレイ画面BGM
MUSIC BGM_CLEAR;				//クリア画面BGM
MUSIC BGM_OVER;					//ゲームオーバー画面BGM
MUSIC BGM_KETTEI;				//決定SE
MUSIC BGM_JUMP1;				//ジャンプSE
MUSIC BGM_JUMP2;				//ニ段ジャンプSE
MUSIC BGM_STAR;					//スター取った時のSE

GAME_MAP_KIND mapData0[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 0
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 1
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 2
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 3
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 4
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 5
		b,t,t,t,h1,t,t,t,t,h2,t,t,t,t,h3,t,t,t,t,b,	// 6
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 7
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 8
		b,s,t,t,t,t,t,t,t,n,t,t,t,t,t,t,t,t,g,b,	// 9
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 10
};	//ステージ０のマップ

GAME_MAP_KIND mapData1[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,	// 0
		n,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,n,	// 1
		n,t,t,g,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,n,	// 2
		n,t,t,b,n,n,t,t,n,t,t,t,t,n,t,t,t,t,t,n,	// 3
		n,t,t,t,t,t,t,t,n,t,t,t,t,n,t,t,t,t,t,n,	// 4
		n,h3,t,t,t,t,t,t,t,b,t,t,t,t,t,t,t,t,t,n,	// 5
		n,b,t,t,t,t,t,t,t,t,t,n,t,h1,t,t,t,t,t,n,	// 6
		n,t,t,t,t,b,t,t,t,t,b,t,t,b,t,t,t,t,t,n,	// 7
		n,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,n,h2,n,	// 8
		n,s,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,n,n,	// 9
		n,b,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,	// 0
};	//ステージ1のマップ

GAME_MAP_KIND mapData2[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		b,t,t,t,t,t,n,t,t,t,t,t,t,n,n,n,t,t,t,n,	// 0
		b,t,t,t,t,t,t,t,t,t,t,t,t,n,n,n,t,t,g,n,	// 1
		b,b,t,t,t,t,b,b,n,b,t,t,t,n,n,n,t,t,b,n,	// 2
		b,t,t,t,t,t,t,t,t,t,n,t,t,n,n,n,t,t,t,n,	// 3
		b,t,t,t,t,t,t,t,t,t,n,t,t,n,n,n,b,t,t,n,	// 4
		b,b,t,t,t,t,t,t,t,t,n,t,t,n,n,n,t,t,t,n,	// 5
		b,t,t,t,t,t,t,t,t,t,n,t,t,n,n,n,t,t,b,n,	// 6
		b,t,t,t,t,t,t,n,h1,n,t,t,t,t,t,t,t,t,t,n,	// 7
		b,t,t,b,t,t,t,n,b,t,t,t,t,t,t,t,t,b,t,n,	// 8
		b,s,t,b,t,t,h2,n,b,h3,t,t,t,t,t,t,t,t,t,n,	// 9
		b,b,b,b,n,n,n,n,n,b,n,n,n,n,n,b,n,n,n,n,	// 10
};	//ステージ２のマップ

GAME_MAP_KIND mapData3[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		n,n,n,n,t,t,t,t,t,t,t,t,t,t,t,t,n,n,n,n,	// 0
		n,h2,m,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,n,	// 1
		n,t,t,t,b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,n,	// 2
		n,t,t,t,t,t,t,b,t,t,m,t,b,t,t,t,t,t,b,n,	// 3
		n,t,t,t,t,h1,t,t,t,b,t,t,t,m,m,t,m,m,m,m,	// 4
		n,h3,n,n,n,n,n,t,t,n,t,t,h3,n,t,t,t,t,t,n,	// 5
		n,t,t,t,t,m,t,t,t,t,t,b,t,n,t,t,t,t,t,n,	// 6
		n,t,b,t,t,t,b,t,t,t,t,t,t,n,t,t,t,t,t,n,	// 7
		n,t,t,t,t,t,t,t,m,t,b,m,t,n,t,t,t,t,t,n,	// 8
		n,s,t,t,t,t,t,n,t,n,t,t,h2,n,t,t,t,t,g,n,	// 9
		n,b,n,n,n,n,n,n,b,n,n,n,n,n,n,n,n,n,n,n,	// 10
};	//ステージ３のマップ

GAME_MAP_KIND mapData4[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 0
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 1
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 2
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 3
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 4
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 5
		b,t,t,t,h1,t,t,t,t,h2,t,t,t,t,h3,t,t,t,t,b,	// 6
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 7
		b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,	// 8
		b,s,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,g,b,	// 9
		b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,	// 10
};	//ステージ４のマップ

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

//マップの当たり判定(基本)
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
VOID MY_PLAY_INIT_OVER(VOID);		//ゲームオーバー版プレイ画面初期化
VOID MY_PLAY(VOID);					//プレイ画面
VOID MY_PLAY_PROC(VOID);			//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);			//プレイ画面の描画

VOID MY_END(VOID);					//エンド画面
VOID MY_END_PROC(VOID);				//エンド画面の処理
VOID MY_END_DRAW(VOID);				//エンド画面の描画

VOID MY_LOAD_QUIZ(VOID);			//画像をまとめて読み込む関数
VOID MY_QUIZ(VOID);					//クイズ画面
VOID MY_QUIZ_PROC(VOID);			//クイズ画面1の処理
VOID MY_QUIZ_DRAW(VOID);			//クイズ画面1の描画

BOOL MY_LOAD_IMAGE(VOID);			//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);			//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);			//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);			//音楽をまとめて削除する関数

VOID PLAYER_MOVE(VOID);				//プレイヤーの動きの処理の関数

BOOL MY_CHECK_GOAL_PLAYER_COLL(RECT);	//ゴールとプレイヤーの当たり判定をする関数
int MY_CHECK_BLOCK_PLAYER_COLL(RECT);	//ブロックとプレイヤーの当たり判定をする関数
int MY_CHECK_STAR_PLAYER_COLL(RECT);	//スターとプレイヤーの当たり判定をする関数
int MY_CHECK_TOGE_PLAYER_COLL(RECT);	//トゲとプレイヤーの当たり判定をする関数
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
	SetWindowIconID(444);								//アイコンファイルを読込
	SetWindowUserCloseEnableFlag(FALSE);				//閉じるボタンで、勝手にウィンドウが閉じないようにする

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	GameStage = GAME_STAGE_0;		//ゲームステージはステージ1から

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);	//文字にアンチエイリアスをかける

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

		MY_ALL_KEYDOWN_UPDATE();	//押しているキー状態を取得

		MY_FPS_UPDATE();			//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_QUIZ:
			MY_QUIZ();	//クイズ画面
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
		return FALSE;	//キーを押し上げていないGAME_FPS
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

	//フォントデータを作成
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//パスをコピー
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//フォント名をコピー
	FontTanu32.handle = -1;								//ハンドルを初期化
	FontTanu32.size = 50;								//サイズは32
	FontTanu32.bold = 1;								//太さ1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//フォントハンドル作成できないとき、エラー
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{

	//フォントデータを削除
	DeleteFontToHandle(FontTanu32.handle);	//フォントのハンドルを削除

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
	//QuizflagをTRUE
	Quizflag = TRUE;

	//BGMが流れていないなら
	if (CheckSoundMem(BGM_START.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 80 / 100, BGM_START.handle);	//80%の音量にする
		PlaySoundMem(BGM_START.handle, DX_PLAYTYPE_LOOP);
	}

	//0キーで死亡数をリセット
	if (CheckHitKey(KEY_INPUT_0) == TRUE)
	{
		Dead = 0;
	}

	//スペースキーを押したら、プレイ画面へ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//クリアフラグ
		switch (Clearflag)
		{

		//TRUEならゲーム画面を塗り替える
		case TRUE:
			MY_PLAY_INIT();	//ゲーム初期化
			MY_LOAD_QUIZ();	//クイズを読み込む
			break;

		//FALSEならトゲの位置を修正
		case FALSE:
			MY_PLAY_INIT_OVER();
			break;
		}

		if (CheckSoundMem(BGM_START.handle) != 0)
		{
			StopSoundMem(BGM_START.handle);	//BGMを止める
		}

		ChangeVolumeSoundMem(255 * 30 / 100, BGM_KETTEI.handle);	//30%の音量にする
		PlaySoundMem(BGM_KETTEI.handle, DX_PLAYTYPE_BACK);

		//ゲームの終了状態を初期化する
		GameEndKind = GAME_END_OVER;

		//ゲームのシーンをプレイ画面にする
		GameScene = GAME_SCENE_QUIZ;

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

	//PLAY TO SPACEKEYを描画する
	DrawGraph(ImageSpace.x, ImageSpace.y, ImageSpace.handle, TRUE);	//PRESS OF SPACEKEYの描画

	return;
}

//クイズ画面
VOID MY_QUIZ(VOID)
{
	MY_QUIZ_PROC();	//クイズ画面の処理
	MY_QUIZ_DRAW();	//クイズ画面の描画

	return;
}

VOID MY_LOAD_QUIZ(VOID)	//クイズを読み込む関数
{
	switch (GameStage)
	{
	case GAME_STAGE_0:
		//クイズ1
		strcpy_s(ImageQuestion.path, IMG_QUESTION_0);				//パスの設定
		break;

		case GAME_STAGE_1:
		//クイズ1
		strcpy_s(ImageQuestion.path, IMG_QUESTION_1);				//パスの設定
		break;

		case GAME_STAGE_2:
		//クイズ2
		strcpy_s(ImageQuestion.path, IMG_QUESTION_2);				//パスの設定
		break;

		case GAME_STAGE_3:
		//クイズ3
		strcpy_s(ImageQuestion.path, IMG_QUESTION_3);				//パスの設定
		break;

		case GAME_STAGE_4:
		//クイズ4
		strcpy_s(ImageQuestion.path, IMG_QUESTION_4);				//パスの設定
		break;

	}

	ImageQuestion.handle = LoadGraph(ImageQuestion.path);	//読み込み
	GetGraphSize(ImageQuestion.handle, &ImageQuestion.width, &ImageQuestion.height);	//画像の幅と高さを取得
	ImageQuestion.x = GAME_WIDTH / 2;				//左右中央揃え
	ImageQuestion.y = GAME_HEIGHT / 2;				//上下中央揃え
	ImageQuestion.angle = DX_PI * 2;				//回転率
	ImageQuestion.angleMAX = DX_PI * 2;				//回転率MAX
	ImageQuestion.rate = 0.1;						//拡大率
	ImageQuestion.rateMAX = IMAGE_QUIZ_ROTA_MAX;	//拡大率MAX

	return;
}

//クイズ画面の処理
VOID MY_QUIZ_PROC(VOID)
{

	//QuizflagがTRUEの場合
	if (Quizflag == TRUE)
	{
		//クイズを拡大
		if (ImageQuestion.rate < ImageQuestion.rateMAX)
		{
			ImageQuestion.rate += IMAGE_QUIZ_ROTA;
		}
	}

	//エンターキーを押したら、QuizflagをTRUEにする
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{	
		Quizflag = FALSE;

	}

	//QuizflagがTRUEの場合
	if (Quizflag == FALSE)
	{
		//クイズを拡小
		if (ImageQuestion.rate > 0)
		{
			ImageQuestion.rate -= IMAGE_QUIZ_ROTA;
		}

		//画像が消えたらプレイ画面へ
		else
		{
		//ゲームのシーンをプレイ画面にする
		GameScene = GAME_SCENE_PLAY;
		}
	}

	return;
}

//クイズ画面の描画
VOID MY_QUIZ_DRAW(VOID)
{
	MY_PLAY_DRAW();	//プレイ画面を描画

	//クイズを拡大しながら描画
	DrawRotaGraph(
		ImageQuestion.x, ImageQuestion.y,		//画像の座標
		ImageQuestion.rate,						//画像の拡大率
		ImageQuestion.angle,					//画像の回転率
		ImageQuestion.handle, TRUE				//画像のハンドル
	);

	// 文字列の描画
	DrawString(900, 50, "エンターキーでスタート！", GetColor(255, 255, 0));

	return;
}

//プレイ画面初期化
VOID MY_PLAY_INIT(VOID)
{
	//動くトゲカウンターを初期化(しないと多分どんどん増えてく)
	Cntm = 0;
	Cntm2 = 0;

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			//ゲームのステージ
			switch (GameStage)
			{
			case GAME_STAGE_0:

				//マップの種類をコピー
				map[tate][yoko].kind = mapData0[tate][yoko];

				break;

			case GAME_STAGE_1:

				//マップの種類をコピー
				map[tate][yoko].kind = mapData1[tate][yoko];

				break;

			case GAME_STAGE_2:

				//マップの種類をコピー
				map[tate][yoko].kind = mapData2[tate][yoko];

				break;

			case GAME_STAGE_3:

				//マップの種類をコピー
				map[tate][yoko].kind = mapData3[tate][yoko];

				break;

			case GAME_STAGE_4:

				//マップの種類をコピー
				map[tate][yoko].kind = mapData4[tate][yoko];

				break;

			}

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;


			//そのマップにある動くトゲをカウント
			if (map[tate][yoko].kind == m)
			{
				Cntm++;
			}

			//そのマップにある縦に動くトゲをカウント
			if (map[tate][yoko].kind == v)
			{
				Cntm2++;
			}

			//消えたスターを元に戻す
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

		}
	}

	//プレイヤーの最初の位置を、スタート位置にする
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//スタート位置を探す
			if (map[tate][yoko].kind == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
				break;
			}
		}
	}

	//プレイヤーをスタート位置に描画
	player.image.x = startPt.x - 30;
	player.CenterX = startPt.x;
	player.image.y = startPt.y - 40;
	player.CenterY = startPt.y - 10;

	Answer = 0;			//持っている回答を消す
	Togeflag = TRUE;	//トゲを右に動くようにする
	TogeMove = 0;		//TogeMoveを初期化
	Togeflag2 = TRUE;	//トゲを下に動くようにする
	TogeMove2 = 0;		//TogeMove2を初期化
	Mapflag = TRUE;
	return;
}

//ゲームオーバー版プレイ画面初期化(トゲの位置を修正)
VOID MY_PLAY_INIT_OVER(VOID)
{
	//プレイヤーをスタート位置に描画
	player.image.x = startPt.x - 30;
	player.CenterX = startPt.x;
	player.image.y = startPt.y - 40;
	player.CenterY = startPt.y - 10;

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{

			//消えたスターを元に戻す
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

			//動くトゲの位置を初期化
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
			//縦に動くトゲの位置を初期化
			if (map[tate][yoko].kind == v)
			{

				if (TogeMove2 < 0)
				{
					map[tate][yoko].y -= TogeMove2 / Cntm2;
					mapColl[tate][yoko].top -= TogeMove2 / Cntm2;
					mapColl[tate][yoko].bottom -= TogeMove2 / Cntm2;
				}

				if (TogeMove2 > 0)
				{
					map[tate][yoko].y -= TogeMove2 / Cntm2;
					mapColl[tate][yoko].top -= TogeMove2 / Cntm2;
					mapColl[tate][yoko].bottom -= TogeMove2 / Cntm2;
				}
			}

		}
	}

	Answer = 0;			//持っている回答を消す
	Togeflag = TRUE;	//トゲを右に動くようにする
	TogeMove = 0;		//TogeMoveを初期化
	Togeflag2 = TRUE;	//トゲを右に動くようにする
	TogeMove2 = 0;		//TogeMoveを初期化

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
		ChangeVolumeSoundMem(255 * 30 / 100, BGM_PLAY.handle);	//30%の音量にする
		PlaySoundMem(BGM_PLAY.handle, DX_PLAYTYPE_LOOP);

	}

	//プレイヤーの当たる以前の位置を設定する
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;

	PLAYER_MOVE();		//プレイヤーの動きの処理

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2;
	player.coll.right = player.CenterX + mapChip.width / 2 - 15;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 10;

	//プレイヤーとブロックが当たっていたら直前の位置へ戻る
	if (MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
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
	if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2 ||
		MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
	{

		//スターSEを流す
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_STAR.handle);	//50%の音量にする
		PlaySoundMem(BGM_STAR.handle, DX_PLAYTYPE_BACK);

		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//スター1に当たっていたらAnswerに1を入れる
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 1)
				{
					Answer = 1;
				}

				//スター2に当たっていたらAnswerに2を入れる
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 2)
				{
					Answer = 2;
				}

				//スター3に当たっていたらAnswerに3を入れる
				if (MY_CHECK_STAR_PLAYER_COLL(player.coll) == 3)
				{
					Answer = 3;
				}

				//スター1を消す(m1に格納)
				if (map[tate][yoko].kind == h1)
				{
					map[tate][yoko].kind = m1;
				}

				//スター2を消す(m2に格納)
				if (map[tate][yoko].kind == h2)
				{
					map[tate][yoko].kind = m2;
				}

				//スター3を消す(m3に格納)
				if (map[tate][yoko].kind == h3)
				{
					map[tate][yoko].kind = m3;
				}
			}
		}
	}

	//動くトゲの処理
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (map[tate][yoko].kind == m)
			{
				//Togeの数だけずれたらTogeflagをFALSEにする
				if (TogeMove == Toge * 60 * Cntm)
				{
					Togeflag = FALSE;
				}

				//Togeの数だけずれたらTogeflagをTRUEにする
				if (TogeMove == Toge * -60 * Cntm)
				{
					Togeflag = TRUE;
				}

				//TogeflagがTRUEなら右に動く
				if (Togeflag == TRUE)
				{
					map[tate][yoko].x += TogeSpeed;
					mapColl[tate][yoko].left += TogeSpeed;
					mapColl[tate][yoko].right += TogeSpeed;
					TogeMove += TogeSpeed;
				}

				//TogeflagがFALSEなら左に動く
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

	//縦に動くトゲの処理
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (map[tate][yoko].kind == v)
			{
				//Togeの数だけずれたらTogeflag2をFALSEにする
				if (TogeMove2 == Toge * 60 * Cntm2)
				{
					Togeflag2 = FALSE;
				}

				//Togeの数だけずれたらTogeflag2をTRUEにする
				if (TogeMove2 == Toge * -60 * Cntm2)
				{
					Togeflag2 = TRUE;
				}

				//Togeflag2がTRUEなら下に動く
				if (Togeflag2 == TRUE)
				{
					map[tate][yoko].y += TogeSpeed;
					mapColl[tate][yoko].top += TogeSpeed;
					mapColl[tate][yoko].bottom += TogeSpeed;
					TogeMove2 += TogeSpeed;
				}

				//Togeflag2がFALSEなら上に動く
				if (Togeflag2 == FALSE)
				{
					map[tate][yoko].y -= TogeSpeed;
					mapColl[tate][yoko].top -= TogeSpeed;
					mapColl[tate][yoko].bottom -= TogeSpeed;
					TogeMove2 -= TogeSpeed;
				}
			}
		}
	}

	//プレイヤーとトゲがあたっていたらゲームオーバー画面に遷移
	if (MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 1 || 
		MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 2 ||
		MY_CHECK_TOGE_PLAYER_COLL(player.coll) == 3)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGMを止める
		}

		GameEndKind = GAME_END_OVER;	//ゲームオーバー！

		Dead += 1;			//ゲームオーバー数を増やす

		//ゲームのシーンをエンド画面にする
		GameScene = GAME_SCENE_END;

	}

	//プレイヤーとゴールがあたっていたらゲームクリア画面に遷移
	if (MY_CHECK_GOAL_PLAYER_COLL(player.coll) == TRUE)
	{
		if (CheckSoundMem(BGM_PLAY.handle) != 0)
		{
			StopSoundMem(BGM_PLAY.handle);	//BGMを止める
		}

		//クイズが正解ならクリア画面へ
		if(MapAnswer[GameStage]==Answer)
		{
			GameEndKind = GAME_END_CLEAR;
		}
		//不正解ならゲームオーバー画面へ
		else
		{
			Dead += 1;			//ゲームオーバー数を増やす

			GameEndKind = GAME_END_OVER;
		}

		//ゲームのシーンをエンド画面にする
		GameScene = GAME_SCENE_END;

	}

	//Pキーでポーズ、クイズ確認
	if (CheckHitKey(KEY_INPUT_P) == TRUE)
	{
		Quizflag = TRUE;

		//ゲームのシーンをクイズ画面にする
		GameScene = GAME_SCENE_QUIZ;

		// 文字列の描画
		DrawString(0, 0, "P", GetColor(255, 0, 0));

	}

	return;

}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{

	//プレイ画面背景を描画する
	DrawGraph(ImagePlay.x, ImagePlay.y, ImagePlay.handle, TRUE);

	//プレイヤーを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//マップチップを描画する
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

	////当たり判定の描画（デバッグ用）
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		//ブロックならば
	//		if (map[tate][yoko].kind == b || map[tate][yoko].kind == a)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
	//		}

	//		//通路ならば
	//		if (map[tate][yoko].kind == t)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
	//		}

	//		//ゴールならば
	//		if (map[tate][yoko].kind == g)
	//		{
	//			DrawBox(goalColl[tate][yoko].left, goalColl[tate][yoko].top, goalColl[tate][yoko].right, goalColl[tate][yoko].bottom, GetColor(0, 255, 0), FALSE);
	//		}

	//		//スターならば
	//		if (map[tate][yoko].kind == h1 || map[tate][yoko].kind == h2 || map[tate][yoko].kind == h3)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 0, 255), FALSE);
	//		}

	//		//トゲならば
	//		if (map[tate][yoko].kind == n || map[tate][yoko].kind == m || map[tate][yoko].kind == v)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 150, 0), FALSE);
	//		}
	//	}
	//}

	////プレーヤー当たり判定の描画（デバッグ用）
	//DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);

	// 文字列の描画
	DrawString(1000, 0, "Pキーでクイズ確認、ポーズ", GetColor(255, 0, 0));

	//ゲームオーバーになった数を表示
	int Color = GetColor(255, 0,0);
	DrawFormatStringToHandle(550,0,Color,FontTanu32.handle, "%d", Dead);

	//Aキーを押すとAを表示
	if (CheckHitKey(KEY_INPUT_A) == TRUE)
	{
		// 文字列の描画
		DrawString(0, 0, "A", GetColor(255, 0, 0));

	}

	//Wキーを押すとWを表示
	if (CheckHitKey(KEY_INPUT_W) == TRUE)
	{
		// 文字列の描画
		DrawString(8, 0, "W", GetColor(255, 0, 0));

	}

	//Dキーを押すとDを表示
	if (CheckHitKey(KEY_INPUT_D) == TRUE)
	{
		// 文字列の描画
		DrawString(16, 0, "D", GetColor(255, 0, 0));

	}

	//Pキーを押すとPを表示
	if (CheckHitKey(KEY_INPUT_P) == TRUE)
	{
		// 文字列の描画
		DrawString(24, 0, "P", GetColor(255, 0, 0));

	}

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
	switch (GameEndKind)
	{
	case GAME_END_CLEAR:
		//ゲームクリアのとき

		Clearflag = TRUE;	//クリアフラグをTRUEにする
		Quizflag = TRUE;	//クイズフラグをTRUEにする(次のステージに初めて行ったときクイズを見せる)

		//MapflagがTRUEのとき
		if (Mapflag == TRUE)
		{

			GameStage += 1;			//ステージを次に進める
			Mapflag = FALSE;		//MapflagをFALSEにする

		}

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_CLEAR.handle) == 0)
		{

			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_CLEAR.handle);	//50%の音量にする
			PlaySoundMem(BGM_CLEAR.handle, DX_PLAYTYPE_LOOP);
		}

		break;

	case GAME_END_OVER:
		//ゲームオーバーのとき

		Clearflag = FALSE;	//クリアフラグをFALSEにする

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_OVER.handle) == 0)
		{

			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_OVER.handle);	//50%の音量にする
			PlaySoundMem(BGM_OVER.handle, DX_PLAYTYPE_LOOP);
		}

		break;
	}

	//エンターキーを押したら、スタート画面へ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_CLEAR.handle) != 0)
		{
			StopSoundMem(BGM_CLEAR.handle);	//BGMを止める
		}

		if (CheckSoundMem(BGM_OVER.handle) != 0)
		{
			StopSoundMem(BGM_OVER.handle);	//BGMを止める
		}

		//スタート画面にする
		GameScene = GAME_SCENE_START;

	}

	//スペースキーを押したら、プレイ画面へ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(BGM_CLEAR.handle) != 0)
		{
			StopSoundMem(BGM_CLEAR.handle);	//BGMを止める
		}

		if (CheckSoundMem(BGM_OVER.handle) != 0)
		{
			StopSoundMem(BGM_OVER.handle);	//BGMを止める
		}

		switch (Clearflag)
		{
		case TRUE:
			MY_LOAD_QUIZ();			//クイズを読み込む
			MY_PLAY_INIT();			//ゲームクリアなら通常のプレイ画面初期化
			break;

		case FALSE:
			MY_PLAY_INIT_OVER();	//ゲームオーバーならトゲの位置を初期化
			break;
		}

		//プレイ画面にする
		GameScene = GAME_SCENE_QUIZ;

	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();	//プレイ画面を描画

	//ゲームの終了状態により、描画を変える
	switch (GameEndKind)
	{
	case GAME_END_CLEAR:
		//ゲームクリアのとき

		//ゲームクリアの描画
		DrawGraph(ImageTitleCLEAR.x, ImageTitleCLEAR.y, ImageTitleCLEAR.handle, TRUE);
		DrawGraph(ImageSpace3.x, ImageSpace3.y, ImageSpace3.handle, TRUE);	//NEXT TO SPACEKEYの描画
		break;

	case GAME_END_OVER:
		//ゲームオーバーのとき

		//ゲームオーバーの描画
		DrawGraph(ImageTitleOVER.x, ImageTitleOVER.y, ImageTitleOVER.handle, TRUE);
		DrawGraph(ImageSpace2.x, ImageSpace2.y, ImageSpace2.handle, TRUE);	//PLAY TO SPACEKEYの描画
		break;
	}

	DrawGraph(ImageEnter.x, ImageEnter.y, ImageEnter.handle, TRUE);	//TITLE TO ENTERKEYの描画

	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//タイトル背景画像
	strcpy_s(ImageTitle.path, IMG_SOUGEN);			//パスの設定
	ImageTitle.handle = LoadGraph(ImageTitle.path);	//読み込み
	if (ImageTitle.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SOUGEN, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);	//画像の幅と高さを取得
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;					//左右中央揃え
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;					//上下中央揃え

	//プレイ画面背景画像
	strcpy_s(ImagePlay.path, IMG_SORA);				//パスの設定
	ImagePlay.handle = LoadGraph(ImagePlay.path);	//読み込み
	if (ImagePlay.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SORA, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImagePlay.handle, &ImagePlay.width, &ImagePlay.height);	//画像の幅と高さを取得
	ImagePlay.x = GAME_WIDTH / 2 - ImagePlay.width / 2;						//左右中央揃え
	ImagePlay.y = GAME_HEIGHT / 2 - ImagePlay.height / 2;					//上下中央揃え

	//タイトルロゴ
	strcpy_s(ImageTitleROGO.path, IMG_LOGO);				//パスの設定
	ImageTitleROGO.handle = LoadGraph(ImageTitleROGO.path);	//読み込み
	if (ImageTitleROGO.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_LOGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.handle, &ImageTitleROGO.width, &ImageTitleROGO.height);	//画像の幅と高さを取得
	ImageTitleROGO.x = GAME_WIDTH / 2 - ImageTitleROGO.width / 2;						//左右中央揃え
	ImageTitleROGO.y = GAME_HEIGHT / 2 - ImageTitleROGO.height / 2;						//上下中央揃え

	//エンド画面(GAME CLEAR)の画像
	strcpy_s(ImageTitleCLEAR.path, IMG_LOGO_CLEAR);				//パスの設定
	ImageTitleCLEAR.handle = LoadGraph(ImageTitleCLEAR.path);	//読み込み
	if (ImageTitleCLEAR.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_LOGO_CLEAR, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleCLEAR.handle, &ImageTitleCLEAR.width, &ImageTitleCLEAR.height);	//画像の幅と高さを取得
	ImageTitleCLEAR.x = GAME_WIDTH / 2 - ImageTitleCLEAR.width / 2;							//左右中央揃え
	ImageTitleCLEAR.y = GAME_HEIGHT / 2 - ImageTitleCLEAR.height / 2;						//上下中央揃え

	//エンド画面(GAME OVER)の画像
	strcpy_s(ImageTitleOVER.path, IMG_LOGO_OVER);			//パスの設定
	ImageTitleOVER.handle = LoadGraph(ImageTitleOVER.path);	//読み込み
	if (ImageTitleOVER.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_LOGO_OVER, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleOVER.handle, &ImageTitleOVER.width, &ImageTitleOVER.height);	//画像の幅と高さを取得
	ImageTitleOVER.x = GAME_WIDTH / 2 - ImageTitleOVER.width / 2;						//左右中央揃え
	ImageTitleOVER.y = GAME_HEIGHT / 2 - ImageTitleOVER.height / 2;						//上下中央揃え

	//PLAY TO SPACEKEY!の画像
	strcpy_s(ImageSpace.path, IMG_SPACE);			//パスの設定
	ImageSpace.handle = LoadGraph(ImageSpace.path);	//読み込み
	if (ImageSpace.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SPACE, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageSpace.handle, &ImageSpace.width, &ImageSpace.height);	//画像の幅と高さを取得
	ImageSpace.x = GAME_WIDTH / 2 - ImageSpace.width / 2;					//左右中央揃え
	ImageSpace.y = GAME_HEIGHT / 2 + ImageSpace.height + 100;				//上下中央揃え

	//RETRY TO SPACEKEY!の画像
	strcpy_s(ImageSpace2.path, IMG_SPACE2);			//パスの設定
	ImageSpace2.handle = LoadGraph(ImageSpace2.path);	//読み込み
	if (ImageSpace2.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SPACE2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageSpace2.handle, &ImageSpace2.width, &ImageSpace2.height);	//画像の幅と高さを取得
	ImageSpace2.x = GAME_WIDTH / 2 - ImageSpace2.width / 2;					//左右中央揃え
	ImageSpace2.y = GAME_HEIGHT / 2 + ImageSpace2.height + 30;				//上下中央揃え

	//NEXT TO SPACEKEY!の画像
	strcpy_s(ImageSpace3.path, IMG_SPACE3);			//パスの設定
	ImageSpace3.handle = LoadGraph(ImageSpace3.path);	//読み込み
	if (ImageSpace3.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_SPACE3, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageSpace3.handle, &ImageSpace3.width, &ImageSpace3.height);	//画像の幅と高さを取得
	ImageSpace3.x = GAME_WIDTH / 2 - ImageSpace3.width / 2;					//左右中央揃え
	ImageSpace3.y = GAME_HEIGHT / 2 + ImageSpace3.height + 30;				//上下中央揃え

	//TITLE TO ENTERKEY!!!の画像
	strcpy_s(ImageEnter.path, IMG_ENTER);			//パスの設定
	ImageEnter.handle = LoadGraph(ImageEnter.path);	//読み込み
	if (ImageEnter.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMG_ENTER, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEnter.handle, &ImageEnter.width, &ImageEnter.height);	//画像の幅と高さを取得
	ImageEnter.x = GAME_WIDTH / 2 - ImageEnter.width / 2;					//左右中央揃え
	ImageEnter.y = GAME_HEIGHT / 2 + ImageEnter.height + 80;				//上下中央揃え

	//プレイヤーの画像
	strcpy_s(player.image.path, IMG_MARU);				//パスの設定
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
	DeleteGraph(ImageTitleCLEAR.handle);
	DeleteGraph(ImageTitleOVER.handle);
	DeleteGraph(ImageSpace.handle);
	DeleteGraph(ImageEnter.handle);
	DeleteGraph(ImageQuestion.handle);

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{
	//スタート画面BGMの読み込み
	strcpy_s(BGM_START.path, MUSIC_START_PATH);			//パスの設定
	BGM_START.handle = LoadSoundMem(BGM_START.path);	//読み込み
	if (BGM_START.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイ画面BGMの読み込み
	strcpy_s(BGM_PLAY.path, MUSIC_PLAY_PATH);		//パスの設定
	BGM_PLAY.handle = LoadSoundMem(BGM_PLAY.path);	//読み込み
	if (BGM_PLAY.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//クリア画面BGMの読み込み
	strcpy_s(BGM_CLEAR.path, MUSIC_CLEAR_PATH);			//パスの設定
	BGM_CLEAR.handle = LoadSoundMem(BGM_CLEAR.path);	//読み込み
	if (BGM_CLEAR.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_CLEAR_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ゲームオーバー画面BGMの読み込み
	strcpy_s(BGM_OVER.path, MUSIC_OVER_PATH);		//パスの設定
	BGM_OVER.handle = LoadSoundMem(BGM_OVER.path);	//読み込み
	if (BGM_OVER.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_OVER_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
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

	//ジャンプSEの読み込み
	strcpy_s(BGM_JUMP1.path, MUSIC_JUMP1_PATH);			//パスの設定
	BGM_JUMP1.handle = LoadSoundMem(BGM_JUMP1.path);	//読み込み
	if (BGM_JUMP1.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_JUMP1_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//二段ジャンプSEの読み込み
	strcpy_s(BGM_JUMP2.path, MUSIC_JUMP2_PATH);		    //パスの設定
	BGM_JUMP2.handle = LoadSoundMem(BGM_JUMP2.path);	//読み込み
	if (BGM_JUMP2.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_JUMP2_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//スターSEの読み込み
	strcpy_s(BGM_STAR.path, MUSIC_STAR_PATH);		//パスの設定
	BGM_STAR.handle = LoadSoundMem(BGM_STAR.path);	//読み込み
	if (BGM_STAR.handle == -1)
	{
		//	エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_STAR_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//音楽をまとめて削除する関数
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
int MY_CHECK_BLOCK_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとブロックが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//通常ブロックのときは、1を返す
				if (map[tate][yoko].kind == b) { return 1; }

				//動くブロックのときは、2を返す
				if (map[tate][yoko].kind == a) { return 2; }

			}
		}
	}

	return FALSE;
}

//プレイヤーとスターの当たり判定をする関数
int MY_CHECK_STAR_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとスターが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//スター1のときは、1を返す
				if (map[tate][yoko].kind == h1) { return 1; }

				//スター2のときは、2を返す
				if (map[tate][yoko].kind == h2) { return 2; }

				//スター3のときは、3を返す
				if (map[tate][yoko].kind == h3) { return 3; }

			}
		}
	}

	return FALSE;
}

//プレイヤーとトゲの当たり判定をする関数
int MY_CHECK_TOGE_PLAYER_COLL(RECT player)
{
	//マップチップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとトゲが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//通常トゲのときは、1を返す
				if (map[tate][yoko].kind == n) { return 1; }

				//動くトゲのときは、2を返す
				if (map[tate][yoko].kind == m) { return 2; }

				//縦に動くトゲのときは3を返す
				if (map[tate][yoko].kind == v) { return 3; }

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

//プレイヤーの動きの処理の関数
VOID PLAYER_MOVE(VOID)
{

	//ジャンプフラグがTRUEでWキーを押していてプレイヤーとブロックがあたっていたらジャンプ
	if (Jumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		//ジャンプSEを流す
		ChangeVolumeSoundMem(255 * 60 / 100, BGM_JUMP1.handle);	//60%の音量にする
		PlaySoundMem(BGM_JUMP1.handle, DX_PLAYTYPE_BACK);

		JumpPower = 13;			//約1ブロック分のジャンプ
		Jumpflag = FALSE;		//ジャンプフラグをFALSEにする
		WKeyflag = TRUE;		//WキーフラグをTRUEにする

		// 文字列の描画
		DrawString(0, 0, "W", GetColor(255, 0, 0));

	}

	//二段ジャンプフラグがTRUEでWキーを押していたら空中ジャンプ
	if (WJumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE)
	{
		//二段ジャンプSEを流す
		ChangeVolumeSoundMem(255 * 60 / 100, BGM_JUMP2.handle);	//60%の音量にする
		PlaySoundMem(BGM_JUMP2.handle, DX_PLAYTYPE_BACK);

		JumpPower = 13;			//２ブロック分のジャンプ
		WJumpflag = FALSE;		//二段ジャンプフラグをFALSEにする
		WKeyflag = FALSE;		//WキーフラグをFALSEにする

		// 文字列の描画
		DrawString(0, 0, "W", GetColor(255, 0, 0));

	}

	//Wキーを離してプレイヤーが地面につくと
	if (CheckHitKey(KEY_INPUT_W) == FALSE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 1)
	{
		Jumpflag = TRUE;		//ジャンプフラグをTRUEにし、ジャンプができるようになる
	}

	//WキーフラグがTRUEかつWキーを離すと
	if (WKeyflag == TRUE && CheckHitKey(KEY_INPUT_W) == FALSE)
	{
		WJumpflag = TRUE;		//二段ジャンプフラグをTRUEにし、二段ジャンプができるようになる
	}

	//ブロックから落ちてしまったときに二段ジャンプ
	if (Jumpflag == TRUE && CheckHitKey(KEY_INPUT_W) == TRUE && MY_CHECK_BLOCK_PLAYER_COLL(player.coll) == 0)
	{
		//ジャンプSEを流す
		ChangeVolumeSoundMem(255 * 60 / 100, BGM_JUMP1.handle);	//60%の音量にする
		PlaySoundMem(BGM_JUMP1.handle, DX_PLAYTYPE_BACK);

		JumpPower = 13;			//約1ブロック分のジャンプ
		Jumpflag = FALSE;		//ジャンプフラグをFALSEにする
		WKeyflag = TRUE;		//WキーフラグをTRUEにする

		// 文字列の描画
		DrawString(0, 0, "W", GetColor(255, 0, 0));

	}

	// 落下処理
	player.CenterY -= JumpPower;
	player.image.y -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 1;

	//Dキーで右へ進む
	if (CheckHitKey(KEY_INPUT_D) == TRUE)
	{
		player.image.x += player.speed;
		player.CenterX += player.speed;

		// 文字列の描画
		DrawString(0,0, "D", GetColor(255, 0, 0));

	}

	//Aキーで左へ進む
	if (CheckHitKey(KEY_INPUT_A) == TRUE)
	{
		player.image.x -= player.speed;
		player.CenterX -= player.speed;

		// 文字列の描画
		DrawString(0, 0, "A", GetColor(255, 0, 0));

	}

}