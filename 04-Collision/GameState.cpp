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
	textures->LoadTexture(Ftexture);

	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT);

	LoadTextSprite(simon, 1, 150);
	LoadTextSprite(simon->whip, 2);


	grid = new Grid();
	grid->ReadFileToGrid(Fgrid);

	ui = new UI();
	ui->Initialize(simon, NULL);

	vector<CGameObject*> listobj;
	listobj = grid->getListObject();
	for (int i = 0; i < listobj.size(); i++)
	{
		if (dynamic_cast<Door *>(listobj[i]))
		{
			LoadTextSprite(listobj.at(i), listobj.at(i)->texId, 1500);
		}
		else
		{
			LoadTextSprite(listobj.at(i), listobj.at(i)->texId);
		}

	}

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetBorder(LBORDER_1, RBORDER_1);

	tilemap = new TileMap();
	tilemap->LoadMap(Fb, Fs, Frow, Fcol, Ftotal, Frowmaxtrix, Fcolmatrix);
	//file .b .s , cot dong cho texture, cot dong trong ma tran

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
				item = new Item(objects[i]->itemNumber, objects[i]->x, objects[i]->y);
				LoadTextSprite(item, objects[i]->itemNumber);
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
			objects.push_back(mm->fireball); //cho update
		}
		else
		{
			coObjects.push_back(objects[i]);
		}
	}

	if (!simon->isStopwatch)
	{
		//update bth
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
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->tag != ENEMY_TAG)
			{
				objects[i]->Update(dt, simon->x, &coObjects);
			}

		}
		WatchTime--;
	}
	if (WatchTime < 0)
	{
		simon->isStopwatch = false;
	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, NULL, &coObjects);
	}

	CheckClearAllObj();

	simon->Update(dt, &coObjects, &items);

	CheckCollideWithCheckPoint(simon);

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


		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameState::CheckCollideWithCheckPoint(Simon * simon)
{
	if (simon->isCollideCheckPoint)
	{
		this->isChangingState = true;
		this->id++;
	}
}

void GameState::LoadTextSprite(LPGAMEOBJECT obj, int textureID, int tineAniFrame)
{
	Textures * textures = Textures::GetInstance();
	Texture *txtemp = textures->Get(textureID);

	obj->_texture = txtemp;
	obj->_sprite = new Sprite(txtemp, tineAniFrame);

	obj->deadffect->_sprite = new Sprite(textures->Get(-1), 50);
	obj->hiteffect->_sprite = new Sprite(textures->Get(-2), 1000);
}

void GameState::CheckClearAllObj()
{
	if (simon->isRosary)
	{
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->tag == ENEMY_TAG)
			{
				objects[i]->health -= 10;
			}

		simon->isRosary = false;
	}
}
