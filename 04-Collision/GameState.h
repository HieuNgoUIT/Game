#pragma once
#include "Grid.h"
#include "Item.h"
#include "UI.h"
#include "Simon.h"
#include "TileMap.h"
#include "Camera.h"
#include "Game.h"
#include "HitEffect.h"
#include "debug.h"
class GameState {
public:
	int id;
	int bossHP = 0;
	float mapSecond = 0;
	float mapTime = 0;
	bool isChangingState;

	Item * item;
	Grid *grid;
	UI *ui;
	TileMap *tilemap;
	Simon *simon;
	Camera *camera;
	CGame *game;


	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	
	GameState();
	~GameState();

	void LoadResources(char* Fgrid, char* Fb, char* Fs, int Frow, int Fcol, int Ftotal, int Frowmaxtrix, int Fcolmatrix);
	void Init(char* Fgrid, char* Fb, char* Fs, int Frow, int Fcol, int Ftotal, int Frowmaxtrix, int Fcolmatrix);
	void Update(DWORD dt);
	void Render();
	void CheckCollideWithCheckPoint(Simon *simon);
	void CheckClearAllObj();
	void ResetLife();

};
