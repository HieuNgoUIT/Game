#include "GameStateTwo.h"

void GameStateTwo::LoadResources()
{
	Textures * textures = Textures::GetInstance();

	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT); //33 4 14

	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv2.txt"); //20 4 80    14 90
	vector<CGameObject*> test;
	test = grid->getListObject();
	for (int i = 0; i < test.size(); i++)
	{
		test.at(i)->_texture = textures->Get(test.at(i)->texId);
		test.at(i)->_sprite = new Sprite(textures->Get(test.at(i)->texId), 100);
		test.at(i)->deadffect->_sprite = new Sprite(textures->Get(-1), 50);
		test.at(i)->hiteffect->_sprite = new Sprite(textures->Get(-2), 1000);
	}

	
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera->SetBorder(60, 2500);
	

	
	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/Grid/lv2.b", "Resource/sprites/Grid/lv2.s", 34, 4, 136, 14, 90);

	

	ui = new UI();
	ui->Initialize(simon, boss);
	
	simon->isStage1 = false;
	simon->isStage2 = true;
	if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
		Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);
	game = CGame::GetInstance();
	boss = new Boss(5300, 100);
}

void GameStateTwo::Update(DWORD dt)
{
	mapSecond++;
	if (mapSecond > 60)
	{
		mapTime++;
		mapSecond = 0;
	}
	ui->Update(1000 - mapTime, 3, 1);


#pragma region Camera

	if (simon->isCollideDor)
	{
		camera->SetBorder(simon->x, simon->x + 640);
		camera->Go(dt);
		if (camera->GetViewport().x > camera->_borderLeft)
		{
			simon->AutoMove();
		}
		
	}
	else
	{
		camera->SetPosition(simon->x - 320 + 60, simon->y - 480);
		if (simon->y > 450)
		{
			
//			camera->UpdateWater();
		}
		else
		{

//			camera->Update();
		}
	}
		
		
		

	//}
	
#pragma endregion

	simon->CheckBoundaries(camera->_borderLeft, camera->_borderRight + 600);



	


	vector<LPGAMEOBJECT> coObjects;
	
	grid->GetListObject(objects, camera);
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<Candle *>(objects.at(i)))
		{
			//LargeCandle *lc = dynamic_cast<LargeCandle *>(coObjects.at(i));
			if (objects[i]->dropItem == true)
			{
				Textures * textures = Textures::GetInstance();

				item = new Item(objects[i]->itemNumber, objects[i]->x, objects[i]->y);
				item->_sprite = new Sprite(textures->Get(objects[i]->itemNumber), 100);
				item->_texture = textures->Get(objects[i]->itemNumber);
				items.push_back(item);
			}
			objects[i]->SetDropItem(false);
		}
		else if (dynamic_cast<Merman *>(objects[i]))
		{
			Merman *boss = dynamic_cast<Merman *>(objects[i]);
			coObjects.push_back(boss);
			coObjects.push_back(boss->fireball);
			objects.push_back(boss->fireball);		
		}
		else
		{
			coObjects.push_back(objects[i]); //neu ma rot item =false thi` da~ chet' nen ko push vao co0bject nua
		}
	}
	

	if (!simon->isStopwatch)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, simon->x, &coObjects);
			if (dynamic_cast<Zombie *>(objects[i]))
			{
				Zombie *zombie = dynamic_cast<Zombie *>(objects[i]);
				zombie->Update(dt,camera, simon->x, &coObjects);
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
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, 0, &coObjects);
	}
	simon->Update(dt, &coObjects, &items);
	if (simon->isRosary)
	{
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->tag == ENEMY_TAG)
			{
				objects[i]->health -= 10;
			}

		simon->isRosary = false;
	}
	
	if (simon->isFightingBoss)
	{
		boss->Update(dt, simon->x, simon->y, &coObjects);
		if (Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
		{
			Sound::GetInstance()->Stop(STAGE_01_VAMPIRE_KILLER);
			Sound::GetInstance()->Play(BOSS_BATTLE_POISON_MIND);
		}
		if (Sound::GetInstance()->IsPLaying(STAGE_CLEAR))
		{
			Sound::GetInstance()->Stop(BOSS_BATTLE_POISON_MIND);
		}
		//Sound::GetInstance()->Play(BOSS_BATTLE_POISON_MIND);
	}

	

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

		ui->Render();
		
		tilemap->DrawMap(camera);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);
		simon->Render(camera);
		boss->Render(camera);
		//door->Render(camera);
		//door2->Render(camera);
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameStateTwo::CheckCollideWithDoor(Simon * simon, Door * door)
{
	if (simon->isColliding(simon, door))
	{

	}

}

GameStateTwo::GameStateTwo()
{

}
