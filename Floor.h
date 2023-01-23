#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include <vector>
class Floor
{
public:

	void Init(FLOAT2 startPos, FLOAT2 endPos);

	void Init(FLOAT2 Pos, int size);

	void Update();

	void Draw();

	void SetActive(bool flag) { isActive_ = flag; }

	void SetFloorType(bool type) { isFloorType = type; }

	void Move(std::vector<Enemy> enemy);

	void Lock() { isLock_ = true; }

	bool GetFlipState() { return isFlip_; }
	void SetFlipState(bool flag) { isFlip_ = flag; }
	//��]���ł��t���O���I�t��
	void FinishMove();

	FLOAT2 GetStartPos() { return startPos_; }
	FLOAT2 GetEndPos() { return endPos_; }

	bool GetActive() { return isActive_; }
	bool GetFloorType() { return isFloorType; }

	

private:

	FLOAT2 startPos_;
	FLOAT2 endPos_;
	//�ʏ폰�ɖ߂�^�C�}�[
	int maxTimer_ = 240;
	int timer_ = maxTimer_;

	bool isActive_ = false;

	int color = 0xffffff;
	//false�@�ʏ�Atrue�@��Ȃ���
	bool isFloorType = false;

	//��]���ł��t���O
	bool isFlip_ = false;
	//true�̎��ς����Ȃ�
	bool isLock_ = false;

};

