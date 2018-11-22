/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Texture.h"
#include "Simon.h"
#include "TileMap.h"
#include "Brick.h"
#include "Sound.h"
#include "gamestatemanager.h"
#include "GameStateManager.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120




HWND hWnd;

GameStateManager *gamestatemanager;


//Whip *whip;
//Item *item;
//Grid *grid;
//UI *ui;
//int mapSecond = 0;
//int mapTime = 0;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	//switch (KeyCode)
	//{
	//case DIK_SPACE:
	//	mario->SetState(MARIO_STATE_JUMP);
	//	break;
	//case DIK_A: // reset
	//	mario->SetState(MARIO_STATE_IDLE);
	//	mario->SetLevel(MARIO_LEVEL_BIG);
	//	mario->SetPosition(50.0f,0.0f);
	//	mario->SetSpeed(0, 0);
	//	break;
	//}
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(hWnd); // thoát

	if (KeyCode == DIK_Q)
		gamestatemanager->gamestate->simon->SetPosition(SIMON_POSITION_DEFAULT);

	if (KeyCode == DIK_SPACE)
	{
		if (gamestatemanager->gamestate->simon->isJumping == false)
			gamestatemanager->gamestate->simon->Jump();
	}

	if (KeyCode == DIK_1)
	{
		DebugOut(L"[SIMON] X = %f , Y = %f \n", gamestatemanager->gamestate->simon->x + 10, gamestatemanager->gamestate->simon->y);
	}

	if (KeyCode == DIK_X)
	{
		gamestatemanager->gamestate->simon->Attack();
	}
	if (KeyCode == DIK_RCONTROL)
	{
		gamestatemanager->gamestate->simon->ThrowSubWp();
	}

}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	/*if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else
		mario->SetState(MARIO_STATE_IDLE);*/
	if (gamestatemanager->gamestate->game->IsKeyDown(DIK_DOWN))
	{
		gamestatemanager->gamestate->simon->Sit();

		if (gamestatemanager->gamestate->game->IsKeyDown(DIK_RIGHT))
			gamestatemanager->gamestate->simon->Right();

		if (gamestatemanager->gamestate->game->IsKeyDown(DIK_LEFT))
			gamestatemanager->gamestate->simon->Left();

		return;
	}
	else
		gamestatemanager->gamestate->simon->Stop();


	if (gamestatemanager->gamestate->game->IsKeyDown(DIK_RIGHT))
	{
		gamestatemanager->gamestate->simon->Right();
		gamestatemanager->gamestate->simon->Go();
		if (gamestatemanager->gamestate->simon->isAttacking == true)
		{
			gamestatemanager->gamestate->simon->Stop();
		}
	}
	else
		if (gamestatemanager->gamestate->game->IsKeyDown(DIK_LEFT))
		{
			gamestatemanager->gamestate->simon->Left();
			gamestatemanager->gamestate->simon->Go();
			if (gamestatemanager->gamestate->simon->isAttacking == true)
			{
				gamestatemanager->gamestate->simon->Stop();
			}
		}
		else
		{
			gamestatemanager->gamestate->simon->Stop();
		}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{

	//simon = new Simon();
	//simon->SetPosition(SIMON_POSITION_DEFAULT);
	////simon->SetPosition(0, 0);

	////brick = new Brick(0, 400, 1536, 32);
	////objects.push_back(brick);

	//camera = new Camera(640, 480);

	//tilemap = new TileMap();
	//tilemap->LoadMap();

	////largecandle = new LargeCandle(300, 265);
	////objects.push_back(largecandle);

	////largecandle = new LargeCandle(350, 200);
	////objects.push_back(largecandle);
	///*Sound::GetInstance()->Stop(GAME_START_PROLOGUE);

	//if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
	//	Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);*/
	//grid = new Grid();
	//grid->ReadFileToGrid("Resource\\sprites\\Grid\\lv1.txt");
	//ui = new UI();
	//ui->Initialize(simon, 16);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	////countdown
	//mapSecond++;
	//if (mapSecond > 60)
	//{
	//	mapTime++;
	//	mapSecond = 0;
	//}
	//ui->Update(16, 1000 - mapTime, 3, 1);

	////tilemap->DrawMap(camera);
	//// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	//// TO-DO: This is a "dirty" way, need a more organized way 
	//vector<LPGAMEOBJECT> coObjects;
	//grid->GetListObject(objects, camera);
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	if (objects[i]->dropItem == true)
	//	{
	//		item = new Item(objects[i]->x, objects[i]->y);
	//		items.push_back(item);
	//		objects[i]->SetDropItem(false);
	//		//objects[i]->isCreatedItem = true;//sau khi push item thi moi xoa khoi objects
	//	}
	//}
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	coObjects.push_back(objects[i]);
	//}
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Update(dt);
	//}
	//for (int i = 0; i < items.size(); i++)
	//{
	//	items[i]->Update(dt);
	//}
	//simon->Update(dt, &coObjects, &items);
	//camera->SetPosition(simon->x - 320 + 60, 0);
	//camera->Update();


}

/*
	Render a frame
*/
void Render()
{
	//LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	//LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	//LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	//if (d3ddv->BeginScene())
	//{
	//	// Clear back buffer with a color
	//	d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

	//	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//	ui->Render();
	//	tilemap->DrawMap(camera);

	//	for (int i = 0; i < objects.size(); i++)
	//		objects[i]->Render(camera);
	//	for (int i = 0; i < items.size(); i++)
	//		items[i]->Render(camera);
	//	simon->Render(camera);
	//	//whip->Render(camera);

	//	spriteHandler->End();
	//	d3ddv->EndScene();
	//}

	//// Display back buffer content to the screen
	//d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			gamestatemanager->gamestate->game->ProcessKeyboard();

			gamestatemanager->Update(dt);
			
			gamestatemanager->Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	gamestatemanager = new GameStateManager(1);
	//gamestatemanager->game = CGame::GetInstance();
	gamestatemanager->gamestate->game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	gamestatemanager->gamestate->game->InitKeyboard(keyHandler);

	//Sound::GetInstance()->loadSound(hWnd);
	gamestatemanager->LoadResources();
	

	//LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}