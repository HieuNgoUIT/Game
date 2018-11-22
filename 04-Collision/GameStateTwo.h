#pragma once
#include "GameState.h"

class GameStateTwo :public GameState
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	GameStateTwo();
};