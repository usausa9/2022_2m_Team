#include "FloorManager.h"


void FloorManager::Init()
{
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			Floor* newFloor = new Floor;
			//����
			FLOAT2 startPos = {
				box.x + (x * boxSize),
				box.y + (y * boxSize)
			};
			//�E��
			FLOAT2 endPos = {
				box.x + ((x + 1) * boxSize) + 70,
				box.y + ((y + 1) * boxSize) + 70
			};

			newFloor->Init(startPos, endPos);
			//����ǉ�
			floors_.push_back(*newFloor);

			delete newFloor;
		}

	}
}

void FloorManager::Update(char key[], char oldkey[], std::vector<Enemy>& enemy) {
	for (auto& floor : floors_) {
		floor.Update();
	}

	for (int i = 0; i < floors_.size(); i++) {
		if (activeNum == i) {
			floors_[i].SetActive(true);
		}
		else {
			floors_[i].SetActive(false);
		}
	}

	if (key[KEY_INPUT_W] == true && oldkey[KEY_INPUT_W] == false) {
		if (activeNum < 3) activeNum += 3;
		else activeNum -= 3;
	}
	else if (key[KEY_INPUT_S] == true && oldkey[KEY_INPUT_S] == false) {
		if (activeNum < 3) activeNum += 3;
		else activeNum -= 3;
	}

	if (key[KEY_INPUT_A] == true && oldkey[KEY_INPUT_A] == false) {
		if (activeNum == 0 || activeNum == 3) activeNum += 2;
		else activeNum--;
	}
	else if (key[KEY_INPUT_D] == true && oldkey[KEY_INPUT_D] == false) {
		if (activeNum == 2 || activeNum == 5) activeNum -= 2;
		else activeNum++;
	}

	if (key[KEY_INPUT_SPACE] == true && oldkey[KEY_INPUT_SPACE] == false) {

		for (Floor& floor : floors_) {
			//���ɂȂ����Ă���Ƃ��ɑI���ł��Ȃ�
			if (floor.GetFloorType() == false) {
				if (floor.GetActive()) {
					floor.Move(enemy);
					break;
				}
			}
		}

		

		for (auto& f : floors_)
		{

			if (f.GetFlipState())
			{
				FLOAT2 startPos = f.GetStartPos();
				FLOAT2 endPos = f.GetEndPos();
				for (int j = 0; j < enemy.size(); j++) {
					//��]����I�u�W�F�N�g�̍��W
					FLOAT2 rotObjPos = {
						enemy[j].GetPos().u,
						enemy[j].GetPos().v
					};

					if (startPos.u <= rotObjPos.u &&
						startPos.v <= rotObjPos.v &&
						endPos.u >= rotObjPos.u &&
						endPos.v >= rotObjPos.v)
					{
						//���SetDown��ς����珈����ʂ�Ȃ��悤�ɂ���
						if (enemy[j].GetIsFlip() == false) {
							//����œ���r���ɒn�ʂ�ύX���ꂽ��
							if (enemy[j].GetIsDown() == true) {
								enemy[j].SetIsDown(false);
								enemy[j].SetDel(true);

								
							}
							//�G�𒾂܂���
							else {
								//�I���������̏�ɂ��鐯��|��
								enemy[j].SetIsDown(true);
							}
							enemy[j].SetIsFlip(true);
						}
					}

				}
			}
			f.FinishMove();

		}

		for (int j = 0; j < enemy.size(); j++) {
			enemy[j].SetIsFlip(false);
		}
	}
}

void FloorManager::Draw() {
	for (auto& floor : floors_) {
		floor.Draw();
	}
}

std::vector<Floor> FloorManager::floors_;

int FloorManager::boxSize = 270;

pos FloorManager::box = { 200,50 };

int FloorManager::activeNum;