#include "Floor.h"

void Floor::Init(FLOAT2 startPos, FLOAT2 endPos)
{
	startPos_ = startPos;
	endPos_ = endPos;

}

void Floor::Update()
{
}

void Floor::Draw()
{
	if (isActive_) {
		color = 0xff0000;
	}
	else {
		color = 0xffffff;
	}

	DrawBox(
		startPos_.u,
		startPos_.v,
		endPos_.u,
		endPos_.v,
		color, false);
}
