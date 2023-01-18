#pragma once
#include "DxLib.h"
class Floor
{
public:

	void Init(FLOAT2 startPos, FLOAT2 endPos);

	void Update();

	void Draw();

	void SetActive(bool flag) { isActive_ = flag; }

private:

	FLOAT2 startPos_;
	FLOAT2 endPos_;

	bool isActive_ = false;

	int color = 0xffffff;

};

