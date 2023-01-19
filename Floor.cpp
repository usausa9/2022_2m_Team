#include "Floor.h"
#include <vector>
#include "FloorManager.h"


void Floor::Init(FLOAT2 startPos, FLOAT2 endPos)
{
	startPos_ = startPos;
	endPos_ = endPos;

}

void Floor::Update()
{
	//沼になったら
	if (isFloorType) {
		if (timer_ > 0)timer_--;
		else {
			isFloorType = false;
			timer_ = maxTimer_;
		}
	}

	
}

void Floor::Draw()
{
	if (isActive_) {
		color = 0xff0000;
	}
	else {
		color = 0xffffff;
	}

	if (isFloorType) {
		color -= 0x500000;
		color += 0x005000;
	}

	DrawBox(
		startPos_.u,
		startPos_.v,
		endPos_.u,
		endPos_.v,
		color, false);
}

void Floor::Move(std::vector<Enemy> enemy)
{
	if (isFlip_) {
		return;
	}
	isFlip_ = true;
	isFloorType = true;

	/*FLOAT2 startPos = GetFloorPos_().at(0);
	FLOAT2 endPos = GetFloorPos_().at(1);*/

	std::vector<FLOAT2> starPos_;

	std::vector<Enemy>& enemy_ = enemy;

	for (int j = 0; j < enemy_.size(); j++) {
		//回転するオブジェクトの座標
		FLOAT2 rotObjPos = {
			enemy_[j].GetPos().u,
			enemy_[j].GetPos().v
		};

		if (startPos_.u <= rotObjPos.u &&
			startPos_.v <= rotObjPos.v &&
			endPos_.u >= rotObjPos.u &&
			endPos_.v >= rotObjPos.v)
		{
			//選択した床の上にある星を検索
			starPos_.push_back(rotObjPos);
		}

	}

	std::vector<Floor>& floors_ = FloorManager::GetFloors();

	for (int i = 0; i < floors_.size(); i++) {
		FLOAT2 startPos = floors_.at(i).GetStartPos();;
		FLOAT2 endPos = floors_.at(i).GetEndPos();
		for (FLOAT2& a : starPos_) {
			if (startPos.u <= a.u &&
				startPos.v <= a.v &&
				endPos.u >= a.u &&
				endPos.v >= a.v)
			{
				//選択した床の上にある星を検索
				floors_[i].Move(enemy_);
			}
		}
	}
}

void Floor::FinishMove()
{
	isFlip_ = false;
}
