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
	Item * item;
	Grid *grid;
	UI *ui;
	TileMap *tilemap;
	Simon *simon;
	Boss *boss;
	Camera *camera;
	CGame *game;
	CheckPoint *checkpoint;
	HitEffect *hiteffect;
	float mapSecond = 0;
	float mapTime = 0;
	float WatchTime = 300;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	bool isChangingState;
	GameState();
	~GameState();
	 void LoadResources(char* Ftexture,char* Fgrid,char* Fb, char* Fs, int Frow, int Fcol, int Ftotal, int Frowmaxtrix, int Fcolmatrix);
	 void Update(DWORD dt);
	 void Render();
	void CheckCollideWithCheckPoint(Simon *simon, CheckPoint *checkpoint);
	virtual void KillAll();
	


};
