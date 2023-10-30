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
		TITLE,		          //1　タイトル画面
		RULE,                 //2　操作説明
		GAMESCENE,            //3　ゲームシーン
		ZUKAN,                //4　図鑑
		HIGHHANDEDEND,        //5　高飛車エンド
		YOURDINNEREND,        //6　お前晩御飯エンド
		SLIMEDEATHEND,        //7　スライム死亡エンド
		SLIMEISSHOGGOTHEND,   //8　スライム＝ショゴスエンド
		BEAUTIFULGIRLEND,     //9　美少女エンド
		NORMALSLIMEEND,       //10 普通スライムエンド
		FINISEND,             //11 終焉エンド
		LNITIALIZATION,       //12 初期化
		
	};
	Scene scene = TITLE;

	//マウス情報の初期化
	int OldMouse = 0;
	int NewMouse = 0;
	//プレイヤー移動用変数
	int MouseX = 0;
	int MouseY = 0;


	int cute = 0;
	int study = 0;
	int move = 0;
	int hungry = 0;

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
		if (scene == TITLE)//タイトル
		{
			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;
			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			if ((NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
			}
		
		}

		
		if (scene == RULE)//操作説明
		{
			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;
			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		}

		
		if (scene == GAMESCENE)//ゲームシーン
		{

			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;

			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//かわいさ
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
			{
				cute = cute + 3;
			}
			//かしこさ
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
			{
				study = study + 3;
			}
			//おなか
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
			{
				hungry = hungry + 3;
			}
			//うんどう
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 525) && (MouseY < 630) && (NewMouse == 1 && OldMouse == 0))
			{
				move = move + 3;
			}

			if ((MouseX > 400) && (MouseX < 700) && (MouseY > 0) && (MouseY < 100) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = ZUKAN;
			}

		}

		if (scene == ZUKAN)//図鑑
		{
			
		}

		if (scene == HIGHHANDEDEND)//高飛車エンド
		{
			
		}

		
		if (scene == SLIMEDEATHEND)//スライム死亡エンド
		{
			
		}
		
		if (scene == SLIMEISSHOGGOTHEND)//スライム＝ショゴスエンド
		{
			
		}

		
		if (scene == BEAUTIFULGIRLEND)//美少女エンド
		{
			
		}

		
		if (scene == NORMALSLIMEEND)//普通スライムエンド
		{
			
		}

		if (scene == FINISEND)// 終焉エンド
		{

		}

		if (scene == LNITIALIZATION)//初期化
		{

		}

		
//*******************************************************************************************************************

		// 描画処理

		if (scene == TITLE)//タイトル画面
		{
			//DrawGraph(0, 0, gh[0], TRUE);//背景画像

		}
		
		if (scene == RULE)//操作説明
		{

		}
		
		if (scene == GAMESCENE)//ゲームシーン
		{

			DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawBox(700, 0, 1200, 100, GetColor(255, 0, 0), TRUE);    // 四角形を描画

			DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画

			DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);
		}

		if (scene == ZUKAN)//図鑑
		{

		}
		
		if (scene == HIGHHANDEDEND)//高飛車エンド
		{

		}


		if (scene == SLIMEDEATHEND)//スライム死亡エンド
		{

		}

		if (scene == SLIMEISSHOGGOTHEND)//スライム＝ショゴスエンド
		{

		}

		if (scene == BEAUTIFULGIRLEND)//美少女エンド
		{

		}

		if (scene == NORMALSLIMEEND)//普通スライムエンド
		{

		}

		if (scene == FINISEND)// 終焉エンド
		{

		}

		// マウスの位置を取得
		GetMousePoint(&MouseX, &MouseY);


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