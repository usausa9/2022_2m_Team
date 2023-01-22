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
	//’¾‚ñ‚Å‚¢‚½‚ç
	if (isDown) {
		//Š®‘S‚É’¾‚ñ‚¾‚çŽ€‚Ê
		if (length <= 0) {
			del = true;
		}
		//’¾‚ñ‚Å‚¢‚­
		else {
			float speed = 0.2f;
			length -= speed;
		}
	}
	//’¾‚ñ‚Å‚¢‚È‚©‚Á‚½‚ç
	else {
		//ˆÚ“®‚·‚é
		//‰E
		if (way_ == 0) pos_.u += speed;
		//¶
		else if (way_ == 1)pos_.u -= speed;
		//ã
		else if (way_ == 2)pos_.v -= speed;
		//‰º
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

