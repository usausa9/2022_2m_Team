#include "Wave.h"

void Wave::Init()
{
	nowWave_ = 0;
	floorManager_.Init();
}

void Wave::Update(char* key, char* oldkey)
{
	if (waveTimer_ > 0)waveTimer_--;
	else {
		waveTimer_ = maxWaveTimer;
		//次のウェーブへ
		nowWave_++;
	}

	if (nowWave_ > 4) {
		nowWave_ = 0;
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


	enemyManager_.Update();
	enemyManager_.PopEnemyUpdate(popWay_);

	floorManager_.Update(key, oldkey, enemyManager_.GetEnemy());
}

void Wave::Draw()
{
	enemyManager_.Draw();
	floorManager_.Draw();
}

void Wave::DebugDraw()
{
	//enemyManager_.Draw();
}
