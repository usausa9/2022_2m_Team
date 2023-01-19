#include "Enemy.h"

void Enemy::Init(FLOAT2 pos)
{
	pos_ = pos;
}

void Enemy::Update()
{
	if (del) {
		color = 0xff0000;
	}
	else {
		color = 0xffff00;
	}

	if (isDown) {
		if (length <= 0) {
			
			del = true;
		}
		else {
			length -= 0.10f;
		}
	}
	else {
		//ˆÚ“®‚·‚é
		pos_.u -= 1.5f;
	}
}

void Enemy::Draw()
{
	DrawBox(
		pos_.u - length,
		pos_.v - length,
		pos_.u + length,
		pos_.v + length,
		color, false);

	DrawCircle(
		pos_.u,
		pos_.v,
		3,
		color, true);
}
