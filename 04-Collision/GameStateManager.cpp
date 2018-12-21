#include "GameStateManager.h"

void GameStateManager::LoadResources()
{
	
	gamestate->LoadResources();
}

void GameStateManager::Update(DWORD dt)
{
	if (gamestate->isChangingState)
	{
		gamestate->KillAll();
		gamestate = new GameStateTwo();		
		gamestate->LoadResources();
		gamestate->isChangingState = false;	
	}
	gamestate->Update(dt);
}

void GameStateManager::Render()
{
	gamestate->Render();
}

GameStateManager::GameStateManager(int stateId)
{
	switch (stateId)
	{
	case 1:
		gamestate = new GameStateOne();
		break;
	case 2:
		gamestate = new GameStateTwo();
		break;
	}
	gamestate->game = CGame::GetInstance();
}

Simon* GameStateManager::GetSimon()
{
	return this->gamestate->simon;
}
