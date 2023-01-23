#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include <vector>
#include "FloorManager.h"
class EnemyManager
{
public:

	void Update();

	void Draw();

	void PopEnemyUpdate(int popWay);

	void ADDEnemy(std::vector<pos> pos,int popWay);

	std::vector<Enemy>& GetEnemy() { return enemy_; }

private:
	std::vector<Enemy> enemy_;

	int maxPopCoolTime = 80;
	int popCoolTime = maxPopCoolTime;

	

};

