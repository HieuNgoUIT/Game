#include "GameStateTwo.h"

void GameStateTwo::LoadResources()
{
	game = CGame::GetInstance();
	camera = new Camera(640, 480);
	simon = new Simon();
	simon->SetPosition(SIMON_POSITION_DEFAULT);
	tilemap = new TileMap();
	tilemap = new TileMap();
	tilemap->LoadMap("Resource/sprites/Grid/lv2.b", "Resource/sprites/Grid/lv2.s", 20, 4, 80, 14, 90); // 18 4 72 12 88
	grid = new Grid();
	grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv2.txt"); //20 4 80    14 90
	ui = new UI();
	ui->Initialize(simon, 16);
	door = new Door(3043, 120);
	//2893 156
}

void GameStateTwo::Update(DWORD dt)
{
#pragma region Camera
	
	if (simon->isColliding(simon, door)) //va cham voi door
	{
		door->Update(dt);
		if (camera->GetViewport().x < 2800)
		{
			camera->Go(dt); //move camera
		}
		else
		{
			simon->AutoMove();
		}
	}
	else //het va cham voi cua 
	{
		if (simon->y > 450)//y duoi nuoc
		{
			camera->SetPosition(simon->x - 320 + 60, 450);
		}
		else if (simon->x > 3200) //man` 21
		{
			if (camera->GetViewport().x < 3025)
			{
				camera->Go(dt); //move camera sau khi simon di 1 ti
				simon->isStage21 = true;
			}
			else
			{
				camera->SetPosition(simon->x - 320 + 60, 0); //update man 21
				camera->UpdateMap21();
			}

		}
		else if (simon->x < 3000 && simon->isCameraStair==false)
		{
			camera->SetPosition(simon->x - 320 + 60, 0);//update man 2
			camera->UpdateMap2();
		}
	}


#pragma endregion




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
			item = new Item(objects[i]->x, objects[i]->y);
			items.push_back(item);
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
		objects[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt);
	}
	simon->Update(dt,camera, &coObjects, &items);

	//door->_sprite->SelectIndex(0);

	//for(int i=0;i<3000;i++)
	//{
	//	//int i = 0;
	//	camera->SetPosition(simon->x - 320 + 60+i, 0);
	//	//i++;
	//}


	/*if (simon->x > 2681)
	{*/



	/*}*/

	//CheckCollideWithCheckPoint(simon, checkpoint);
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
