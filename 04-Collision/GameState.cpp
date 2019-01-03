#include "GameState.h"




GameState::GameState()
{
	game = CGame::GetInstance();
}

GameState::~GameState()
{
}

void GameState::LoadResources(char* Ftexture, char* Fgrid, char* Fb, char* Fs, int Frow, int Fcol, int Ftotal, int Frowmaxtrix, int Fcolmatrix)
{

	Textures * textures = Textures::GetInstance();
	textures->LoadTexture(Ftexture); //"Resource\\sprites\\Grid\\textures.txt"

	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	simon->_texture = textures->Get(1);
	simon->_sprite = new Sprite(textures->Get(1), 150);
	simon->whip->_sprite = new Sprite(textures->Get(2), 100);
	simon->whip->_texture = textures->Get(2);
	simon->isStage1 = true;

	grid = new Grid();
	grid->ReadFileToGrid(Fgrid); //"Resource\\sprites\\Grid\\lv1.txt"




	ui = new UI();
	ui->Initialize(simon, NULL);

	vector<CGameObject*> listobj;
	listobj = grid->getListObject();
	for (int i = 0; i < listobj.size(); i++)
	{
		listobj.at(i)->_texture = textures->Get(listobj.at(i)->texId);
		
		listobj.at(i)->deadffect->_sprite = new Sprite(textures->Get(-1), 50);
		listobj.at(i)->hiteffect->_sprite = new Sprite(textures->Get(-2), 1000);
		if (dynamic_cast<Door *>(listobj[i]))
		{
			listobj.at(i)->_sprite = new Sprite(textures->Get(listobj.at(i)->texId), 1500);
		}
		else
		{
			listobj.at(i)->_sprite = new Sprite(textures->Get(listobj.at(i)->texId), 100);
		}
	}

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetBorder(LBORDER_1, RBORDER_1);

	tilemap = new TileMap();
	tilemap->LoadMap(Fb, Fs, Frow, Fcol, Ftotal, Frowmaxtrix, Fcolmatrix);
	// "Resource/sprites/Grid/lv1.b", "Resource/sprites/Grid/lv1.s", 9, 4, 36, 6, 24


	checkpoint = new CheckPoint();
	checkpoint->SetPosition(1366, 365);


	if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
		Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);
}

void GameState::Update(DWORD dt)
{
	mapSecond++;
	if (mapSecond > 60)
	{
		mapTime++;
		mapSecond = 0;
	}

	


#pragma region Camera

	if (simon->isCollideDor)
	{
		camera->SetBorder(simon->x, RBORDER_2);
		camera->Go(dt);
		if (camera->GetViewport().x > camera->_borderLeft)
		{
			simon->AutoMove();
		}
	}
	else
	{
		camera->SetPosition(simon->x - SCREEN_WIDTH / 2 + simon->_texture->FrameWidth, simon->y - SCREEN_HEIGHT);
		if (simon->y > yWATER)
		{
			camera->SetBoundariesWater();
		}
		else
		{
			camera->SetBoundaries();
		}
	}

	if (simon->x > xBOSS)
	{
		simon->isFightingBoss = true;
 		camera->SetBorder(RBORDER_2, RBORDER_2); // cuoi cung boss nen trung voi bien cuoi
	}

#pragma endregion

	simon->CheckBoundaries(camera->_borderLeft, camera->_borderRight + SCREEN_WIDTH - simon->_texture->FrameWidth);

	vector<LPGAMEOBJECT> coObjects;
	grid->GetListObject(objects, camera);
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Candle *>(objects.at(i)) || dynamic_cast<LargeCandle *>(objects.at(i)))
		{
			if (objects[i]->dropItem == true)
			{
				Textures * textures = Textures::GetInstance();
				item = new Item(objects[i]->itemNumber, objects[i]->x, objects[i]->y);
				item->_sprite = new Sprite(textures->Get(objects[i]->itemNumber), 100);
				item->_texture = textures->Get(objects[i]->itemNumber);
				items.push_back(item);
			}
			else
			{
				coObjects.push_back(objects[i]); // neu ma rot item = false thi` da~chet' nen ko push vao co0bject nua
			}
			objects[i]->SetDropItem(false);

		}
		else if (dynamic_cast<Merman *>(objects[i]))
		{
			Merman *mm = dynamic_cast<Merman *>(objects[i]);
			coObjects.push_back(mm);
			coObjects.push_back(mm->fireball);
			objects.push_back(mm->fireball);
		}
		else
		{
			coObjects.push_back(objects[i]);
		}
	}

	
	if (!simon->isStopwatch)
	{
		for (int i = 0; i < objects.size(); i++)
		{

			if (dynamic_cast<Zombie *>(objects[i]))
			{
				Zombie *zombie = dynamic_cast<Zombie *>(objects[i]);
				zombie->Update(dt, camera, simon->x, &coObjects);
			}
			else if (dynamic_cast<Boss *>(objects[i]))
			{
				Boss *boss = dynamic_cast<Boss *>(objects[i]);
				boss->Update(dt, simon->x, simon->y, simon->isFightingBoss, &coObjects);
				bossHP = boss->health;
			}
			else
			{
				objects[i]->Update(dt, simon->x, &coObjects);
			}
		}
	}
	else
	{
		WatchTime--;
	}
	if (WatchTime < 0)
	{
		simon->isStopwatch = false;
	}


	if (simon->isRosary)
	{
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->tag == ENEMY_TAG)
			{
				objects[i]->health -= 10;
			}

		simon->isRosary = false;
	}


	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, NULL, &coObjects);
	}
	simon->Update(dt, &coObjects, &items);


	CheckCollideWithCheckPoint(simon, checkpoint);
	ui->Update(1000 - mapTime, 3, 1, bossHP);
	
}

void GameState::Render()
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
		if (boss != NULL)
		{
			boss->Render(camera);
		}
		checkpoint->Render(camera);
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameState::CheckCollideWithCheckPoint(Simon * simon, CheckPoint * checkpoint)
{
	if (simon->isCollisionWithCheckPoint(checkpoint))
	{
		if (game->IsKeyDown(DIK_UP))
		{
			this->id++;
		}

	}
}

void GameState::KillAll()
{

}
