#include "TileMap.h"



TileMap::TileMap()
{
	
}


TileMap::~TileMap()
{
}

void TileMap::LoadMap(char* b,char* s)
{
	ReadFile(b);
	TileTexture = new Texture(s, 10, 4, 40);
	TileSprite = new Sprite(TileTexture, 100);

}

void TileMap::ReadFile(char * filename)
{
	std::ifstream input;
	input.open(filename, std::ios::in);
	if (input)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 24; j++)
			{
				input >>tileMap[i][j];
			}
		}
		input.close();
	}


}

void TileMap::DrawMap(Camera *camera)
{
	int row = 480 / 64;
	int	col = 640 / 64;

	int currentRow=camera->GetViewport().y / 64;
	int currentCol=camera->GetViewport().x / 64;

	x = -(int(camera->GetViewport().x) % TileTexture->FrameHeight);
	y = -(int(camera->GetViewport().y) % TileTexture->FrameHeight);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col+1; j++)
		{
			TileSprite->SelectIndex(tileMap[currentRow + i][currentCol + j]);
			TileSprite->Draw(x+TileTexture->FrameHeight*j,y+TileTexture->FrameWidth*i+75);
		}
	}


}

