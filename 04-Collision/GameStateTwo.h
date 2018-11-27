#pragma once
#include "GameState.h"
#include "Simon.h"
#include "Door.h"
class GameStateTwo :public GameState
{
public:
	int test = 245;
	Door * door;
	bool isCollideDoor;
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void CheckCollideWithDoor(Simon* simon, Door *door);
	GameStateTwo();
};