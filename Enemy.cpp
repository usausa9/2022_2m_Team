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
	//����ł�����
	if (isDown) {
		//���S�ɒ��񂾂玀��
		if (length <= 0) {
			del = true;
		}
		//����ł���
		else {
			float speed = 0.2f;
			length -= speed;
		}
	}
	//����ł��Ȃ�������
	else {
		//�ړ�����
		//�E
		if (way_ == 0) pos_.u += speed;
		//��
		else if (way_ == 1)pos_.u -= speed;
		//��
		else if (way_ == 2)pos_.v -= speed;
		//��
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

