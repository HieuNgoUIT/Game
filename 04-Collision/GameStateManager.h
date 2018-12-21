#pragma once
#include "GameStateOne.h"
#include "GameStateTwo.h"
#include "GameState.h"
#include "Simon.h"
class GameStateManager {
public:
	GameState* gamestate;
	int stateId;
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	GameStateManager(int stateId);
	Simon* GetSimon();
};