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
#include "Sound.h"
#include "debug.h"
#include "GameState.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define MAX_FRAME_RATE 120


HWND hWnd;

GameState *gamestate;


class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{

	if (gamestate->simon->beingHit) return;

	if (KeyCode == DIK_ESCAPE)
		DestroyWindow(hWnd); // thoát

	if (KeyCode == DIK_Q)
		gamestate->simon->SetPosition(3000, 100);
	if (KeyCode == DIK_M)
	{
		gamestate->isChangingState = true;
		gamestate->id++;
	}
	if (KeyCode == DIK_SPACE)
	{
		if (gamestate->simon->isJumping == false)
			gamestate->simon->Jump();
	}

	if (KeyCode == DIK_X)
	{
		gamestate->simon->Attack();
	}
	if (KeyCode == DIK_RCONTROL)
	{
		gamestate->simon->ThrowSubWp();
	}

}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (!gamestate->simon->isCollideDor)//va cham voi cua
	{
		if (gamestate->game->IsKeyDown(DIK_DOWN))
		{
			if (gamestate->simon->isOnStair == false)
			{
				gamestate->simon->Sit();
			}


			if (gamestate->game->IsKeyDown(DIK_RIGHT))
				gamestate->simon->Right();

			if (gamestate->game->IsKeyDown(DIK_LEFT))
				gamestate->simon->Left();

			return;
		}
		else
			gamestate->simon->Stop();


		if (!gamestate->simon->isOnStair)// ko tren stair
		{
			if (gamestate->simon->beingHit) return;

			if (gamestate->game->IsKeyDown(DIK_RIGHT))
			{
				gamestate->simon->Right();
				gamestate->simon->Go();
				if (gamestate->simon->isAttacking == true)//atttack thi stop
				{
					gamestate->simon->Stop();
				}
			}
			else
				if (gamestate->game->IsKeyDown(DIK_LEFT))
				{
					gamestate->simon->Left();
					gamestate->simon->Go();
					if (gamestate->simon->isAttacking == true)
					{
						gamestate->simon->Stop();
					}
				}
				else
				{
					gamestate->simon->Stop();
				}
		}
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
void ChangeState(int id)
{
	switch (id)
	{
	case 1:
		gamestate->LoadResources(
			"Resource\\sprites\\Grid\\lv1.txt",
			"Resource/sprites/Grid/lv1.b",
			"Resource/sprites/Grid/lv1.s", 9, 4, 36, 6, 24);
		gamestate->camera->SetBorder(LBORDER_1, RBORDER_1);
		gamestate->isChangingState = false;
		break;
	case 2:
		gamestate->LoadResources(
			"Resource\\sprites\\Grid\\lv2.txt",
			"Resource/sprites/Grid/lv2.b",
			"Resource/sprites/Grid/lv2.s", 34, 4, 136, 14, 90);
		gamestate->camera->SetBorder(LBORDER_2, RFIRSTBORDER_2);
		gamestate->isChangingState = false;
		break;
	default:
		break;
	}
}
void InitState(int id)
{
	switch (id)
	{
	case 1:
		gamestate->Init(
			"Resource\\sprites\\Grid\\lv1.txt",
			"Resource/sprites/Grid/lv1.b",
			"Resource/sprites/Grid/lv1.s", 9, 4, 36, 6, 24);
		gamestate->camera->SetBorder(LBORDER_1, RBORDER_1);
		break;
	case 2:
		gamestate->Init(
			"Resource\\sprites\\Grid\\lv2.txt",
			"Resource/sprites/Grid/lv2.b",
			"Resource/sprites/Grid/lv2.s", 34, 4, 136, 14, 90);
		gamestate->camera->SetBorder(LBORDER_2, RFIRSTBORDER_2);
		break;
	default:
		break;
	}
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

			if (gamestate->isChangingState)
			{
				ChangeState(gamestate->id);
			}
			gamestate->game->ProcessKeyboard();

			gamestate->Update(dt);

			gamestate->Render();


		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gamestate = new GameState();
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	gamestate->game->Init(hWnd);
	Sound::GetInstance()->loadSound(hWnd);


	keyHandler = new CSampleKeyHander();
	gamestate->game->InitKeyboard(keyHandler);

	InitState(1);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}

