#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include <vector>
class Floor
{
public:

	void Init(FLOAT2 startPos, FLOAT2 endPos);

	void Update();

	void Draw();

	void SetActive(bool flag) { isActive_ = flag; }

	void SetFloorType(bool type) { isFloorType = type; }

	void Move(std::vector<Enemy> enemy);

	bool GetFlipState() { return isFlip_; }
	//回転中ですフラグをオフに
	void FinishMove();

	FLOAT2 GetStartPos() { return startPos_; }
	FLOAT2 GetEndPos() { return endPos_; }

	bool GetActive() { return isActive_; }

private:

	FLOAT2 startPos_;
	FLOAT2 endPos_;
	//通常床に戻るタイマー
	int maxTimer_ = 120;
	int timer_ = maxTimer_;

	bool isActive_ = false;

	int color = 0xffffff;
	//false　通常、true　底なし沼
	bool isFloorType = false;

	//回転中ですフラグ
	bool isFlip_ = false;

};

