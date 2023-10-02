#include "DxLib.h"
#include<stdlib.h>//文字表示機能を表示する
#include<stdio.h>//ポーズ機能を導入する
#include<math.h>//数学的演算
#include<time.h>//時間を利用

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "卒業制作";

// ウィンドウ横幅
const int WIN_WIDTH = 1200;

// ウィンドウ縦幅
const int WIN_HEIGHT = 700;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	// R/はリソースファイルの意味　エクスプローラーにあります
	int gh[1];
	gh[0] = LoadGraph("R/.png");//

	//音楽入れるようの変数
	int sound[1];
	sound[0] = LoadSoundMem("R/.mp3");//
	ChangeVolumeSoundMem(100, sound[0]);//音量

	// ゲームループで使う変数の宣言
	//シーン管理用変数
	enum Scene {
		TITLE,		//0　タイトル画面
		RULE,	//1　操作説明
		CREDIT,	//2　クレジット
		SELECT,
		WAITING,	//　待機画面
		STAGE_1,
		STAGE_2,
		TUTORIAL,	//
		CLEAR,		//
		GAMEOVER,	// 
	};
	Scene scene = TITLE;

	//マウス情報の初期化
	int OldMouse = 0;
	int NewMouse = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// マウスを表示状態にする
	SetMouseDispFlag(FALSE);

	//音楽を流す
	PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

	// マウスを非表示状態にする
	SetMouseDispFlag(TRUE);

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		if (scene == TITLE)//スタート画面
		{
		
		}

		//ステージ選択画面
		if (scene == SELECT)
		{
	
		}

		//待機画面
		if (scene == WAITING)
		{
		
		}

		if (scene == RULE)//操作説明
		{
			
		}

		if (scene == CREDIT)//クレジット
		{
			
		}

		//ゲーム画面1
		if (scene == STAGE_1)
		{
			
		}
		//ゲーム画面2
		if (scene == STAGE_2)
		{
			
		}

		//エンド分岐　クリア
		if (scene == CLEAR)
		{
			
		}

		//エンド分岐　ゲームオーバー
		if (scene == GAMEOVER)
		{
			
		}

//*******************************************************************************************************************

		// 描画処理

		if (scene == TITLE)//タイトル画面
		{
		
		}
		//ステージ選択画面
		if (scene == SELECT)
		{
			
		}

		if (scene == WAITING)//スタート画面
		{
			
		}
		if (scene == RULE)//操作説明
		{
			
		}
		if (scene == CREDIT)//クレジット
		{
			
		}

		//ゲーム画面 ステージ1
		if (scene == STAGE_1)
		{
			
		}
		//ゲーム画面　ステージ2
		if (scene == STAGE_2)
		{
			
		}

		//エンド分岐　クリア
		if (scene == CLEAR)
		{
			
		}

		//エンド分岐　ゲームオーバー
		if (scene == GAMEOVER)
		{
		
		}

		// マウスの位置を取得
		//GetMousePoint(&, &);


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}