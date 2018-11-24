#include "GameStateTwo.h"

void GameStateTwo::LoadResources()
{
	game = CGame::GetInstance();
	camera = new Camera(640, 480);
	simon = new Simon();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	tilemap = new TileMap();
	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/lv2.b", "Resource/sprites/lv2.s",18,4,72,12,88);
}

void GameStateTwo::Update(DWORD dt)
{
}

void GameStateTwo::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(0, 0, 0));

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//ui->Render();
		tilemap->DrawMap(camera);

	/*	for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);
		simon->Render(camera);*/
		//whip->Render(camera);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

GameStateTwo::GameStateTwo()
{
	
}
