#pragma once

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Game.h" 
#include <string>
#include "Brick.h"
#include "debug.h"
#include "LargeCandle.h"
#include "CheckPoint.h"
#include "HiddenStair.h"
#include "Door.h"
#include "Candle.h"
#include "Zombie.h"
#include "Pander.h"
#include "Merman.h"
#include "Bat.h"
#include "BreakableBrick.h"
#include "Door.h"
#include "Boss.h"
#include "CheckPoint.h"
using namespace std;

#define GRID_CELL_WIDTH 256
#define GRID_CELL_HEIGHT 224




class Grid
{ 

private:
	vector<CGameObject*> listObject;
	vector<CGameObject*> cells[500][500];
	Textures *textures;
	void ResetTake();
 
public:
	void ReadFileToGrid(char * filename); 
	void GetListObject(vector<CGameObject*>& ListObj, Camera * camera);
	
	vector<CGameObject*> getListObject();
	void DeleteObjects();
	void Insert( int type,  float x, float y, float w, float h); 
	void LoadTextSprite(LPGAMEOBJECT obj, int textureID, int tineAniFrame = 100);
	CGameObject * CreateObject(int type, int x, int y, int w, int h);

	Grid();
	~Grid();
};

