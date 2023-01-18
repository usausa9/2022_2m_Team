#include "DxLib.h"
#include <vector>

#include"Floor.h"
#include "Enemy.h"
#include "FloorManager.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "2308_�Z���t���b�v_�v���g";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 720;

//typedef struct pos
//{
//	int x;
//	int y;
//};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	const int cWhite = GetColor(255, 255, 255);
	const int boxSize = 270;

	pos box = { 200,50 };

#pragma region ��

	pos selectPos_ = {0,0};

	FloorManager floorManager_;

	floorManager_.Init();

#pragma endregion
#pragma region �G
	std::vector<Enemy> enemy_;
	for (int i = 0; i < 3; i++) {
		Enemy* newEnemy = new Enemy;

		newEnemy->Init({ 300 + (float)200 * i,500 });

		enemy_.push_back(*newEnemy);

		delete newEnemy;
	}
#pragma endregion

	floorManager_.Init();

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {

		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//�G�X�V
		for (auto& enemy : enemy_) {
			enemy.Update();
		}
#pragma region �ړ�
		if (Input::Key::Triggered(DIK_UP) || Input::Key::Triggered(DIK_W)) {
			if (activeNum < 3) activeNum += 3;
			else activeNum -= 3;
		}
		else if (Input::Key::Triggered(DIK_DOWN) || Input::Key::Triggered(DIK_S)) {
			if (activeNum < 3) activeNum += 3;
			else activeNum -= 3;
		}

		if (Input::Key::Triggered(DIK_LEFT) || Input::Key::Triggered(DIK_A)) {
			if (activeNum == 0 || activeNum == 3) activeNum += 2;
			else activeNum--;
		}
		else if (Input::Key::Triggered(DIK_RIGHT) || Input::Key::Triggered(DIK_D)) {
			if (activeNum == 2 || activeNum == 5) activeNum -= 2;
			else activeNum++;
		}
#pragma endregion
		//����
		if (keys[KEY_INPUT_RETURN] == true &&
			oldkeys[KEY_INPUT_RETURN] == false) {
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if (selectPos_.x == x &&
						selectPos_.y == y)
					{
						//floors_[y][x].SetFloorType(true);
					}
				}
			}
		}
		
		floorManager_.Update();
		

		// �`�揈��
		
		//��
		floorManager_.Update();
		
		//�G�`��
		for (auto& enemy : enemy_) {
			enemy.Draw();
		}

		floorManager_.Draw();
		
		

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}


