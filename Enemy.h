#pragma once
#include "DxLib.h"
class Enemy
{
public:

	void Init(FLOAT2 pos);

	void Update();

	void Draw();

	FLOAT2 GetPos() { return pos_; }

private:
	FLOAT2 pos_;
	float length = 32;

};

