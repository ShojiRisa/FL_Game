#include "DxLib.h"
#include<stdlib.h>//�����\���@�\��\������
#include<stdio.h>//�|�[�Y�@�\�𓱓�����
#include<math.h>//���w�I���Z
#include<time.h>//���Ԃ𗘗p

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "���Ɛ���";

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
	int gh[1];
	gh[0] = LoadGraph("R/.png");//

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
		
	};
	Scene scene = TITLE;

	//�}�E�X���̏�����
	int OldMouse = 0;
	int NewMouse = 0;
	//�v���C���[�ړ��p�ϐ�
	int MouseX = 0;
	int MouseY = 0;


	int cute = 0;
	int study = 0;
	int move = 0;
	int hungry = 0;

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

			if ((NewMouse == 1 && OldMouse == 0))
			{
				scene = GAMESCENE;
			}
		
		}

		
		if (scene == RULE)//�������
		{
			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;
			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

		}

		
		if (scene == GAMESCENE)//�Q�[���V�[��
		{

			//�}�E�X�̏������@�Ȃ���1�N���b�N�őS�ẴV�[�����Ԃ���т܂�
			OldMouse = NewMouse;

			//�}�E�X�����N���b�N����Ă��邩
			NewMouse = (GetMouseInput() & MOUSE_INPUT_LEFT);

			//���킢��
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 150) && (MouseY < 255) && (NewMouse == 1 && OldMouse == 0))
			{
				cute = cute + 3;
			}
			//��������
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 275) && (MouseY < 380) && (NewMouse == 1 && OldMouse == 0))
			{
				study = study + 3;
			}
			//���Ȃ�
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 400) && (MouseY < 505) && (NewMouse == 1 && OldMouse == 0))
			{
				hungry = hungry + 3;
			}
			//����ǂ�
			if ((MouseX > 50) && (MouseX < 550) && (MouseY > 525) && (MouseY < 630) && (NewMouse == 1 && OldMouse == 0))
			{
				move = move + 3;
			}

			if ((MouseX > 400) && (MouseX < 700) && (MouseY > 0) && (MouseY < 100) && (NewMouse == 1 && OldMouse == 0))
			{
				scene = ZUKAN;
			}

		}

		if (scene == ZUKAN)//�}��
		{
			
		}

		if (scene == HIGHHANDEDEND)//����ԃG���h
		{
			
		}

		
		if (scene == SLIMEDEATHEND)//�X���C�����S�G���h
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
			//DrawGraph(0, 0, gh[0], TRUE);//�w�i�摜

		}
		
		if (scene == RULE)//�������
		{

		}
		
		if (scene == GAMESCENE)//�Q�[���V�[��
		{

			DrawBox(0, 0, 400, 100, GetColor(0, 0, 0), TRUE);    // �l�p�`��`��
			DrawBox(400, 0, 700, 100, GetColor(0, 255, 0), TRUE);    // �l�p�`��`��
			DrawBox(700, 0, 1200, 100, GetColor(255, 0, 0), TRUE);    // �l�p�`��`��

			DrawBox(50, 150, 550, 255, GetColor(255, 100, 255), TRUE);    // �l�p�`��`��
			DrawBox(50, 275, 550, 380, GetColor(255, 255, 200), TRUE);    // �l�p�`��`��
			DrawBox(50, 400, 550, 505, GetColor(255, 200, 255), TRUE);    // �l�p�`��`��
			DrawBox(50, 525, 550, 630, GetColor(200, 255, 255), TRUE);    // �l�p�`��`��

			DrawBox(700, 150, 1100, 255, GetColor(180, 255, 255), TRUE);    // �l�p�`��`��

			unsigned int Color;

			Color = GetColor(255, 255, 255);
			DrawFormatString(0, 0, Color, " ���킢��%d", cute);
			DrawFormatString(0, 50, Color, " ����%d", study);
			DrawFormatString(0, 100, Color, " ���Ȃ�%d", hungry);
			DrawFormatString(0, 150, Color, " ����ɂ�%d", move);
		}

		if (scene == ZUKAN)//�}��
		{

		}
		
		if (scene == HIGHHANDEDEND)//����ԃG���h
		{

		}


		if (scene == SLIMEDEATHEND)//�X���C�����S�G���h
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