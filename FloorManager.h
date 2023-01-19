#pragma once
#include "Floor.h"
#include <vector>
#include "Enemy.h"

typedef struct pos
{
	int x;
	int y;
};

class FloorManager
{
public:

	static void Init();

	static void Update(char key[], char oldkey[], std::vector<Enemy>& enemy);

	static void Draw();

	static std::vector<Floor>& GetFloors() {return floors_;}

	static int GetCombo() { return combo; }

	static int GetComboTimer() { return comboTimer_; }

private:
	static int boxSize;

	static pos box;

	static std::vector<Floor> floors_;

	static int activeNum;

	static int combo;
	static int comboTimer_;
};

