#pragma once
#include "DxLib.h"
class Floor
{
public:

	void Init(FLOAT2 startPos, FLOAT2 endPos);

	void Update();

	void Draw();

	void SetActive(bool flag) { isActive_ = flag; }

	void SetFloorType(bool type) { isFloorType = type; }

private:

	FLOAT2 startPos_;
	FLOAT2 endPos_;

	int maxTimer_ = 240;
	int timer_ = maxTimer_;

	bool isActive_ = false;

	int color = 0xffffff;
	//falseÅ@í èÌÅAtrueÅ@íÍÇ»Çµè¿
	bool isFloorType = false;

};

