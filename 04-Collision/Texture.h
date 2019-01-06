#pragma once
#include "Game.h"
#include <d3d9.h>
#include <d3dx9.h>
class Texture
{
public:
	char* mfile; 	
	int FrameWidth;
	int FrameHeight;
	int mcols;		
	int mrows;		
	int mcount;		
		
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	Texture(char* fileName, int cols = 1, int rows = 1, int count = 1);
	Texture(char* fileName, int cols, int rows, int count, int R, int G, int B);	
	void Draw(int x, int y);
	void Load();
	void Load(int R, int G, int B);
	~Texture();
};


