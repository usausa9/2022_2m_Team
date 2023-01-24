       #include "DxLib.h"
#include <vector>
#include <list>

#include"Floor.h"
#include "Enemy.h"
#include "FloorManager.h"
#include <random>
#include "Boss.h"
#include "EnemyManager.h"


// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "2308_セルフリップ_プロト";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

//typedef struct pos
//{
//	int x;
//	int y;
//};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	

	// ゲームループで使う変数の宣言

	const int cWhite = GetColor(255, 255, 255);
	const int boxSize = 270;

	pos box = { 200,50 };

#pragma region 床

	FloorManager floorManager_;

	floorManager_.Init();

#pragma endregion
#pragma region 敵
	
	int popWay_ = 0;

	EnemyManager enemyManager_;

#pragma endregion

#pragma region 敵を出現させるカーソル

	pos cursolPos = {400,400};

	std::vector<pos> popPos_;

#pragma endregion

	

	Boss boss_;
	boss_.Init();

	//ウェーブ
	int nowWave_ = 1;
	int maxWaveTimer = 1200;
	int waveTimer_ = maxWaveTimer;

	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {

		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		//敵更新
		if (nowWave_ < 5) {
			if (waveTimer_ > 0)waveTimer_--;
			else {
				waveTimer_ = maxWaveTimer;
				//次のウェーブへ
				nowWave_++;
			}
		}

		

		if (nowWave_ == 1) {
			popWay_ = 0;
		}
		else if (nowWave_ == 2) {
			popWay_ = 1;
		}
		else if (nowWave_ == 3) {
			popWay_ = 2;
		}
		else if (nowWave_ == 4) {
			popWay_ = 3;
		}

		
		if (nowWave_ == 5) {
			boss_.Update();
		}


		enemyManager_.Update();

		enemyManager_.PopEnemyUpdate(popWay_);

		
#pragma region 移動

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
		
		//敵を登録する
		if (keys[KEY_INPUT_P] == true && oldkeys[KEY_INPUT_P] == false) {
			popPos_.push_back(cursolPos);
		}
		//敵を出現させる
		if (keys[KEY_INPUT_RETURN] == true &&
			oldkeys[KEY_INPUT_RETURN] == false) {

			enemyManager_.ADDEnemy(popPos_, popWay_);

			popPos_.clear();
		}

		if (keys[KEY_INPUT_1] == true &&
			oldkeys[KEY_INPUT_1] == false) {
			//スポーンする方向
			popWay_++;
			if (popWay_ > 3)popWay_ = 0;
		}
		
#pragma endregion
		
		
		floorManager_.Update(keys,oldkeys,enemyManager_.GetEnemy());

		

		// 描画処理

		//敵描画
		enemyManager_.Draw();

		if (nowWave_ == 5) {
			boss_.Draw();
		}

		floorManager_.Draw();
		
		DrawCircle(cursolPos.x, cursolPos.y, 5, 0x00ff00, true);

		for (pos pos : popPos_) {
			DrawCircle(pos.x, pos.y, 5, 0x00f0f0, true);
		}
		
		DrawFormatString(0, 0, 0xffffff, "WASDキー : パネルを選択");
		DrawFormatString(0, 20, 0xffffff, "SPACEキー : パネル変化");

		DrawFormatString(0, 60, 0xffffff, "デバッグ操作");
		DrawFormatString(0, 80, 0xffffff, "ARROWキー : カーソル位置変更");
		DrawFormatString(0, 100, 0xffffff, "Pキー : 敵を登録");
		DrawFormatString(0, 120, 0xffffff, "ENTERキー : 敵を出現");

		DrawFormatString(0, 140, 0xffffff, "combo : %d", FloorManager::GetCombo());
		DrawFormatString(0, 160, 0xffffff, "comboTimer : %d", FloorManager::GetComboTimer());

		DrawFormatString(0, 180, 0xffffff, "nowWave : %d", nowWave_);
		DrawFormatString(0, 200, 0xffffff, "timer : %d", waveTimer_);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}


