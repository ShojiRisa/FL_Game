#include "DxLib.h"
#include<stdlib.h>//文字表示機能を表示する
#include<stdio.h>//ポーズ機能を導入する
#include<math.h>//数学的演算
#include<time.h>//時間を利用

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "育ててスライムつくって終焉";

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
	int gh[20];
	gh[0] = LoadGraph("R/TITLE.png");//タイトル
	gh[1] = LoadGraph("R/RULE.png");//操作説明
	gh[2] = LoadGraph("R/GAMESCENE.png");//ゲームシーン
	gh[3] = LoadGraph("R/ZUKAN.png");//図鑑
	gh[4] = LoadGraph("R/HIGHHANDEDEND.png");//高飛車エンド
	gh[5] = LoadGraph("R/YOURDINNEREND.png");//お前晩御飯エンド
	gh[6] = LoadGraph("R/SLIMEDEATHEND.png");//スライム死亡エンド
	gh[7] = LoadGraph("R/SLIMEISSHOGGOTHEND.png");//スライムショゴスエンド
	gh[8] = LoadGraph("R/BEAUTIFULGIRLEND.png");//美少女エンド
	gh[9] = LoadGraph("R/NORMALSLIMEEND.png");//普通スライムエンド
	gh[10] = LoadGraph("R/FINISEND.png");//終焉エンド
	gh[11] = LoadGraph("R/Day.png");//日数
	gh[12] = LoadGraph("R/parameters_icon.png");
	gh[13] = LoadGraph("R/kawaisa.png");
	gh[14] = LoadGraph("R/situkeru.png");
	gh[15] = LoadGraph("R/gohann.png");
	gh[16] = LoadGraph("R/unndou.png");
	gh[17] = LoadGraph("R/zukann.png");
	gh[18] = LoadGraph("R/ikuseikaisi.png");
	gh[19] = LoadGraph("R/sousa.png");


	int slimeGraph[6];
	LoadDivGraph("R/slime.png", 6, 6, 1, 256, 256, slimeGraph);

	int scoreGraph[10];
	LoadDivGraph("R/number.png", 10, 16, 1, 96, 96, scoreGraph);

	int gageGraph[5];
	LoadDivGraph("R/parameters_gage.png", 5, 5, 1, 48, 48, gageGraph);

	/*int paraGraph[5];
	LoadDivGraph("R/parameters_icon.png", 5, 5, 1, 48, 48, paraGraph);*/


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

		CUTE,
		STUDY,
		MOVE,
		HUNGRY,

	};
	Scene scene = TITLE;

	//マウス情報の初期化
	int OldMouse = 0;
	int NewMouse = 0;
	//プレイヤー移動用変数
	int MouseX = 0;
	int MouseY = 0;

	int cute = 0; //ハート
	int study = 0; //スペード
	int hungry = 0; //クローバー
	int move = 0; //ひし形

	int count = 0;
	int timer = 0;

	int pink = 0;
	int blue = 0;
	int green = 0;
	int yellow = 0;
	int red = 0;

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

			// スタート画面が押されている
			if ((MouseX > 400) && (MouseX < 750) && (MouseY > 400) && (MouseY < 500) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
			}
			//操作説明が押されている
			if ((MouseX > 400) && (MouseX < 750) && (MouseY > 550) && (MouseY < 650) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = RULE;
			}
		}

		if (scene == RULE)//操作説明
		{
			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;
			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//クレジットが押されている
			if ((MouseX > 900) && (MouseX < 1200) && (MouseY > 600) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = TITLE;
			}

		}

		if (scene == ZUKAN)//図鑑
		{

			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;
			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);
			//クレジットが押されている
			if ((MouseX > 900) && (MouseX < 1200) && (MouseY > 600) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
			}
		}

		if (scene == GAMESCENE)//ゲームシーン
		{
			timer = 0;
			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;

			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//かわいさ
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
			{
				cute = cute + 3;
				scene = CUTE;
				count = count + 1;
				pink = pink + 1;
			}
			//かしこさ
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
			{
				study = study + 3;
				scene = STUDY;
				count = count + 1;
				blue = blue + 1;
			}
			//おなか
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
			{
				hungry = hungry + 3;
				scene = HUNGRY;
				count = count + 1;
				green = green + 1;
			}
			//うんどう
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 525) && (MouseY < 630) && (NewMouse == 1 && OldMouse == 0))
			{
				move = move + 3;
				scene = MOVE;
				count = count + 1;
				yellow = yellow + 1;
			}

			if ((MouseX > 400) && (MouseX < 700) && (MouseY > 0) && (MouseY < 100) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = ZUKAN;
			}

		}

		//連打防止
		if (scene == CUTE)//かわいさが上昇
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == STUDY)//かしこさが上昇
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == HUNGRY)//おなかが上昇
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == MOVE)//うんどうが上昇
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}



		//エンド
		if (cute == 21)
		{
			scene = HIGHHANDEDEND;
		}
		if (study == 21)
		{
			scene = SLIMEDEATHEND;
		}
		if (hungry == 21)
		{
			scene = YOURDINNEREND;
		}
		if (move == 21)
		{
			scene = SLIMEISSHOGGOTHEND;
		}


		//*******************************************************************************************************************
		//ここからエンド分岐
		if (scene == HIGHHANDEDEND)//高飛車エンド
		{

		}

		if (scene == SLIMEDEATHEND)//スライム死亡エンド
		{

		}

		if (scene == YOURDINNEREND)//お前晩御飯エンド
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
			DrawGraph(0, 0, gh[0], TRUE);//背景画像

			//DrawBox(400, 400, 750, 500, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 400, gh[18], TRUE);//ゲーム開始
			//DrawBox(400, 550, 750, 650, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 550, gh[19], TRUE);//操作説明


			//DrawGraph(100, 100, gageGraph[0], TRUE);//仮画像

		}

		if (scene == RULE)//操作説明
		{
			DrawGraph(0, 0, gh[1], TRUE);
			DrawBox(900, 600, 1200, 700, GetColor(0, 0, 0), TRUE);    // 四角形を描画
		}

		//ゲーム画面
		if (scene == GAMESCENE)//ゲームシーン
		{

			DrawGraph(0, 0, gh[2], TRUE);

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 0, gh[17], TRUE); //ずかん
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 150, gh[13], TRUE);//日数//かわいがる
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawGraph(50, 275, gh[14], TRUE);//しつける
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 400, gh[15], TRUE);//ごはん
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 525, gh[16], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//スライム
			DrawGraph(0, 0, gh[11], TRUE);//日数

			//日付のカウント
			if (count == 0)
			{
				DrawGraph(180, 0, scoreGraph[0], TRUE);
			}
			if (count == 1)
			{
				DrawGraph(180, 0, scoreGraph[1], TRUE);
			}
			if (count == 2)
			{
				DrawGraph(180, 0, scoreGraph[2], TRUE);
			}
			if (count == 3)
			{
				DrawGraph(180, 0, scoreGraph[3], TRUE);
			}
			if (count == 4)
			{
				DrawGraph(180, 0, scoreGraph[4], TRUE);
			}
			if (count == 5)
			{
				DrawGraph(180, 0, scoreGraph[5], TRUE);
			}
			if (count == 6)
			{
				DrawGraph(180, 0, scoreGraph[6], TRUE);
			}

			DrawGraph(700, 0, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(752, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(772, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(792, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(812, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(832, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(852, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(872, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(752, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(772, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(792, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(812, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(832, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(852, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(872, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(992, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1012, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1032, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1052, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1072, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1092, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1112, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(992, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1012, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1032, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1052, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1072, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1092, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1112, 50, gageGraph[3], TRUE);
			}

			////怒りゲージ
			//if (red >= 1)
			//{
			//	DrawGraph(1092, 522, gageGraph[4], TRUE);
			//}
			//if (red >= 2)
			//{
			//	DrawGraph(1092, 474, gageGraph[4], TRUE);
			//}
			//if (red >= 3)
			//{
			//	DrawGraph(1092, 426, gageGraph[4], TRUE);
			//}
			//if (red >= 4)
			//{
			//	DrawGraph(1092, 378, gageGraph[4], TRUE);
			//}
			//if (red >= 5)
			//{
			//	DrawGraph(1092, 330, gageGraph[4], TRUE);
			//}
			//if (red >= 6)
			//{
			//	DrawGraph(1092, 282, gageGraph[4], TRUE);
			//}
			//if (red >= 7)
			//{
			//	DrawGraph(1092, 240, gageGraph[4], TRUE);
			//}
		}

		//かわいさが上昇
		if (scene == CUTE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[1], TRUE);//スライム描画

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 0, gh[17], TRUE); //ずかん
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 150, gh[13], TRUE);//日数//かわいがる
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawGraph(50, 275, gh[14], TRUE);//しつける
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 400, gh[15], TRUE);//ごはん
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 525, gh[16], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);

			//DrawGraph(600, 300, slimeGraph[0], TRUE);//スライム
			DrawGraph(0, 0, gh[11], TRUE);//日数

			//日付のカウント
			if (count == 0)
			{
				DrawGraph(180, 0, scoreGraph[0], TRUE);
			}
			if (count == 1)
			{
				DrawGraph(180, 0, scoreGraph[1], TRUE);
			}
			if (count == 2)
			{
				DrawGraph(180, 0, scoreGraph[2], TRUE);
			}
			if (count == 3)
			{
				DrawGraph(180, 0, scoreGraph[3], TRUE);
			}
			if (count == 4)
			{
				DrawGraph(180, 0, scoreGraph[4], TRUE);
			}
			if (count == 5)
			{
				DrawGraph(180, 0, scoreGraph[5], TRUE);
			}
			if (count == 6)
			{
				DrawGraph(180, 0, scoreGraph[6], TRUE);
			}

			DrawGraph(700, 0, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(752, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(772, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(792, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(812, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(832, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(852, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(872, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(752, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(772, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(792, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(812, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(832, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(852, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(872, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(992, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1012, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1032, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1052, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1072, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1092, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1112, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(992, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1012, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1032, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1052, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1072, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1092, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1112, 50, gageGraph[3], TRUE);
			}

		}

		//かしこさが上昇
		if (scene == STUDY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[5], TRUE);//スライム描画

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 0, gh[17], TRUE); //ずかん
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 150, gh[13], TRUE);//日数//かわいがる
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawGraph(50, 275, gh[14], TRUE);//しつける
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 400, gh[15], TRUE);//ごはん
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 525, gh[16], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//スライム
			DrawGraph(0, 0, gh[11], TRUE);//日数

			//日付のカウント
			if (count == 0)
			{
				DrawGraph(180, 0, scoreGraph[0], TRUE);
			}
			if (count == 1)
			{
				DrawGraph(180, 0, scoreGraph[1], TRUE);
			}
			if (count == 2)
			{
				DrawGraph(180, 0, scoreGraph[2], TRUE);
			}
			if (count == 3)
			{
				DrawGraph(180, 0, scoreGraph[3], TRUE);
			}
			if (count == 4)
			{
				DrawGraph(180, 0, scoreGraph[4], TRUE);
			}
			if (count == 5)
			{
				DrawGraph(180, 0, scoreGraph[5], TRUE);
			}
			if (count == 6)
			{
				DrawGraph(180, 0, scoreGraph[6], TRUE);
			}

			DrawGraph(700, 0, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(752, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(772, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(792, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(812, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(832, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(852, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(872, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(752, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(772, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(792, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(812, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(832, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(852, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(872, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(992, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1012, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1032, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1052, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1072, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1092, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1112, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(992, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1012, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1032, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1052, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1072, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1092, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1112, 50, gageGraph[3], TRUE);
			}
		}

		//おなかが上昇
		if (scene == HUNGRY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[3], TRUE);//スライム描画

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 0, gh[17], TRUE); //ずかん
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 150, gh[13], TRUE);//日数//かわいがる
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawGraph(50, 275, gh[14], TRUE);//しつける
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 400, gh[15], TRUE);//ごはん
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 525, gh[16], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//スライム
			DrawGraph(0, 0, gh[11], TRUE);//日数

			//日付のカウント
			if (count == 0)
			{
				DrawGraph(180, 0, scoreGraph[0], TRUE);
			}
			if (count == 1)
			{
				DrawGraph(180, 0, scoreGraph[1], TRUE);
			}
			if (count == 2)
			{
				DrawGraph(180, 0, scoreGraph[2], TRUE);
			}
			if (count == 3)
			{
				DrawGraph(180, 0, scoreGraph[3], TRUE);
			}
			if (count == 4)
			{
				DrawGraph(180, 0, scoreGraph[4], TRUE);
			}
			if (count == 5)
			{
				DrawGraph(180, 0, scoreGraph[5], TRUE);
			}
			if (count == 6)
			{
				DrawGraph(180, 0, scoreGraph[6], TRUE);
			}

			DrawGraph(700, 0, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(752, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(772, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(792, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(812, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(832, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(852, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(872, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(752, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(772, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(792, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(812, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(832, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(852, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(872, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(992, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1012, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1032, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1052, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1072, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1092, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1112, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(992, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1012, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1032, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1052, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1072, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1092, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1112, 50, gageGraph[3], TRUE);
			}

		}

		//うんどうが上昇
		if (scene == MOVE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[4], TRUE);//スライム描画

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // 四角形を描画
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // 四角形を描画
			DrawGraph(400, 0, gh[17], TRUE); //ずかん
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 150, gh[13], TRUE);//日数//かわいがる
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // 四角形を描画
			DrawGraph(50, 275, gh[14], TRUE);//しつける
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 400, gh[15], TRUE);//ごはん
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // 四角形を描画
			DrawGraph(50, 525, gh[16], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//スライム
			DrawGraph(0, 0, gh[11], TRUE);//日数

			//日付のカウント
			if (count == 0)
			{
				DrawGraph(180, 0, scoreGraph[0], TRUE);
			}
			if (count == 1)
			{
				DrawGraph(180, 0, scoreGraph[1], TRUE);
			}
			if (count == 2)
			{
				DrawGraph(180, 0, scoreGraph[2], TRUE);
			}
			if (count == 3)
			{
				DrawGraph(180, 0, scoreGraph[3], TRUE);
			}
			if (count == 4)
			{
				DrawGraph(180, 0, scoreGraph[4], TRUE);
			}
			if (count == 5)
			{
				DrawGraph(180, 0, scoreGraph[5], TRUE);
			}
			if (count == 6)
			{
				DrawGraph(180, 0, scoreGraph[6], TRUE);
			}

			DrawGraph(700, 0, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(752, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(772, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(792, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(812, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(832, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(852, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(872, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(752, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(772, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(792, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(812, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(832, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(852, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(872, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(992, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1012, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1032, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1052, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1072, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1092, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1112, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(992, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1012, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1032, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1052, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1072, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1092, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1112, 50, gageGraph[3], TRUE);
			}

		}

		if (scene == ZUKAN)//図鑑一覧の描画
		{
			DrawGraph(0, 0, gh[3], TRUE);
			DrawBox(900, 600, 1200, 700, GetColor(0, 0, 0), TRUE);    // 四角形を描画
		}

		//ここから各エンド************************************************************************************

		if (scene == HIGHHANDEDEND)//高飛車エンド
		{
			DrawGraph(0, 0, gh[4], TRUE);
		}

		if (scene == YOURDINNEREND)//お前晩御飯エンド
		{
			DrawGraph(0, 0, gh[5], TRUE);
		}

		if (scene == SLIMEDEATHEND)//スライム死亡エンド
		{
			DrawGraph(0, 0, gh[6], TRUE);
		}

		if (scene == SLIMEISSHOGGOTHEND)//スライム＝ショゴスエンド
		{
			DrawGraph(0, 0, gh[7], TRUE);
		}

		if (scene == BEAUTIFULGIRLEND)//美少女エンド
		{
			DrawGraph(0, 0, gh[8], TRUE);
		}

		if (scene == NORMALSLIMEEND)//普通スライムエンド
		{
			DrawGraph(0, 0, gh[9], TRUE);
		}

		if (scene == FINISEND)// 終焉エンド
		{
			DrawGraph(0, 0, gh[10], TRUE);
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