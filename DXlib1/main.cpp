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
		TITLE,		//0�@�^�C�g�����
		RULE,	//1�@�������
		CREDIT,	//2�@�N���W�b�g
		SELECT,
		WAITING,	//�@�ҋ@���
		STAGE_1,
		STAGE_2,
		TUTORIAL,	//
		CLEAR,		//
		GAMEOVER,	// 
	};
	Scene scene = TITLE;

	//�}�E�X���̏�����
	int OldMouse = 0;
	int NewMouse = 0;

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
		if (scene == TITLE)//�X�^�[�g���
		{
		
		}

		//�X�e�[�W�I�����
		if (scene == SELECT)
		{
	
		}

		//�ҋ@���
		if (scene == WAITING)
		{
		
		}

		if (scene == RULE)//�������
		{
			
		}

		if (scene == CREDIT)//�N���W�b�g
		{
			
		}

		//�Q�[�����1
		if (scene == STAGE_1)
		{
			
		}
		//�Q�[�����2
		if (scene == STAGE_2)
		{
			
		}

		//�G���h����@�N���A
		if (scene == CLEAR)
		{
			
		}

		//�G���h����@�Q�[���I�[�o�[
		if (scene == GAMEOVER)
		{
			
		}

//*******************************************************************************************************************

		// �`�揈��

		if (scene == TITLE)//�^�C�g�����
		{
		
		}
		//�X�e�[�W�I�����
		if (scene == SELECT)
		{
			
		}

		if (scene == WAITING)//�X�^�[�g���
		{
			
		}
		if (scene == RULE)//�������
		{
			
		}
		if (scene == CREDIT)//�N���W�b�g
		{
			
		}

		//�Q�[����� �X�e�[�W1
		if (scene == STAGE_1)
		{
			
		}
		//�Q�[����ʁ@�X�e�[�W2
		if (scene == STAGE_2)
		{
			
		}

		//�G���h����@�N���A
		if (scene == CLEAR)
		{
			
		}

		//�G���h����@�Q�[���I�[�o�[
		if (scene == GAMEOVER)
		{
		
		}

		// �}�E�X�̈ʒu���擾
		//GetMousePoint(&, &);


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