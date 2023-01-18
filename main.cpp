#include "DxLib.h"
#include <vector>

#include"Floor.h"
#include "Enemy.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "2308_セルフリップ_プロト";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

typedef struct pos
{
	int x;
	int y;
};

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
	Floor floors_[2][3];

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			Floor *newFloor = new Floor;
			//左上
			FLOAT2 startPos = {
				box.x + (x * boxSize),
				box.y + (y * boxSize)
			};
			//右下
			FLOAT2 endPos = {
				box.x + ((x + 1) * boxSize) + 70,
				box.y + ((y + 1) * boxSize) + 70
			};

			newFloor->Init(startPos, endPos);
			//床を追加
			floors_[y][x] = *newFloor;

			delete newFloor;
		}

	}

	pos selectPos_ = {0,0};
#pragma endregion
#pragma region 敵
	std::vector<Enemy> enemy_;
	for (int i = 0; i < 3; i++) {
		Enemy* newEnemy = new Enemy;

		newEnemy->Init({ 300 + (float)200 * i,500 });

		enemy_.push_back(*newEnemy);

		delete newEnemy;
	}
#pragma endregion

	/*std::vector<std::vector<FLOAT2>> */

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
		for (auto& enemy : enemy_) {
			enemy.Update();
		}
#pragma region 移動
		if (keys[KEY_INPUT_D] == true &&
			oldkeys[KEY_INPUT_D] == false)
		{
			if (selectPos_.x == 2)
			{
				selectPos_.x = 0;
			}
			else
			{
				selectPos_.x++;
			}
		}
		else if (keys[KEY_INPUT_A] == true &&
			oldkeys[KEY_INPUT_A] == false)
		{
			if (selectPos_.x == 0)
			{
				selectPos_.x = 2;
			}
			else
			{
				selectPos_.x--;
			}
		}

		if (keys[KEY_INPUT_W] == true &&
			oldkeys[KEY_INPUT_W] == false)
		{
			if (selectPos_.y == 0)
			{
				selectPos_.y = 1;
			}
			else
			{
				selectPos_.y--;
			}
		}
		else if (keys[KEY_INPUT_S] == true &&
			oldkeys[KEY_INPUT_S] == false)
		{
			if (selectPos_.y == 1)
			{
				selectPos_.y = 0;
			}
			else
			{
				selectPos_.y++;
			}
		}
#pragma endregion
		//決定
		if (keys[KEY_INPUT_RETURN] == true &&
			oldkeys[KEY_INPUT_RETURN] == false) {
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if (selectPos_.x == x &&
						selectPos_.y == y)
					{
						floors_[y][x].SetFloorType(true);
					}
				}
			}
		}
		

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (selectPos_.x == x &&
					selectPos_.y == y)
				{
					floors_[y][x].SetActive(true);
				}
				else
				{
					floors_[y][x].SetActive(false);
				}
				//床更新
				floors_[y][x].Update();
			}

		}

		// 描画処理
		
		//床
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				floors_[y][x].Draw();
			}
			
		}
		//敵描画
		for (auto& enemy : enemy_) {
			enemy.Draw();
		}
		
		

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
