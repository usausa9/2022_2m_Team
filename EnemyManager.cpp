#include "EnemyManager.h"
#include <random>

void EnemyManager::Update()
{
	//�G�̍X�V
	int erasecount = 0;
	for (auto itr = enemy_.begin(); itr != enemy_.end();) {
		//�G�����񂾂�폜
		if (itr->GetDel())
		{
			itr = enemy_.erase(itr);
			erasecount++;
		}
		//�X�V
		else
		{
			itr->Update();
			itr++;
		}
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : enemy_) {
		enemy.Draw();
	}
}

void EnemyManager::PopEnemyUpdate(int popWay)
{
	maxPopCoolTime = 30 - FloorManager::GetCombo() * 0.03f;
	float enemySpeed = -1.5f - FloorManager::GetCombo() * 0.05f;


	if (popCoolTime > 0)popCoolTime--;
	else {
		popCoolTime = maxPopCoolTime;

		//����������
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());

		//�G�̔�����
		std::uniform_real_distribution<float> x(1, 3);

		int popNum = x(engine);

		for (int i = 0; i < popNum; i++) {
			Enemy* newEnemy = new Enemy;

			float popx = 0;
			float popy = 0;
			//�E
			if (popWay == 0) {
				popx = 1280;

				std::uniform_real_distribution<float> y(160, 550);
				popy = y(engine);
			}
			//��
			else if (popWay == 1) {
				popx = 0;

				std::uniform_real_distribution<float> y(160, 550);
				popy = y(engine);
			}
			//��
			else if (popWay == 2) {
				std::uniform_real_distribution<float> x(80, 1100);
				popx = x(engine);

				popy = 0;
			}
			//��
			else if (popWay == 3) {
				std::uniform_real_distribution<float> x(80, 1100);
				popx = x(engine);

				popy = 720;

			}

			newEnemy->Init({ popx,popy }, popWay);

			enemy_.push_back(*newEnemy);

			delete newEnemy;
		}
	}
}

void EnemyManager::ADDEnemy(std::vector<pos> pos, int popWay)
{
	for (int i = 0; i < pos.size(); i++) {
		Enemy* newEnemy = new Enemy;

		newEnemy->Init({ (float)pos[i].x,(float)pos[i].y }, popWay);

		enemy_.push_back(*newEnemy);

		delete newEnemy;
	}
}
