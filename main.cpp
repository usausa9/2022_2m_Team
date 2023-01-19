#include "DxLib.h"
#include <vector>
#include <list>

#include"Floor.h"
#include "Enemy.h"
#include "FloorManager.h"

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

#pragma region 敵を出現させるカーソル

	pos cursolPos = {400,400};

	std::vector<pos> popPos_;

#pragma endregion

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
		

		// 描画処理

		
		//敵描画
		for (auto& enemy : enemy_) {
			enemy.Draw();
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


