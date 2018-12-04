#include "GameStateOne.h"

void GameStateOne::LoadResources()
{
	simon = new Simon();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	//simon->SetPosition(0, 0);

	//brick = new Brick(0, 400, 1536, 32);
	//objects.push_back(brick);

	camera = new Camera(640, 480);

	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/lv1.b", "Resource/sprites/lv1.s",10,4,40,6,24);

	//largecandle = new LargeCandle(300, 265);
	//objects.push_back(largecandle);
	checkpoint = new CheckPoint();
	checkpoint->SetPosition(1366, 365);
	//largecandle = new LargeCandle(350, 200);
	//objects.push_back(largecandle);
	/*Sound::GetInstance()->Stop(GAME_START_PROLOGUE);

	if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
	Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);*/
	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv1.txt");
	ui = new UI();
	ui->Initialize(simon, 16);
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
	ui->Update(16, 1000 - mapTime, 3, 1);

	
	vector<LPGAMEOBJECT> coObjects;
	grid->GetListObject(objects, camera);
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->dropItem == true)
		{
			if (objects[i]->currentPosMap1==0 || objects[i]->currentPosMap1 == 3)
			{
				item = new Item(HEART_PATH, objects[i]->x, objects[i]->y);
				items.push_back(item);
			}
			else if (objects[i]->currentPosMap1 == 1 || objects[i]->currentPosMap1 == 2)
			{
				item = new Item(WHIP_PATH, objects[i]->x, objects[i]->y);
				items.push_back(item);
			}
			else if (objects[i]->currentPosMap1 == 4)
			{
				item = new Item(KNIFE_PATH, objects[i]->x, objects[i]->y);
				items.push_back(item);
			}		
			objects[i]->SetDropItem(false);
			//objects[i]->isCreatedItem = true;//sau khi push item thi moi xoa khoi objects
		}
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
		items[i]->Update(dt);
	}
	simon->Update(dt, &coObjects, &items);
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
		tilemap->DrawMap(camera);

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
	delete camera;
	delete tilemap;
	delete ui;
	delete grid;
	delete checkpoint;
	delete simon;
}

GameStateOne::GameStateOne()
{
	
}
