#include "GameStateTwo.h"

void GameStateTwo::LoadResources()
{
	game = CGame::GetInstance();
	camera = new Camera(640, 480);
	simon = Simon::GetInstance();
	simon->SetPosition(SIMON_POSITION_DEFAULT); //33 4 14
	boss = new Boss(5300, 100);
	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/Grid/test1.b", "Resource/sprites/Grid/test1.s", 34, 4, 136, 14, 90);
	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv2.txt"); //20 4 80    14 90
	ui = new UI();
	ui->Initialize(simon, boss);
	door = new Door(3115, 130);
	door2 = new Door(4129, 130);
	simon->isStage1 = false;
	simon->isStage2 = true;
	
	//objects.push_back(boss);
	//2893 156
}

void GameStateTwo::Update(DWORD dt)
{
#pragma region Camera

	if (simon->isColliding(simon, door)) //va cham voi door
	{
		simon->isCollideDor = true;
		simon->Stop();
		door->Update(dt);
		if (camera->GetViewport().x < 2900)
		{
			camera->Go(dt); //move camera
		}
		else
		{
			simon->AutoMove();
			simon->isCollideDor = false;
		}
	}
	else if (simon->isColliding(simon, door2))
	{
		simon->isCollideDor = true;
		simon->Stop();
		door->Update(dt);
		if (camera->GetViewport().x < 4000)
		{
			camera->Go(dt); //move camera
		}
		else
		{
			simon->AutoMove();
			simon->isCollideDor = false;
			simon->isStage21 = false;
		}
	}
	else //het va cham voi cua 
	{
		
		if (simon->y > 450)//y duoi nuoc
		{
			camera->SetPosition(simon->x - 320 + 60, 450);
			camera->UpdateWater();
		}
		else if (simon->x > 3200 && simon->x <4160) //man` 21
		{
			if (camera->GetViewport().x < 3150)
			{
				camera->Go(dt); //move camera sau khi simon di 1 ti
				simon->isStage21 = true;
				simon->isStage2 = false;
			}
			else
			{
				camera->SetPosition(simon->x - 320 + 60, 0); //update man 21
				camera->UpdateMap21();
			}

		}
		else if (simon->x < 3000)//&& simon->isCameraStair==false)
		{
			camera->SetPosition(simon->x - 320 + 60, 0);//update man 2
			camera->UpdateMap2();
		}
		else if (simon->x > 4300)// man 22
		{
			if (camera->GetViewport().x < 4154)
			{
				camera->Go(dt); //move camera sau khi simon di 1 ti
				simon->isStage21 = false;
				simon->isStage22 = true;
				
			}
			else
			{
				if (!simon->isFightingBoss)
				{
					camera->SetPosition(simon->x - 320 + 60, 0); //update man 22
					camera->UpdateMap22();
				}
				else
				{
					camera->SetPosition(5065, 0);//boss
					//camera->SetPosition(boss->x - 320 + 60, 0);
				}
				
			}
		}
		
	}

	
	//else //het va cham voi cua 
	//{
	//	camera->SetPosition(simon->x - 320 + 60, 0);//update man 2
	//	camera->UpdateMap2();
	//}
#pragma endregion




	mapSecond++;
	if (mapSecond > 60)
	{
		mapTime++;
		mapSecond = 0;
	}
	ui->Update( 1000 - mapTime, 3, 1);


	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(boss);
	grid->GetListObject(objects, camera);
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->dropItem == true)
		{
			item = new Item(objects[i]->itemLink, objects[i]->x, objects[i]->y);
			items.push_back(item);
			objects[i]->SetDropItem(false);
			//objects[i]->isCreatedItem = true;//sau khi push item thi moi xoa khoi objects
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
		}
	}
	else
	{

	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, 0, &coObjects);
	}
	simon->Update(dt, camera, &coObjects, &items);
	if (simon->isRosary)
	{
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->tag == 500)
			{
				objects[i]->isDead = true;
			}

		simon->isRosary = false;
	}
	if (simon->isFightingBoss)
	{
		boss->Update(dt, simon->x,simon->y);
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
		//if (simon->y > 450)//y duoi nuoc
		//{
		//	tilemap->DrawMapWater(camera);
		//}
		//else
		//{
		tilemap->DrawMap(camera);
		/*}*/




		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(camera);
		for (int i = 0; i < items.size(); i++)
			items[i]->Render(camera);
		simon->Render(camera);
		boss->Render(camera);
		//whip->Render(camera);
		door->Render(camera);
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
