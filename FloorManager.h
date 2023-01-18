#pragma once
#include "Floor.h"
#include <vector>

typedef struct pos
{
	int x;
	int y;
};

class FloorManager
{
public:

	static void Init();

	static void Update();

	static void Draw();

	static std::vector<Floor> GetFloor() {return floors_;}

private:
	static int boxSize;

	static pos box;

	static std::vector<Floor> floors_;
};

