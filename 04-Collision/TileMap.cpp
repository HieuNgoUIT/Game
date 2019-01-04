#include "TileMap.h"



TileMap::TileMap()
{
	
}

TileMap::~TileMap()
{
}

void TileMap::LoadMap(char* b,char* s,int row,int col,int total,int rowmaxtrix,int colmatrix)
{
	ReadFile(b,rowmaxtrix,  colmatrix);
	TileTexture = new Texture(s, row, col, total);//10440  18472
	TileSprite = new Sprite(TileTexture, 100);

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
	int row = SCREEN_HEIGHT / 64;
	int	col = SCREEN_WIDTH / 64;

	int currentRow=camera->GetViewport().y / 64;
	int currentCol=camera->GetViewport().x / 64;

	x = -(int(camera->GetViewport().x) % TileTexture->FrameHeight);
	y = -(int(camera->GetViewport().y) % TileTexture->FrameHeight);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col+1; j++)
		{
			TileSprite->SelectIndex(tileMap[currentRow + i][currentCol + j]);
			TileSprite->Draw(x+TileTexture->FrameHeight*j,y+TileTexture->FrameWidth*i);
		}
	}
}





