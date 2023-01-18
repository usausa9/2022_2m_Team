#include "Enemy.h"

void Enemy::Init(FLOAT2 pos)
{
	pos_ = pos;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawBox(
		pos_.u - length,
		pos_.v - length,
		pos_.u + length,
		pos_.v + length,
		0xffff00, false);
}
