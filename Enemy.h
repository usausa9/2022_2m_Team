#pragma once
#include "DxLib.h"
class Enemy
{
public:

	void Init(FLOAT2 pos);

	void Update();

	void Draw();

	FLOAT2 GetPos() { return pos_; }

	void SetDel(bool flag) { del = flag; }

	void SetIsDown(bool flag) { isDown = flag; }

	bool GetIsDown() { return isDown; }

private:
	FLOAT2 pos_;
	float length = 32;
	//’¾‚ñ‚Å‚¢‚é
	bool isDown = false;

	bool del = false;

	int color = 0xffff00;

};

