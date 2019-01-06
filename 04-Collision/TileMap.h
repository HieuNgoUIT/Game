#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "debug.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

class TileMap
{
	int tileMap[500][500];
	int x, y;	
	
public:
	Texture * _texture;
	Sprite *_sprite;

	void LoadMap(char* b, char* s, int row, int col, int total, int rowmaxtrix, int colmatrix);
	void ReadFile(char * filename, int rowmaxtrix, int colmatrix);
	void DrawMap(Camera * camera);
	/*void DrawMapWater(Camera * camera);*/

	TileMap();
	~TileMap();
};




