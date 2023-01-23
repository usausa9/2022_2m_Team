#include "Boss.h"

void Boss::Init()
{
	pos_.u = 640;
	pos_.v = 360;
}

void Boss::Update()
{
}

void Boss::Draw()
{
	DrawCircle(pos_.u, pos_.v, 64, 0x00ffff, false);
	DrawCircle(pos_.u, pos_.v, 3, 0x00ffff, true);
}
