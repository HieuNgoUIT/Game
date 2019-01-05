#pragma once
#include "Game.h"
#include <d3d9.h>
#include <d3dx9.h>
class Texture
{
public:
	char* FileName; 	
	int FrameWidth;
	int FrameHeight;
	int Cols;		
	int Rows;		
	int Count;		
		
	LPDIRECT3DTEXTURE9 texture;
	RECT Size;
	Texture(char* fileName, int cols = 1, int rows = 1, int count = 1);
	Texture(char* fileName, int cols, int rows, int count, int R, int G, int B);
	
	
	~Texture();
	
	void Draw(int x, int y);
	
protected:
	void Load();
	void Load(int R, int G, int B);
};


