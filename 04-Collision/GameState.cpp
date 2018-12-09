#include "GameState.h"


void GameState::LoadResources()
{
}

void GameState::Update(DWORD dt)
{
}

void GameState::Render()
{
}

void GameState::CheckCollideWithCheckPoint(Simon * simon, CheckPoint * checkpoint)
{
	if (simon->isCollisionWithCheckPoint(checkpoint))
	{
		if (game->IsKeyDown(DIK_UP))
		{
			this->isChangingState = true;
		}
		
	}
}

void GameState::KillAll()
{
}
