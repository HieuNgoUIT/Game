#pragma once

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Game.h" 
#include "Brick.h"
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
#include "debug.h"
using namespace std;

#define GRID_CELL_WIDTH 160
#define GRID_CELL_HEIGHT 120




class Grid
{
	Textures *textures;
	vector<CGameObject*> listObject;
	vector<CGameObject*> cells[500][500];
	void ResetisTake();
 
public:
	void GetListObject(vector<CGameObject*>& ListObj, Camera * camera);
	void ReadFile(char * filename); 
	void DeleteObjects();
	void Insert( int type,  float x, float y, float w, float h); 
	void LoadTextSprite(LPGAMEOBJECT obj, int textureID, int tineAniFrame = 100);
	CGameObject * CreateObject(int type, int x, int y, int w, int h);

	Grid();
	~Grid();
};

