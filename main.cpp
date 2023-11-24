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
	int gh[20];
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


	//���y�����悤�̕ϐ�
	int sound[1];
	sound[0] = LoadSoundMem("R/.mp3");//
	ChangeVolumeSoundMem(100, sound[0]);//����

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
			if ((MouseX > 400) && (MouseX < 750) && (MouseY > 400) && (MouseY < 500) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
			}
			//���������������Ă���
			if ((MouseX > 400) && (MouseX < 750) && (MouseY > 550) && (MouseY < 650) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = RULE;
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
			}
		}

		if (scene == GAMESCENE)//�Q�[���V�[��
		{
			timer = 0;
			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;

			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//���킢��
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
			{
				cute = cute + 3;
				scene = CUTE;
				count = count + 1;
				pink = pink + 1;
			}
			//��������
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
			{
				study = study + 3;
				scene = STUDY;
				count = count + 1;
				blue = blue + 1;
			}
			//���Ȃ�
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
			{
				hungry = hungry + 3;
				scene = HUNGRY;
				count = count + 1;
				green = green + 1;
			}
			//����ǂ�
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



		//�G���h
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
		//��������G���h����
		if (scene == HIGHHANDEDEND)//����ԃG���h
		{

		}

		if (scene == SLIMEDEATHEND)//�X���C�����S�G���h
		{

		}

		if (scene == YOURDINNEREND)//���O�ӌ�уG���h
		{

		}

		if (scene == SLIMEISSHOGGOTHEND)//�X���C�����V���S�X�G���h
		{

		}

		if (scene == BEAUTIFULGIRLEND)//�������G���h
		{

		}

		if (scene == NORMALSLIMEEND)//���ʃX���C���G���h
		{

		}

		if (scene == FINISEND)// �I���G���h
		{

		}

		if (scene == LNITIALIZATION)//������
		{

		}


		//*******************************************************************************************************************

		// �`�揈��

		if (scene == TITLE)//�^�C�g�����
		{
			DrawGraph(0, 0, gh[0], TRUE);//�w�i�摜

			//DrawBox(400, 400, 750, 500, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 400, gh[18], TRUE);//�Q�[���J�n
			//DrawBox(400, 550, 750, 650, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 550, gh[19], TRUE);//�������


			//DrawGraph(100, 100, gageGraph[0], TRUE);//���摜

		}

		if (scene == RULE)//�������
		{
			DrawGraph(0, 0, gh[1], TRUE);
			DrawBox(900, 600, 1200, 700, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
		}

		//�Q�[�����
		if (scene == GAMESCENE)//�Q�[���V�[��
		{

			DrawGraph(0, 0, gh[2], TRUE);

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 0, gh[17], TRUE); //������
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 150, gh[13], TRUE);//����//���킢����
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawGraph(50, 275, gh[14], TRUE);//������
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 400, gh[15], TRUE);//���͂�
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 525, gh[16], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
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

			DrawGraph(700, 0, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

			////�{��Q�[�W
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

		//���킢�����㏸
		if (scene == CUTE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[1], TRUE);//�X���C���`��

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 0, gh[17], TRUE); //������
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 150, gh[13], TRUE);//����//���킢����
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawGraph(50, 275, gh[14], TRUE);//������
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 400, gh[15], TRUE);//���͂�
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 525, gh[16], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);

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

			DrawGraph(700, 0, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//�����������㏸
		if (scene == STUDY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[5], TRUE);//�X���C���`��

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 0, gh[17], TRUE); //������
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 150, gh[13], TRUE);//����//���킢����
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawGraph(50, 275, gh[14], TRUE);//������
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 400, gh[15], TRUE);//���͂�
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 525, gh[16], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
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

			DrawGraph(700, 0, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//���Ȃ����㏸
		if (scene == HUNGRY)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[3], TRUE);//�X���C���`��

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 0, gh[17], TRUE); //������
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 150, gh[13], TRUE);//����//���킢����
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawGraph(50, 275, gh[14], TRUE);//������
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 400, gh[15], TRUE);//���͂�
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 525, gh[16], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
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

			DrawGraph(700, 0, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		//����ǂ����㏸
		if (scene == MOVE)
		{
			DrawGraph(0, 0, gh[2], TRUE);

			DrawGraph(600, 300, slimeGraph[4], TRUE);//�X���C���`��

			//DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			//DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawGraph(400, 0, gh[17], TRUE); //������
			DrawBox(700, 0, 1200, 100, GetColor(255, 255, 255), TRUE);    // �l�p�`��`��

			//DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 150, gh[13], TRUE);//����//���킢����
			//DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawGraph(50, 275, gh[14], TRUE);//������
			//DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 400, gh[15], TRUE);//���͂�
			//DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��
			DrawGraph(50, 525, gh[16], TRUE);//����ǂ�

			//DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`�� �`���b�g�E�C���h�E

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			//�f�o�b�N�e�L�X�g
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);

			DrawGraph(600, 300, slimeGraph[0], TRUE);//�X���C��
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

			DrawGraph(700, 0, gh[12], TRUE);//�p�����[�^�[�A�C�R��

			//�n�[�g�Q�[�W
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

			//�X�y�[�h�Q�[�W
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

			//�N���[�o�[�Q�[�W
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

			//�Ђ��`�Q�[�W
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

		if (scene == ZUKAN)//�}�ӈꗗ�̕`��
		{
			DrawGraph(0, 0, gh[3], TRUE);
			DrawBox(900, 600, 1200, 700, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
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

		if (scene == BEAUTIFULGIRLEND)//�������G���h
		{
			DrawGraph(0, 0, gh[8], TRUE);
		}

		if (scene == NORMALSLIMEEND)//���ʃX���C���G���h
		{
			DrawGraph(0, 0, gh[9], TRUE);
		}

		if (scene == FINISEND)// �I���G���h
		{
			DrawGraph(0, 0, gh[10], TRUE);
		}

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