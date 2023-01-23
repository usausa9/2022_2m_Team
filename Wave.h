#pragma once
#include "FloorManager.h"
#include "EnemyManager.h"
class Wave
{
public:

	void Init();

	void Update(char* key, char* oldkey);

	void Draw();

	void DebugDraw();

private:
	int maxWave;
	int nowWave_ = 1;

	int maxWaveTimer = 1200;
	int waveTimer_ = maxWaveTimer;

	EnemyManager enemyManager_;

	FloorManager floorManager_;

	int popWay_;
};

