#pragma once
#include "DxLib.h"
class Enemy
{
public:

	void Init(FLOAT2 pos, int way);

	void Update();

	void Draw();

	FLOAT2 GetPos() { return pos_; }

	void SetDel(bool flag) { del = flag; }

	bool GetDel() { return del; }

	void SetIsDown(bool flag) { isDown = flag; }

	bool GetIsDown() { return isDown; }

	void SetIsFlip(bool isflip) { isFlip = isflip; }

	bool GetIsFlip() { return isFlip; }

private:
	FLOAT2 pos_;
	float length = 32;
	//íæÇÒÇ≈Ç¢ÇÈ
	bool isDown = false;

	bool del = false;

	int color = 0xffff00;

	bool isFlip = false;

	float speed = -4.0f;
	//êiÇﬁï˚å¸
	//0 âE, 1 ç∂, 2 è„ , 3 â∫
	int way_;

};

