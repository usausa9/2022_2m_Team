#include "Floor.h"

void Floor::Init(FLOAT2 startPos, FLOAT2 endPos)
{
	startPos_ = startPos;
	endPos_ = endPos;

}

void Floor::Update()
{
	//À‚É‚È‚Á‚½‚ç
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
