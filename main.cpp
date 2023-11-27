#include "DxLib.h"
#include<stdlib.h>//�����\���@�\��\������
#include<stdio.h>//�|�[�Y�@�\�𓱓�����
#include<math.h>//���w�I���Z
#include<time.h>//���Ԃ𗘗p

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "��ĂăX���C�������ďI��";

// �E�B���h�E����
const int WIN_WIDTH = 1200;

// �E�B���h�E�c��
const int WIN_HEIGHT = 700;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	// R/�̓��\�[�X�t�@�C���̈Ӗ��@�G�N�X�v���[���[�ɂ���܂�
	int gh[23];
	gh[0] = LoadGraph("R/TITLE.png");//�^�C�g��
	gh[1] = LoadGraph("R/RULE.png");//�������
	gh[2] = LoadGraph("R/GAMESCENE.png");//�Q�[���V�[��
	gh[3] = LoadGraph("R/ZUKAN.png");//�}��
	gh[4] = LoadGraph("R/HIGHHANDEDEND.png");//����ԃG���h
	gh[5] = LoadGraph("R/YOURDINNEREND.png");//���O�ӌ�уG���h
	gh[6] = LoadGraph("R/SLIMEDEATHEND.png");//�X���C�����S�G���h
	gh[7] = LoadGraph("R/SLIMEISSHOGGOTHEND.png");//�X���C���V���S�X�G���h
	gh[8] = LoadGraph("R/BEAUTIFULGIRLEND.png");//�������G���h
	gh[9] = LoadGraph("R/NORMALSLIMEEND.png");//���ʃX���C���G���h
	gh[10] = LoadGraph("R/FINISEND.png");//�I���G���h
	gh[11] = LoadGraph("R/Day.png");//����
	gh[12] = LoadGraph("R/parameters_icon.png");
	/*gh[13] = LoadGraph("R/kawaisa.png");
	gh[14] = LoadGraph("R/situkeru.png");
	gh[15] = LoadGraph("R/gohann.png");
	gh[16] = LoadGraph("R/unndou.png");
	gh[17] = LoadGraph("R/zukann.png");
	gh[18] = LoadGraph("R/ikuseikaisi.png");
	gh[19] = LoadGraph("R/sousa.png");*/
	gh[20] = LoadGraph("R/UI_book.png");//�}��
	gh[21] = LoadGraph("R/UI_return.png");//�߂�{�^��
	gh[22] = LoadGraph("R/Secret.png");//�i�����O�摜


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


	//���y�����悤�̕ϐ�
	int sound[15];
	sound[0] = LoadSoundMem("R/1-Title.mp3");//�^�C�g��
	ChangeVolumeSoundMem(100, sound[0]);//����
	sound[1] = LoadSoundMem("R/2-Sousa.mp3");//������
	ChangeVolumeSoundMem(100, sound[1]);//����
	sound[2] = LoadSoundMem("R/3-Game.mp3");//�Q�[�����
	ChangeVolumeSoundMem(100, sound[2]);//����
	sound[3] = LoadSoundMem("R/4-Zukann.mp3");//�}��
	ChangeVolumeSoundMem(100, sound[3]);//����
	sound[4] = LoadSoundMem("R/5-HIGHHANDEDEND.mp3");//�����G���h
	ChangeVolumeSoundMem(100, sound[4]);//����
	sound[5] = LoadSoundMem("R/6-YOURDINNEREND.mp3");//�ӌ�уG���h
	ChangeVolumeSoundMem(100, sound[5]);//����
	sound[6] = LoadSoundMem("R/7-SLIMEDEATHEND.mp3");//���S�G���h
	ChangeVolumeSoundMem(100, sound[6]);//����
	sound[7] = LoadSoundMem("R/8-SLIMEISSHOGGOTHEND.mp3");//�V���S�X�G���h
	ChangeVolumeSoundMem(100, sound[7]);//����
	//sound[8] = LoadSoundMem("R/9-CLEAR.mp3");//
	//ChangeVolumeSoundMem(100, sound[8]);//����
	sound[9] = LoadSoundMem("R/10-NORMALSLIMEEND.mp3");//���ʃX���C���G���h
	ChangeVolumeSoundMem(100, sound[9]);//����
	//sound[10] = LoadSoundMem("R/11-CLEAR.mp3");//
	//ChangeVolumeSoundMem(100, sound[10]);//����
	sound[11] = LoadSoundMem("R/KIRAKIRA.mp3");//�G�t�F�N�g
	ChangeVolumeSoundMem(100, sound[11]);//����
	sound[12] = LoadSoundMem("R/SE.mp3");//SE
	ChangeVolumeSoundMem(100, sound[12]);//����

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�V�[���Ǘ��p�ϐ�
	enum Scene {
		TITLE,		          //1�@�^�C�g�����
		RULE,                 //2�@�������
		GAMESCENE,            //3�@�Q�[���V�[��
		ZUKAN,                //4�@�}��
		HIGHHANDEDEND,        //5�@����ԃG���h
		YOURDINNEREND,        //6�@���O�ӌ�уG���h
		SLIMEDEATHEND,        //7�@�X���C�����S�G���h
		SLIMEISSHOGGOTHEND,   //8�@�X���C�����V���S�X�G���h
		BEAUTIFULGIRLEND,     //9�@�������G���h
		NORMALSLIMEEND,       //10 ���ʃX���C���G���h
		FINISEND,             //11 �I���G���h
		LNITIALIZATION,       //12 ������

		CUTE,
		STUDY,
		MOVE,
		HUNGRY,

	};
	Scene scene = TITLE;

	//�}�E�X���̏�����
	int OldMouse = 0;
	int NewMouse = 0;
	//�v���C���[�ړ��p�ϐ�
	int MouseX = 0;
	int MouseY = 0;

	int cute = 0; //�n�[�g
	int study = 0; //�X�y�[�h
	int hungry = 0; //�N���[�o�[
	int move = 0; //�Ђ��`

	int count = 0;
	int timer = 0;

	int pink = 0;
	int blue = 0;
	int green = 0;
	int yellow = 0;
	int red = 0;

	int endflag = 0;
	int timeflag = 0;

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(FALSE);

	//���y�𗬂�
	PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

	// �}�E�X���\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		if (scene == TITLE)//�^�C�g��
		{
			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;
			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			// �X�^�[�g��ʂ�������Ă���
			if ((MouseX > 350) && (MouseX < 850) && (MouseY > 480) && (MouseY < 580) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
				//���y���~�߂�
				StopSoundMem(sound[0]);
				//���y�𗬂�
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//���y�𗬂�
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);

			}
			//���������������Ă���
			if ((MouseX > 350) && (MouseX < 850) && (MouseY > 580) && (MouseY < 680) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = RULE;
				//���y���~�߂�
				StopSoundMem(sound[0]);
				//���y�𗬂�
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//���y�𗬂�
				PlaySoundMem(sound[1], DX_PLAYTYPE_BACK);
			}
		}

		if (scene == RULE)//�������
		{
			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;
			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//�N���W�b�g��������Ă���
			if ((MouseX > 900) && (MouseX < 1200) && (MouseY > 600) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = TITLE;
				//���y���~�߂�
				StopSoundMem(sound[1]);
				//���y�𗬂�
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//���y�𗬂�
				PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

			}

		}

		if (scene == ZUKAN)//�}��
		{

			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;
			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);
			//�N���W�b�g��������Ă���
			if ((MouseX > 900) && (MouseX < 1200) && (MouseY > 600) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
				//���y�𗬂�
				PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				//���y���~�߂�
				StopSoundMem(sound[3]);
				//���y�𗬂�
				PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);
			}
		}

		//�Q�[���V�[��
		if (scene == GAMESCENE)
		{
			timer = 0;

			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;

			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);


			if (count <= 6)
			{
				//���킢��
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
				{
					cute = cute + 3;
					scene = CUTE;
					count = count + 1;
					pink = pink + 1;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//��������
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
				{
					study = study + 3;
					scene = STUDY;
					count = count + 1;
					blue = blue + 1;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//����ǂ�
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
				{
					move = move + 3;
					scene = MOVE;
					count = count + 1;
					green = green + 1;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}
				//���Ȃ�
				if ((MouseX > 50) && (MouseX < 550) && (MouseY > 525) && (MouseY < 630) && (NewMouse == 1 && OldMouse == 0))
				{
					hungry = hungry + 3;
					scene = HUNGRY;
					count = count + 1;
					yellow = yellow + 1;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
				}


				if ((MouseX > 400) && (MouseX < 700) && (MouseY > 0) && (MouseY < 100) && (NewMouse == 1 && OldMouse == 0))
				{
					scene = ZUKAN;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
					//���y���~�߂�
					StopSoundMem(sound[2]);
					//���y�𗬂�
					PlaySoundMem(sound[3], DX_PLAYTYPE_BACK);
				}
			}

			if (count == 7 && timeflag == 1)
			{

				if ((MouseX > 0) && (MouseX < 1200) && (MouseY > 100) && (MouseY < 700) && (NewMouse == 1 && OldMouse == 0))
				{
					endflag = 1;
					//���y�𗬂�
					PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
					//���y���~�߂�
					StopSoundMem(sound[2]);
					//���y�𗬂�
					PlaySoundMem(sound[4], DX_PLAYTYPE_BACK);
					//���y�𗬂�
					PlaySoundMem(sound[6], DX_PLAYTYPE_BACK);
					//���y�𗬂�
					PlaySoundMem(sound[5], DX_PLAYTYPE_BACK);
					//���y�𗬂�
					PlaySoundMem(sound[7], DX_PLAYTYPE_BACK);
					//���y�𗬂�
					PlaySoundMem(sound[9], DX_PLAYTYPE_BACK);
				}
			}

		}

		//�A�Ŗh�~
		if (scene == CUTE)//���킢�����㏸
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == STUDY)//�����������㏸
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == HUNGRY)//���Ȃ����㏸
		{
			timer = timer + 1;

			if (timer >= 120)
			{
				scene = GAMESCENE;
			}
		}
		if (scene == MOVE)//����ǂ����㏸
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



		//�G���h
		if (endflag == 1)
		{
			if (cute >= 21)
			{
				scene = HIGHHANDEDEND;
				//���y���~�߂�
				StopSoundMem(sound[6]);
				//���y���~�߂�
				StopSoundMem(sound[5]);
				//���y���~�߂�
				StopSoundMem(sound[7]);
				//���y���~�߂�
				StopSoundMem(sound[9]);
			}
			if (study >= 21)
			{
				scene = SLIMEDEATHEND;
				//���y���~�߂�
				StopSoundMem(sound[4]);
				//���y���~�߂�
				StopSoundMem(sound[5]);
				//���y���~�߂�
				StopSoundMem(sound[7]);
				//���y���~�߂�
				StopSoundMem(sound[9]);
			}
			if (hungry >= 21)
			{
				scene = YOURDINNEREND;
				//���y���~�߂�
				StopSoundMem(sound[6]);
				//���y���~�߂�
				StopSoundMem(sound[4]);
				//���y���~�߂�
				StopSoundMem(sound[7]);
				//���y���~�߂�
				StopSoundMem(sound[9]);
			}
			if (move >= 21)
			{
				scene = SLIMEISSHOGGOTHEND;
				//���y���~�߂�
				StopSoundMem(sound[6]);
				//���y���~�߂�
				StopSoundMem(sound[5]);
				//���y���~�߂�
				StopSoundMem(sound[4]);
				//���y���~�߂�
				StopSoundMem(sound[9]);
			}
			else if (cute <= 20 && study <= 20 && hungry <= 20 && move <= 20)
			{
				scene = NORMALSLIMEEND;
				//���y���~�߂�
				StopSoundMem(sound[6]);
				//���y���~�߂�
				StopSoundMem(sound[5]);
				//���y���~�߂�
				StopSoundMem(sound[7]);
				//���y���~�߂�
				StopSoundMem(sound[4]);
			}
		}



		//*******************************************************************************************************************
		//��������G���h����
		if (scene == HIGHHANDEDEND || SLIMEDEATHEND || YOURDINNEREND || SLIMEISSHOGGOTHEND || NORMALSLIMEEND)//�G���h.
		{
			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;
			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0)
			{
				scene = LNITIALIZATION;
			}
		}

		//if (scene == BEAUTIFULGIRLEND)//�������G���h
		//{

		//}

		//if (scene == FINISEND)// �I���G���h
		//{

		//}

		if (scene == LNITIALIZATION)//������
		{
			scene = TITLE;

			//�}�E�X���̏�����
			OldMouse = 0;
			NewMouse = 0;
			//�v���C���[�ړ��p�ϐ�
			MouseX = 0;
			MouseY = 0;

			cute = 0; //�n�[�g
			study = 0; //�X�y�[�h
			hungry = 0; //�N���[�o�[
			move = 0; //�Ђ��`

			count = 0;
			timer = 0;

			pink = 0;
			blue = 0;
			green = 0;
			yellow = 0;
			red = 0;

			endflag = 0;
			timeflag = 0;
			
			//���y���~�߂�
			StopSoundMem(sound[4]);
			//���y���~�߂�
			StopSoundMem(sound[6]);
			//���y���~�߂�
			StopSoundMem(sound[5]);
			//���y���~�߂�
			StopSoundMem(sound[7]);
			//���y���~�߂�
			StopSoundMem(sound[9]);
			//���y�𗬂�
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);
			//���y�𗬂�
			PlaySoundMem(sound[12], DX_PLAYTYPE_BACK);
		}


		//*******************************************************************************************************************

		// �`�揈��

		if (scene == TITLE)//�^�C�g�����
		{
			//DrawGraph(400, 400, gh[18], TRUE);//�Q�[���J�n
			//DrawGraph(400, 550, gh[19], TRUE);//�������
			DrawGraph(0, 0, gh[2], TRUE);
			DrawGraph(220, 50, gh[0], TRUE);//�w�i�摜
			DrawGraph(350, 480, titleGraph[0], TRUE);
			DrawGraph(350, 580, titleGraph[1], TRUE);
		}

		if (scene == RULE)//�������
		{

			DrawGraph(0, 0, gh[2], TRUE);//�w�i

			DrawGraph(50, 150, choiceGraph[0], TRUE);//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			DrawGraph(750, 390, slimeGraph[0], TRUE);//�X���C��

			DrawGraph(384, 0, gh[20], TRUE); //������
			DrawGraph(0, 0, gh[11], TRUE);//����

			DrawGraph(180, 0, scoreGraph[0], TRUE);

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			DrawGraph(900, 600, gh[21], TRUE); //�߂�
			DrawGraph(0, 0, gh[1], TRUE);//�������
		}



		//�Q�[�����
		if (scene == GAMESCENE)//�Q�[���V�[��
		{

			DrawGraph(0, 0, gh[2], TRUE);//�w�i

			DrawGraph(50, 150, choiceGraph[0], TRUE);//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			/*DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);*/

			DrawGraph(750, 390, slimeGraph[0], TRUE);//�X���C��

			if (count == 7 && timeflag == 1)
			{
				DrawGraph(0, 0, gh[2], TRUE);//�w�i
				DrawGraph(0, 0, gh[22], TRUE);//�w�i
			}

			DrawGraph(384, 0, gh[20], TRUE); //������
			DrawGraph(0, 0, gh[11], TRUE);//����

			//���t�̃J�E���g
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

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//���킢�����㏸
		if (scene == CUTE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[1], TRUE);//�X���C���`��

			DrawGraph(384, 0, gh[20], TRUE); //������
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			DrawGraph(50, 150, choiceGraph[0], TRUE);//����//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E
			DrawGraph(700, 150, displayGraph[0], TRUE);//�`���b�g�E�C���h�E��\��

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			/*DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);*/

			//DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
			DrawGraph(0, 0, gh[11], TRUE);//����

			//���t�̃J�E���g
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

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//�����������㏸
		if (scene == STUDY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[5], TRUE);//�X���C���`��

			DrawGraph(384, 0, gh[20], TRUE); //������
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			DrawGraph(50, 150, choiceGraph[0], TRUE);//����//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E
			DrawGraph(700, 150, displayGraph[1], TRUE);//�`���b�g�E�C���h�E��\��

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			/*DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);*/

			//DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
			DrawGraph(0, 0, gh[11], TRUE);//����

			//���t�̃J�E���g
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

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//����ǂ����㏸
		if (scene == MOVE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[4], TRUE);//�X���C���`��

			DrawGraph(384, 0, gh[20], TRUE); //������
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			DrawGraph(50, 150, choiceGraph[0], TRUE);//����//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E
			DrawGraph(700, 150, displayGraph[2], TRUE);//�`���b�g�E�C���h�E��\��

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
		/*	DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);*/

			//DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
			DrawGraph(0, 0, gh[11], TRUE);//����

			//���t�̃J�E���g
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

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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


		//���Ȃ����㏸
		if (scene == HUNGRY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(750, 390, slimeGraph[3], TRUE);//�X���C���`��

			DrawGraph(384, 0, gh[20], TRUE); //������
			//DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			DrawGraph(50, 150, choiceGraph[0], TRUE);//����//���킢����
			DrawGraph(50, 275, choiceGraph[1], TRUE);//������
			DrawGraph(50, 400, choiceGraph[2], TRUE);//���͂�
			DrawGraph(50, 525, choiceGraph[3], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E
			DrawGraph(700, 150, displayGraph[3], TRUE);//�`���b�g�E�C���h�E��\��

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			/*DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);*/

			//DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
			DrawGraph(0, 0, gh[11], TRUE);//����

			//���t�̃J�E���g
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

			DrawGraph(768, -2, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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


		if (scene == ZUKAN)//�}�ӈꗗ�̕`��
		{
			DrawGraph(0, 0, gh[3], TRUE);
			DrawGraph(900, 600, gh[21], TRUE); //�߂�
		}

		//��������e�G���h************************************************************************************

		if (scene == HIGHHANDEDEND)//����ԃG���h
		{
			DrawGraph(0, 0, gh[4], TRUE);
		}

		if (scene == YOURDINNEREND)//���O�ӌ�уG���h
		{
			DrawGraph(0, 0, gh[5], TRUE);
		}

		if (scene == SLIMEDEATHEND)//�X���C�����S�G���h
		{
			DrawGraph(0, 0, gh[6], TRUE);
		}

		if (scene == SLIMEISSHOGGOTHEND)//�X���C�����V���S�X�G���h
		{
			DrawGraph(0, 0, gh[7], TRUE);
		}

		//if (scene == BEAUTIFULGIRLEND)//�������G���h
		//{
		//	DrawGraph(0, 0, gh[8], TRUE);
		//}

		if (scene == NORMALSLIMEEND)//���ʃX���C���G���h
		{
			DrawGraph(0, 0, gh[9], TRUE);
		}

		//if (scene == FINISEND)// �I���G���h
		//{
		//	DrawGraph(0, 0, gh[10], TRUE);
		//}

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&MouseX, &MouseY);





		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}