#include "GameStateOne.h"

void GameStateOne::LoadResources()
{
	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	
	simon->isStage1 = true;
	

	camera = new Camera(640, 480);

	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/lv1.b", "Resource/sprites/lv1.s", 10, 4, 40, 6, 24);

	
	checkpoint = new CheckPoint();
	checkpoint->SetPosition(1366, 365);
	
	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv1.txt");
	ui = new UI();
	ui->Initialize(simon,NULL);
	game = CGame::GetInstance();
	if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
		Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);
}

void GameStateOne::Update(DWORD dt)
{
	mapSecond++;
	if (mapSecond > 60)
	{
		mapTime++;
		mapSecond = 0;
	}
	ui->Update(1000 - mapTime, 3, 1);


	vector<LPGAMEOBJECT> coObjects;
	grid->GetListObject(objects, camera);
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->dropItem == true)
		{
			item = new Item(objects[i]->itemLink, objects[i]->x, objects[i]->y);
			items.push_back(item);
		}
		objects[i]->SetDropItem(false);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt,0 ,&coObjects);
	}
	simon->Update(dt, camera, &coObjects, &items);
	camera->SetPosition(simon->x - 320 + 60, 0);
	camera->Update();
	CheckCollideWithCheckPoint(simon, checkpoint);
}

void GameStateOne::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(0, 0, 0));

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		ui->Render();
		tilemap->DrawMaplvl1(camera);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);
		simon->Render(camera);
		//whip->Render(camera);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameStateOne::KillAll()
{
	/*vector<LPGAMEOBJECT> test;
	Camera *cameratest = new Camera(1536,384);
	grid->GetListObject(test, cameratest);
	for (int i = 0; i < test.size(); i++)
	{
		delete(test[i]);
	}*/
	//grid->DeleteObjects();
	delete grid;
	grid = NULL;

	delete tilemap;
	tilemap = NULL;

	delete ui;
	ui = NULL;
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}
	for (int i = 0; i < items.size(); i++)
	{
		delete items[i];
		items[i] = NULL;
	}
	
}

GameStateOne::GameStateOne()
{

}
