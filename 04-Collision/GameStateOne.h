#pragma once
#include "GameState.h"

class GameStateOne :public GameState
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void KillAll();
	GameStateOne();
};