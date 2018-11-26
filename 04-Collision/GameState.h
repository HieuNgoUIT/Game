#pragma once
#include "Grid.h"
#include "Item.h"
#include "UI.h"
#include "Simon.h"
#include "TileMap.h"
#include "Camera.h"
#include "Game.h"
class GameState {
public:
	Item * item;
	Grid *grid;
	UI *ui;
	TileMap *tilemap;
	Simon *simon;
	Camera *camera;
	CGame *game;
	CheckPoint *checkpoint;
	int mapSecond = 0;
	int mapTime = 0;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	bool isChangingState;
	virtual void LoadResources();
	virtual void Update(DWORD dt);
	virtual void Render();
	void CheckCollideWithCheckPoint(Simon *simon, CheckPoint *checkpoint);
	virtual void KillAll();


};