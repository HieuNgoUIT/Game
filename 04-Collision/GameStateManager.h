#pragma once
#include "GameStateOne.h"
#include "GameStateTwo.h"
#include "GameState.h"
class GameStateManager {
public:
	GameState* gamestate;
	int stateId;
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	GameStateManager(int stateId);
};