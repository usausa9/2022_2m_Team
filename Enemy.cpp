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
			float speed = 0.2f;
			length -= speed;
		}
	}
	else {
		//ˆÚ“®‚·‚é
		pos_.u += speed;
	}

	if (pos_.u < 0) {
		del = true;
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

float Enemy::speed = -1.5f;