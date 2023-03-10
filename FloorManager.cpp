#include "FloorManager.h"


void FloorManager::Init()
{
	//for (int y = 0; y < 2; y++)
	//{
	//	for (int x = 0; x < 3; x++)
	//	{
	//		Floor* newFloor = new Floor;
	//		//左上
	//		FLOAT2 startPos = {
	//			box.x + (x * boxSize),
	//			box.y + (y * boxSize)
	//		};
	//		//右下
	//		FLOAT2 endPos = {
	//			box.x + ((x + 1) * boxSize) + 70,
	//			box.y + ((y + 1) * boxSize) + 70
	//		};

	//		newFloor->Init(startPos, endPos);
	//		//床を追加
	//		floors_.push_back(*newFloor);

	//		delete newFloor;
	//	}

	//}

	for (int i = 0; i < 7; i++) {
		Floor* newFloor = new Floor;

		FLOAT2 startPos{};


		if (i == 0) {
			startPos = {
				200,
				720 / 2
			};
		}
		else if (i == 1) {
			startPos = {
				400,
				720 / 2.5f
			};
		}
		else if (i == 2) {
			startPos = {
				400,
				720 / 1.7f
			};
		}
		else if (i == 3) {
			startPos = {
				600,
				720 / 2.f
			};
		}
		else if (i == 4) {
			startPos = {
				800,
				720 / 2.5f
			};
		}
		else if (i == 5) {
			startPos = {
				800,
				720 / 1.7f
			};
		}
		else if (i == 6) {
			startPos = {
				1000,
				720 / 2.0f
			};
		}

		newFloor->Init({(startPos.u + 45), startPos.v}, 135);
		//床を追加
		floors_.push_back(*newFloor);

		delete newFloor;
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
		if (activeNum == 1) activeNum = 2;
		else if (activeNum == 2)activeNum = 1;
		else if (activeNum == 4)activeNum = 5;
		else if (activeNum == 5)activeNum = 4;
	}
	else if (key[KEY_INPUT_S] == true && oldkey[KEY_INPUT_S] == false) {
		if (activeNum == 1) activeNum = 2;
		else if (activeNum == 2)activeNum = 1;
		else if (activeNum == 4)activeNum = 5;
		else if (activeNum == 5)activeNum = 4;
	}

	if (key[KEY_INPUT_A] == true && oldkey[KEY_INPUT_A] == false) {
		if (activeNum == 0) activeNum = 6;
		else if (activeNum == 1) activeNum = 0;
		else if (activeNum == 2)activeNum = 0;
		else if (activeNum == 3)activeNum = 1;
		else if (activeNum == 4)activeNum = 3;
		else if (activeNum == 5)activeNum = 3;
		else if (activeNum == 6)activeNum = 4;
	}
	else if (key[KEY_INPUT_D] == true && oldkey[KEY_INPUT_D] == false) {
		if (activeNum == 0) activeNum = 1;
		else if (activeNum == 1) activeNum = 3;
		else if (activeNum == 2)activeNum = 3;
		else if (activeNum == 3)activeNum = 4;
		else if (activeNum == 4)activeNum = 6;
		else if (activeNum == 5)activeNum = 6;
		else if (activeNum == 6)activeNum = 0;
	}

	if (key[KEY_INPUT_SPACE] == true && oldkey[KEY_INPUT_SPACE] == false) {

		for (Floor& floor : floors_) {
			//沼になっっているときに選択できない
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
					//回転するオブジェクトの座標
					FLOAT2 rotObjPos = {
						enemy[j].GetPos().u,
						enemy[j].GetPos().v
					};

					if (startPos.u <= rotObjPos.u &&
						startPos.v <= rotObjPos.v &&
						endPos.u >= rotObjPos.u &&
						endPos.v >= rotObjPos.v)
					{
						//一回SetDownを変えたら処理を通らないようにする
						if (enemy[j].GetIsFlip() == false) {
							//沈んで入る途中に地面を変更されたら
							if (enemy[j].GetIsDown() == true) {
								enemy[j].SetIsDown(false);
								enemy[j].SetDel(true);

								combo++;
								comboTimer_ = 240;
							}
							//敵を沈ませる
							else {
								//選択した床の上にある星を倒す
								enemy[j].SetIsDown(true);

								combo++;
								comboTimer_ = 240;
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
	//コンボしているとき
	if (combo > 0) {
		if (comboTimer_ > 0) comboTimer_--;
		else {
			comboTimer_ = 240;
			combo = 0;
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

int FloorManager::combo = 0;
int FloorManager::comboTimer_ = 240;