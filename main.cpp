#include "DxLib.h"
#include <vector>
#include <list>

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

	FloorManager floorManager_;

	floorManager_.Init();

#pragma endregion
#pragma region �G
	std::vector<Enemy> enemy_;
	for (int i = 0; i < 3; i++) {
		Enemy* newEnemy = new Enemy;

		newEnemy->Init({ 300 + (float)250 * i,500 });

		if (i == 1) {
			newEnemy->Init({ 300 + (float)220 * i,370 });
		}

		enemy_.push_back(*newEnemy);

		delete newEnemy;
	}
#pragma endregion

#pragma region �G���o��������J�[�\��

	pos cursolPos = {400,400};

	std::vector<pos> popPos_;

#pragma endregion

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
		/*for (auto& enemy : enemy_) {
			enemy.Update();
		}*/

		int erasecount = 0;
		for (auto itr = enemy_.begin(); itr != enemy_.end();) {
			if (itr->GetDel())
			{
				itr = enemy_.erase(itr);
				erasecount++;
			}
			else
			{
				itr->Update();
				itr++;
			}
		}
#pragma region �ړ�

		if (keys[KEY_INPUT_LEFT] == true) {
			cursolPos.x -= 5;
		}
		if (keys[KEY_INPUT_RIGHT] == true) {
			cursolPos.x += 5;
		}

		if (keys[KEY_INPUT_UP] == true) {
			cursolPos.y -= 5;
		}
		if (keys[KEY_INPUT_DOWN] == true) {
			cursolPos.y += 5;
		}
		
		//�G��o�^����
		if (keys[KEY_INPUT_P] == true && oldkeys[KEY_INPUT_P] == false) {
			popPos_.push_back(cursolPos);
		}
		//�G���o��������
		if (keys[KEY_INPUT_RETURN] == true &&
			oldkeys[KEY_INPUT_RETURN] == false) {
			for (int i = 0; i < popPos_.size(); i++) {
				Enemy* newEnemy = new Enemy;

				newEnemy->Init({ (float)popPos_[i].x,(float)popPos_[i].y });

				enemy_.push_back(*newEnemy);

				delete newEnemy;
			}

			popPos_.clear();
		}
		
#pragma endregion
		
		
		floorManager_.Update(keys,oldkeys,enemy_);
		

		// �`�揈��

		
		//�G�`��
		for (auto& enemy : enemy_) {
			enemy.Draw();
		}

		floorManager_.Draw();
		
		DrawCircle(cursolPos.x, cursolPos.y, 5, 0x00ff00, true);

		for (pos pos : popPos_) {
			DrawCircle(pos.x, pos.y, 5, 0x00f0f0, true);
		}
		
		DrawFormatString(0, 0, 0xffffff, "WASD�L�[ : �p�l����I��");
		DrawFormatString(0, 20, 0xffffff, "SPACE�L�[ : �p�l���ω�");

		DrawFormatString(0, 60, 0xffffff, "�f�o�b�O����");
		DrawFormatString(0, 80, 0xffffff, "ARROW�L�[ : �J�[�\���ʒu�ύX");
		DrawFormatString(0, 100, 0xffffff, "P�L�[ : �G��o�^");
		DrawFormatString(0, 120, 0xffffff, "ENTER�L�[ : �G���o��");

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


