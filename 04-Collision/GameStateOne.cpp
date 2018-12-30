#include "GameStateOne.h"

void GameStateOne::LoadResources()
{
	Textures * textures = Textures::GetInstance();
	textures->LoadTexture("Resource\\sprites\\Grid\\textures.txt");
	
	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->_texture = textures->Get(1);
	simon->_sprite = new Sprite(textures->Get(1), 150);
	simon->whip->_sprite= new Sprite(textures->Get(2), 100);
	simon->whip->_texture= textures->Get(2);
	simon->isStage1 = true;
	
	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv1.txt");

	vector<CGameObject*> test;
	test = grid->getListObject();
	for (int i = 0; i < test.size(); i++)
	{
		test.at(i)->_sprite = new Sprite(textures->Get(test.at(i)->texId), 100);
		test.at(i)->_texture = textures->Get(test.at(i)->texId);

		test.at(i)->deadffect->_sprite= new Sprite(textures->Get(-1), 50);
		test.at(i)->hiteffect->_sprite = new Sprite(textures->Get(-2), 1000);
	}

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/lv1.b", "Resource/sprites/lv1.s", 10, 4, 40, 6, 24);

	
	checkpoint = new CheckPoint();
	checkpoint->SetPosition(1366, 365);
	


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
		if (dynamic_cast<LargeCandle *>(objects.at(i)))
		{
			//LargeCandle *lc = dynamic_cast<LargeCandle *>(coObjects.at(i));
			if (objects[i]->dropItem == true)
			{
				Textures * textures = Textures::GetInstance();

				item = new Item(objects[i]->itemNumber,objects[i]->x, objects[i]->y);
				item->_sprite = new Sprite(textures->Get(objects[i]->itemNumber), 100);
				item->_texture = textures->Get(objects[i]->itemNumber);
				items.push_back(item);
			}
			objects[i]->SetDropItem(false);
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
		items[i]->Update(dt,0 ,&coObjects);
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
		tilemap->DrawMaplvl1(camera);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);
		simon->Render(camera);
		
		checkpoint->Render(camera);
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

GameStateOne::~GameStateOne()
{
}
