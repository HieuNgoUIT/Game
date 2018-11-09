﻿#ifndef __MAP_H__
#define __MAP_H__


#include <stdio.h>

#include "Texture.h"
#include "Sprite.h"


#include "Camera.h"

#include <fstream>
#include <iostream>
#include <iosfwd>

#define TILE_FRAME_WIDTH 64
#define TILE_FRAME_HEIGHT 64

class TileMap
{
private:
	Texture * TileTexture;
	Sprite *TileSprite;

	int ScreenColumn;
	int ScreenRow;

	int RowMatrix; // số lượng dòng của ma trận tilemap txt
	int ColumnMatrix;// số lượng cột của ma trận tilemap txt

	int ColTile; // số lượng cột tile trong texture
	int RowTile;// số lượng dòng tile trong texture
	int CountTileFrame; // tổng số lương tile trong texture 
	int tileMap[500][500];
	int AutoFit;


	int row; // dòng hiện tại camera đang đứng
	int column; //cột hiện tại camera đang đứng
	int x, y;


public:
	TileMap();
	~TileMap();
	void LoadMap();
	void ReadFile(char * filename);
	void DrawMap(Camera * camera);

};




#endif