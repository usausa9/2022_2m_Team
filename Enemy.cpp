#include "Enemy.h"

void Enemy::Init(FLOAT2 pos, int way)
{
	pos_ = pos;

	way_ = way;
}

void Enemy::Update()
{
	if (del) {
		color = 0xff0000;
	}
	else {
		color = 0xffff00;
	}
	//沈んでいたら
	if (isDown) {
		//完全に沈んだら死ぬ
		if (length <= 0) {
			del = true;
		}
		//沈んでいく
		else {
			float speed = 4.0f;
			length -= speed;
		}
	}
	//沈んでいなかったら
	else {
		//移動する
		//右
		if (way_ == 0) pos_.u += speed;
		//左
		else if (way_ == 1)pos_.u -= speed;
		//上
		else if (way_ == 2)pos_.v -= speed;
		//下
		else if (way_ == 3)pos_.v += speed;
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

