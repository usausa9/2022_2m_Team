#include "FloorManager.h"

void FloorManager::Init()
{
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			Floor* newFloor = new Floor;
			//ç∂è„
			FLOAT2 startPos = {
				box.x + (x * boxSize),
				box.y + (y * boxSize)
			};
			//âEâ∫
			FLOAT2 endPos = {
				box.x + ((x + 1) * boxSize) + 70,
				box.y + ((y + 1) * boxSize) + 70
			};

			newFloor->Init(startPos, endPos);
			//è∞Çí«â¡
			floors_.push_back(*newFloor);

			delete newFloor;
		}

	}
}

void FloorManager::Update() {
	for (auto& floor : floors_) {
		floor.Update();
	}

}

void FloorManager::Draw() {
	for (auto& floor : floors_) {
		floor.Draw();
	}
}

std::vector<Floor> FloorManager::floors_;

int FloorManager::boxSize = 270;

pos FloorManager::box = { 200,50 };