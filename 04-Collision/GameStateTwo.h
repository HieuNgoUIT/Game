#pragma once
#include "GameState.h"
#include "Simon.h"
#include "Door.h"
#include "Boss.h"
class GameStateTwo :public GameState
{
public:

	Door * door;
	Door * door2;
	Boss *boss;
	bool isCollideDoor;
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void CheckCollideWithDoor(Simon* simon, Door *door);
	GameStateTwo();
};