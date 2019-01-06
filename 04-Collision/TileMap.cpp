#include "TileMap.h"

TileMap::TileMap()
{
	
}

void TileMap::LoadMap(char* b,char* s,int row,int col,int total,int rowmaxtrix,int colmatrix)
{
	ReadFile(b,rowmaxtrix,  colmatrix);
	_texture = new Texture(s, row, col, total);//10440  18472
	_sprite = new Sprite(_texture, 100);

}

void TileMap::ReadFile(char * filename, int rowmaxtrix, int colmatrix)
{
	std::ifstream input;
	input.open(filename, std::ios::in);
	if (input)
	{
		for (int i = 0; i < rowmaxtrix; i++)//6  12 88
		{
			for (int j = 0; j < colmatrix; j++)//24
			{
				input >>tileMap[i][j];
			}
		}
		input.close();
	}
}

void TileMap::DrawMap(Camera *camera)
{
	int row = SCREEN_HEIGHT / TILE_HEIGHT;
	int	col = SCREEN_WIDTH / TILE_WIDTH;

	int currentRow=camera->GetViewport().y / TILE_HEIGHT;
	int currentCol=camera->GetViewport().x / TILE_WIDTH;

	x = -(int(camera->GetViewport().x) % _texture->FrameHeight);
	y = -(int(camera->GetViewport().y) % _texture->FrameHeight);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col+1; j++)
		{
			_sprite->SelectIndex(tileMap[currentRow + i][currentCol + j]);
			_sprite->Draw(x+ _texture->FrameHeight*j,y+ _texture->FrameWidth*i);
		}
	}
}


TileMap::~TileMap()
{
}




