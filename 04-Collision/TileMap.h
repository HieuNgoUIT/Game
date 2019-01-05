﻿#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "debug.h"

#define TILE_FRAME_WIDTH 64
#define TILE_FRAME_HEIGHT 64

class TileMap
{
	int ScreenColumn;
	int ScreenRow;

	int RowMatrix; 
	int ColumnMatrix;

	int ColTile; 
	int RowTile;
	int CountTileFrame; 
	int tileMap[500][500];
	int AutoFit;

	int row; 
	int column; 
	int x, y;

	Texture * _texture;
	Sprite *_sprite;


public:
	TileMap();
	~TileMap();
	void LoadMap(char* b, char* s, int row, int col, int total, int rowmaxtrix, int colmatrix);
	void ReadFile(char * filename, int rowmaxtrix, int colmatrix);
	void DrawMap(Camera * camera);
	
	/*void DrawMapWater(Camera * camera);*/
};




