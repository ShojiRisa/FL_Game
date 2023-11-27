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
	int gh[23];
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
	/*gh[13] = LoadGraph("R/kawaisa.png");
	gh[14] = LoadGraph("R/situkeru.png");
	gh[15] = LoadGraph("R/gohann.png");
	gh[16] = LoadGraph("R/unndou.png");
	gh[17] = LoadGraph("R/zukann.png");
	gh[18] = LoadGraph("R/ikuseikaisi.png");
	gh[19] = LoadGraph("R/sousa.png");*/
	gh[20] = LoadGraph("R/UI_book.png");//図鑑
	gh[21] = LoadGraph("R/UI_return.png");//戻るボタン
	gh[22] = LoadGraph("R/Secret.png");//進化直前画像


	int slimeGraph[6];
	LoadDivGraph("R/slime.png", 6, 6, 1, 256, 256, slimeGraph);

	int scoreGraph[10];
	LoadDivGraph("R/number.png", 10, 16, 1, 96, 96, scoreGraph);

	int gageGraph[5];
	LoadDivGraph("R/parameters_gage.png", 5, 5, 1, 48, 44, gageGraph);

	int titleGraph[2];
	LoadDivGraph("R/UI_title.png", 2, 2, 1, 512, 96, titleGraph);

	int choiceGraph[5];
	LoadDivGraph("R/UI_choice.png", 5, 5, 1, 512, 96, choiceGraph);

	int displayGraph[5];
	LoadDivGraph("R/UI_display.png", 5, 5, 1, 416, 96, displayGraph);


	//音楽入れるようの変数
	int sound[15];
	sound[0] = LoadSoundMem("R/1-Title.mp3");//タイトル
	ChangeVolumeSoundMem(100, sound[0]);//音量
	sound[1] = LoadSoundMem("R/2-Sousa.mp3");//操作画面
	ChangeVolumeSoundMem(100, sound[1]);//音量
	sound[2] = LoadSoundMem("R/3-Game.mp3");//ゲーム画面
	ChangeVolumeSoundMem(100, sound[2]);//音量
	sound[3] = LoadSoundMem("R/4-Zukann.mp3");//図鑑
	ChangeVolumeSoundMem(100, sound[3]);//音量
	sound[4] = LoadSoundMem("R/5-HIGHHANDEDEND.mp3");//可愛いエンド
	ChangeVolumeSoundMem(100, sound[4]);//音量
	sound[5] = LoadSoundMem("R/6-YOURDINNEREND.mp3");//晩御飯エンド
	ChangeVolumeSoundMem(100, sound[5]);//音量
	sound[6] = LoadSoundMem("R/7-SLIMEDEATHEND.mp3");//死亡エンド
	ChangeVolumeSoundMem(100, sound[6]);//音量
	sound[7] = LoadSoundMem("R/8-SLIMEISSHOGGOTHEND.mp3");//ショゴスエンド
	ChangeVolumeSoundMem(100, sound[7]);//音量
	//sound[8] = LoadSoundMem("R/9-CLEAR.mp3");//
	//ChangeVolumeSoundMem(100, sound[8]);//音量
	sound[9] = LoadSoundMem("R/10-NORMALSLIMEEND.mp3");//普通スライムエンド
	ChangeVolumeSoundMem(100, sound[9]);//音量
	//sound[10] = LoadSoundMem("R/11-CLEAR.mp3");//
	//ChangeVolumeSoundMem(100, sound[10]);//音量
	sound[11] = LoadSoundMem("R/KIRAKIRA.mp3");//エフェクト
	ChangeVolumeSoundMem(100, sound[11]);//音量
	sound[12] = LoadSoundMem("R/SE.mp3");//SE
	ChangeVolumeSoundMem(100, sound[12]);//音量

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

	int endflag = 0;
	int timeflag = 0;

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
			if ((MouseX > 350) && (MouseX < 850) && (MouseY > 480) && (MouseY < 580) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
				//音楽を止める
				StopSoundMem(sound[0]);
				//音楽を流す
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//音楽を流す
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);

			}
			//操作説明が押されている
			if ((MouseX > 350) && (MouseX < 850) && (MouseY > 580) && (MouseY < 680) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = RULE;
				//音楽を止める
				StopSoundMem(sound[0]);
				//音楽を流す
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//音楽を流す
				PlaySoundMem(sound[1], DX_PLAYTYPE_BACK);
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
				//音楽を止める
				StopSoundMem(sound[1]);
				//音楽を流す
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//音楽を流す
				PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

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
				//音楽を流す
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//音楽を止める
				StopSoundMem(sound[3]);
				//音楽を流す
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);
			}
		}

		//ゲームシーン
		if (scene == GAMESCENE)
		{
			timer = 0;

			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;

			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);


			if (count <= 6)
			{
				//かわいさ
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
				{
					cute = cute + 3;
					scene = CUTE;
					count = count + 1;
					pink = pink + 1;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//かしこさ
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
				{
					study = study + 3;
					scene = STUDY;
					count = count + 1;
					blue = blue + 1;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//うんどう
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
				{
					move = move + 3;
					scene = MOVE;
					count = count + 1;
					green = green + 1;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//おなか
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 525) && (MouseY < 630) && (NewMouse == 1 && OldMouse == 0))
				{
					hungry = hungry + 3;
					scene = HUNGRY;
					count = count + 1;
					yellow = yellow + 1;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}


				if ((MouseX > 400) && (MouseX < 700) && (MouseY > 0) && (MouseY < 100) && (NewMouse == 1 && OldMouse == 0))
				{
					scene = ZUKAN;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
					//音楽を止める
					StopSoundMem(sound[2]);
					//音楽を流す
					PlaySoundMem(sound[3], DX_PLAYTYPE_BACK);
				}
			}

			if (count == 7 && timeflag == 1)
			{

				if ((MouseX > 0) && (MouseX < 1200) && (MouseY > 100) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
				{
					endflag = 1;
					//音楽を流す
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
					//音楽を止める
					StopSoundMem(sound[2]);
					//音楽を流す
					PlaySoundMem(sound[4], DX_PLAYTYPE_BACK);
					//音楽を流す
					PlaySoundMem(sound[6], DX_PLAYTYPE_BACK);
					//音楽を流す
					PlaySoundMem(sound[5], DX_PLAYTYPE_BACK);
					//音楽を流す
					PlaySoundMem(sound[7], DX_PLAYTYPE_BACK);
					//音楽を流す
					PlaySoundMem(sound[9], DX_PLAYTYPE_BACK);
				}
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
		if (count == 7)
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				timeflag = 1;
			}
		}



		//エンド
		if (endflag == 1)
		{
			if (cute >= 21)
			{
				scene = HIGHHANDEDEND;
				//音楽を止める
				StopSoundMem(sound[6]);
				//音楽を止める
				StopSoundMem(sound[5]);
				//音楽を止める
				StopSoundMem(sound[7]);
				//音楽を止める
				StopSoundMem(sound[9]);
			}
			if (study >= 21)
			{
				scene = SLIMEDEATHEND;
				//音楽を止める
				StopSoundMem(sound[4]);
				//音楽を止める
				StopSoundMem(sound[5]);
				//音楽を止める
				StopSoundMem(sound[7]);
				//音楽を止める
				StopSoundMem(sound[9]);
			}
			if (hungry >= 21)
			{
				scene = YOURDINNEREND;
				//音楽を止める
				StopSoundMem(sound[6]);
				//音楽を止める
				StopSoundMem(sound[4]);
				//音楽を止める
				StopSoundMem(sound[7]);
				//音楽を止める
				StopSoundMem(sound[9]);
			}
			if (move >= 21)
			{
				scene = SLIMEISSHOGGOTHEND;
				//音楽を止める
				StopSoundMem(sound[6]);
				//音楽を止める
				StopSoundMem(sound[5]);
				//音楽を止める
				StopSoundMem(sound[4]);
				//音楽を止める
				StopSoundMem(sound[9]);
			}
			else if (cute <= 20 && study <= 20 && hungry <= 20 && move <= 20)
			{
				scene = NORMALSLIMEEND;
				//音楽を止める
				StopSoundMem(sound[6]);
				//音楽を止める
				StopSoundMem(sound[5]);
				//音楽を止める
				StopSoundMem(sound[7]);
				//音楽を止める
				StopSoundMem(sound[4]);
			}
		}



		//*******************************************************************************************************************
		//ここからエンド分岐
		if (scene == HIGHHANDEDEND || SLIMEDEATHEND || YOURDINNEREND || SLIMEISSHOGGOTHEND || NORMALSLIMEEND)//エンド.
		{
			//マウスの初期化　ないと1クリックで全てのシーンがぶっ飛びます
			OldMouse = NewMouse;
			//マウスが左クリックされているか
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0)
			{
				scene = LNITIALIZATION;
			}
		}

		//if (scene == BEAUTIFULGIRLEND)//美少女エンド
		//{

		//}

		//if (scene == FINISEND)// 終焉エンド
		//{

		//}

		if (scene == LNITIALIZATION)//初期化
		{
			scene = TITLE;

			//マウス情報の初期化
			OldMouse = 0;
			NewMouse = 0;
			//プレイヤー移動用変数
			MouseX = 0;
			MouseY = 0;

			cute = 0; //ハート
			study = 0; //スペード
			hungry = 0; //クローバー
			move = 0; //ひし形

			count = 0;
			timer = 0;

			pink = 0;
			blue = 0;
			green = 0;
			yellow = 0;
			red = 0;

			endflag = 0;
			timeflag = 0;
			
			//音楽を止める
			StopSoundMem(sound[4]);
			//音楽を止める
			StopSoundMem(sound[6]);
			//音楽を止める
			StopSoundMem(sound[5]);
			//音楽を止める
			StopSoundMem(sound[7]);
			//音楽を止める
			StopSoundMem(sound[9]);
			//音楽を流す
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);
			//音楽を流す
			PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
		}


		//*******************************************************************************************************************

		// 描画処理

		if (scene == TITLE)//タイトル画面
		{
			//DrawGraph(400, 400, gh[18], TRUE);//ゲーム開始
			//DrawGraph(400, 550, gh[19], TRUE);//操作説明
			DrawGraph(0, 0, gh[2], TRUE);
			DrawGraph(220, 50, gh[0], TRUE);//背景画像
			DrawGraph(350, 480, titleGraph[0], TRUE);
			DrawGraph(350, 580, titleGraph[1], TRUE);
		}

		if (scene == RULE)//操作説明
		{

			DrawGraph(0, 0, gh[2], TRUE);//背景

			DrawGraph(50, 150, choiceGraph[0], TRUE);//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			DrawGraph(750, 390, slimeGraph[0], TRUE);//スライム

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
			DrawGraph(0, 0, gh[11], TRUE);//日数

			DrawGraph(180, 0, scoreGraph[0], TRUE);

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			DrawGraph(900, 600, gh[21], TRUE); //戻る
			DrawGraph(0, 0, gh[1], TRUE);//操作説明
		}



		//ゲーム画面
		if (scene == GAMESCENE)//ゲームシーン
		{

			DrawGraph(0, 0, gh[2], TRUE);//背景

			DrawGraph(50, 150, choiceGraph[0], TRUE);//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			/*DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);*/

			DrawGraph(750, 390, slimeGraph[0], TRUE);//スライム

			if (count == 7 && timeflag == 1)
			{
				DrawGraph(0, 0, gh[2], TRUE);//背景
				DrawGraph(0, 0, gh[22], TRUE);//背景
			}

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
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
			if (count == 7)
			{
				DrawGraph(180, 0, scoreGraph[7], TRUE);
			}

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(820, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(840, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(860, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(880, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(900, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(920, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(940, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(820, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(840, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(860, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(880, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(900, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(920, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(940, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(1030, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1050, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1070, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1090, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1110, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1130, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1150, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(1030, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1050, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1070, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1090, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1110, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1130, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1150, 50, gageGraph[3], TRUE);
			}
		}

		//かわいさが上昇
		if (scene == CUTE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[1], TRUE);//スライム描画

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			DrawGraph(50, 150, choiceGraph[0], TRUE);//日数//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ
			DrawGraph(700, 150, displayGraph[0], TRUE);//チャットウインドウを表示

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			/*DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);*/

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
			if (count == 7)
			{
				DrawGraph(180, 0, scoreGraph[7], TRUE);
			}

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(820, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(840, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(860, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(880, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(900, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(920, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(940, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(820, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(840, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(860, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(880, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(900, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(920, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(940, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(1030, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1050, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1070, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1090, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1110, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1130, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1150, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(1030, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1050, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1070, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1090, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1110, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1130, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1150, 50, gageGraph[3], TRUE);
			}

		}

		//かしこさが上昇
		if (scene == STUDY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[5], TRUE);//スライム描画

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			DrawGraph(50, 150, choiceGraph[0], TRUE);//日数//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ
			DrawGraph(700, 150, displayGraph[1], TRUE);//チャットウインドウを表示

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			/*DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);*/

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
			if (count == 7)
			{
				DrawGraph(180, 0, scoreGraph[7], TRUE);
			}

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(820, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(840, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(860, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(880, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(900, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(920, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(940, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(820, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(840, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(860, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(880, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(900, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(920, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(940, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(1030, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1050, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1070, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1090, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1110, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1130, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1150, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(1030, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1050, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1070, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1090, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1110, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1130, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1150, 50, gageGraph[3], TRUE);
			}

		}

		//うんどうが上昇
		if (scene == MOVE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[4], TRUE);//スライム描画

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			DrawGraph(50, 150, choiceGraph[0], TRUE);//日数//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ
			DrawGraph(700, 150, displayGraph[2], TRUE);//チャットウインドウを表示

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
		/*	DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);*/

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
			if (count == 7)
			{
				DrawGraph(180, 0, scoreGraph[7], TRUE);
			}

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(820, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(840, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(860, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(880, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(900, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(920, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(940, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(820, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(840, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(860, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(880, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(900, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(920, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(940, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(1030, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1050, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1070, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1090, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1110, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1130, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1150, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(1030, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1050, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1070, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1090, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1110, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1130, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1150, 50, gageGraph[3], TRUE);
			}

		}


		//おなかが上昇
		if (scene == HUNGRY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[3], TRUE);//スライム描画

			DrawGraph(384, 0, gh[20], TRUE); //ずかん
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // 四角形を描画

			DrawGraph(50, 150, choiceGraph[0], TRUE);//日数//かわいがる
			DrawGraph(50, 275, choiceGraph[1], TRUE);//しつける
			DrawGraph(50, 400, choiceGraph[2], TRUE);//ごはん
			DrawGraph(50, 525, choiceGraph[3], TRUE);//うんどう

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // 四角形を描画 チャットウインドウ
			DrawGraph(700, 150, displayGraph[3], TRUE);//チャットウインドウを表示

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//デバックテキスト
			/*DrawFormatString(0, 0, Color, " かわいさ%d", cute);
			DrawFormatString(0, 50, Color, " しつけ%d", study);
			DrawFormatString(0, 100, Color, " おなか%d", hungry);
			DrawFormatString(0, 150, Color, " きんにく%d", move);*/

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
			if (count == 7)
			{
				DrawGraph(180, 0, scoreGraph[7], TRUE);
			}

			DrawGraph(768, -2, gh[12], TRUE);//パラメーターアイコン

			//ハートゲージ
			if (pink >= 1)
			{
				DrawGraph(820, 0, gageGraph[0], TRUE);
			}
			if (pink >= 2)
			{
				DrawGraph(840, 0, gageGraph[0], TRUE);
			}
			if (pink >= 3)
			{
				DrawGraph(860, 0, gageGraph[0], TRUE);
			}
			if (pink >= 4)
			{
				DrawGraph(880, 0, gageGraph[0], TRUE);
			}
			if (pink >= 5)
			{
				DrawGraph(900, 0, gageGraph[0], TRUE);
			}
			if (pink >= 6)
			{
				DrawGraph(920, 0, gageGraph[0], TRUE);
			}
			if (pink >= 7)
			{
				DrawGraph(940, 0, gageGraph[0], TRUE);
			}

			//スペードゲージ
			if (blue >= 1)
			{
				DrawGraph(820, 50, gageGraph[1], TRUE);
			}
			if (blue >= 2)
			{
				DrawGraph(840, 50, gageGraph[1], TRUE);
			}
			if (blue >= 3)
			{
				DrawGraph(860, 50, gageGraph[1], TRUE);
			}
			if (blue >= 4)
			{
				DrawGraph(880, 50, gageGraph[1], TRUE);
			}
			if (blue >= 5)
			{
				DrawGraph(900, 50, gageGraph[1], TRUE);
			}
			if (blue >= 6)
			{
				DrawGraph(920, 50, gageGraph[1], TRUE);
			}
			if (blue >= 7)
			{
				DrawGraph(940, 50, gageGraph[1], TRUE);
			}

			//クローバーゲージ
			if (green >= 1)
			{
				DrawGraph(1030, 0, gageGraph[2], TRUE);
			}
			if (green >= 2)
			{
				DrawGraph(1050, 0, gageGraph[2], TRUE);
			}
			if (green >= 3)
			{
				DrawGraph(1070, 0, gageGraph[2], TRUE);
			}
			if (green >= 4)
			{
				DrawGraph(1090, 0, gageGraph[2], TRUE);
			}
			if (green >= 5)
			{
				DrawGraph(1110, 0, gageGraph[2], TRUE);
			}
			if (green >= 6)
			{
				DrawGraph(1130, 0, gageGraph[2], TRUE);
			}
			if (green >= 7)
			{
				DrawGraph(1150, 0, gageGraph[2], TRUE);
			}

			//ひし形ゲージ
			if (yellow >= 1)
			{
				DrawGraph(1030, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 2)
			{
				DrawGraph(1050, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 3)
			{
				DrawGraph(1070, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 4)
			{
				DrawGraph(1090, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 5)
			{
				DrawGraph(1110, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 6)
			{
				DrawGraph(1130, 50, gageGraph[3], TRUE);
			}
			if (yellow >= 7)
			{
				DrawGraph(1150, 50, gageGraph[3], TRUE);
			}

		}


		if (scene == ZUKAN)//図鑑一覧の描画
		{
			DrawGraph(0, 0, gh[3], TRUE);
			DrawGraph(900, 600, gh[21], TRUE); //戻る
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

		//if (scene == BEAUTIFULGIRLEND)//美少女エンド
		//{
		//	DrawGraph(0, 0, gh[8], TRUE);
		//}

		if (scene == NORMALSLIMEEND)//普通スライムエンド
		{
			DrawGraph(0, 0, gh[9], TRUE);
		}

		//if (scene == FINISEND)// 終焉エンド
		//{
		//	DrawGraph(0, 0, gh[10], TRUE);
		//}

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