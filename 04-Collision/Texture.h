#ifndef __CTEXTURE_H__
#define __CTEXTURE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"


class Texture
{
public:
	char* FileName; 
	RECT Size;		
	LPDIRECT3DTEXTURE9 texture;
	int Cols;		
	int Rows;		
	int Count;		
	int FrameWidth;		
	int FrameHeight;	

	Texture(char* _fileName, int cols = 1, int rows = 1, int count = 1);
	Texture(char* _fileName, int cols, int rows, int count, int R, int G, int B);
	
	
	~Texture();
	
	void Draw(int x, int y);
	
protected:
	void Load();
	void Load(int R, int G, int B);
};


#endif