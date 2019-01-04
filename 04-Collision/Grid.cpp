﻿#include "Grid.h"
 
Grid::Grid()
{
	textures= Textures::GetInstance();
	textures->LoadTexture("Resource\\sprites\\Grid\\textures1.txt");
}
 
Grid::~Grid()
{
	
}

void Grid::ReadFileToGrid(char * filename)
{
	listObject.clear();

	std::ifstream input;
	input.open(filename, std::ifstream::in);

	int  type ;
	float x, y ;
	int w =0, h=0 ;
	string checkEnd;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			break;
		}
		type = atoi(checkEnd.c_str());
		if (type == 12 || type == -12 || type == 7 || type == -7 || type == 13 || type == 14)
		{
			input >> x >> y >> w >> h;
		}
		else if (type == 10 || type == 11 || type == 500)
		{
			input >> x >> y >> w ;
		}
		else
		{
			input >> x >> y;
		}	
		Insert(type, x, y, w, h);
	}

}

void Grid::GetListObject(vector<CGameObject*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list
	ResetTake();

	int rowBottom = floor((camera->GetViewport().y + camera->GetHeight()) / (float)GRID_CELL_HEIGHT);
	int rowTop = floor((camera->GetViewport().y) / (float)GRID_CELL_HEIGHT);

	int colLeft = floor((camera->GetViewport().x) / (float)GRID_CELL_WIDTH);
	int colRight = floor((camera->GetViewport().x + camera->GetWidth()) / (float)GRID_CELL_WIDTH);


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (int i = 0; i < cells[row ][col ].size(); i++)
			{
					if (cells[row][col].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row ][col ].at(i));
						cells[row][col].at(i)->isTake = true;
					}

			}
		}
}
void Grid::ResetTake()
{
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->isTake = false;
	}
}
 
vector<CGameObject*> Grid::getListObject()
{
	return listObject;
}

void Grid::DeleteObjects()
{
	for (int i = 0; i < listObject.size(); i++)
	{
		delete(listObject[i]);
	}

}

void Grid::Insert(int type,  float x, float y, float w, float h)
{ 
	LPGAMEOBJECT dataObject = CreateObject(type, x, y, w, h);
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] ");
		return;
	} 
	dataObject->isTake = false;

	if (dynamic_cast<Door *>(dataObject))
	{
		LoadTextSprite(dataObject, dataObject->texId, 1500);
	}
	else
	{
		LoadTextSprite(dataObject, dataObject->texId);
	}

	listObject.push_back(dataObject);

	int Top, Bottom, Left, Right;
	if (type == 12 || type == -12)
	{
		 Top = floor(y / (float)GRID_CELL_HEIGHT);
		 Bottom = floor((y + h) / (float)GRID_CELL_HEIGHT);
		 Left = floor(x / (float)GRID_CELL_WIDTH);
		 Right = floor((x +w) / (float)GRID_CELL_WIDTH);
	}
	else
	{
		 Top = floor(y / (float)GRID_CELL_HEIGHT);
		 Bottom = floor((y + dataObject->_texture->FrameHeight) / (float)GRID_CELL_HEIGHT);
		 Left = floor(x / (float)GRID_CELL_WIDTH);
		 Right = floor((x + dataObject->_texture->FrameWidth) / (float)GRID_CELL_WIDTH);
	}

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row][col].push_back(dataObject);
		}
	}

}
void Grid::LoadTextSprite(LPGAMEOBJECT obj, int textureID, int tineAniFrame)
{
	
	obj->_texture = textures->Get(textureID);
	obj->_sprite = new Sprite(textures->Get(textureID), tineAniFrame);

	obj->deadffect->_sprite = new Sprite(textures->Get(-1), 50);
	obj->hiteffect->_sprite = new Sprite(textures->Get(-2), 1000);
}
CGameObject * Grid::CreateObject(int type, int x, int y,int w, int h)
{
	if (type == BRICK_TYPE1 || type == BRICK_TYPE2) return new Brick(type,x, y, w, h);
	else if (type == BOTSTAIR || type == TOPSTAIR) return new HiddenStair(type, x, y, w, h);//type,x,y,direction,isleft
	else if (type == BREAKABLEBRICK_TYPE1 || type == BREAKABLEBRICK_TYPE2) return new BreakableBrick(type, x, y, w, h);
	else if (type == LARGECANDLE_TYPE ) return new LargeCandle(type,x, y,w); //x,y,typeitem
	else if (type == CANDLE_TYPE ) return new Candle(type, x, y,w);//x,y,typeitem
	else if (type == ZOMBIE_TYPE ) return new Zombie(type, x,y,w); //x,y,direction
	else if (type == PANDER_TYPE) return new Pander(type, x, y);
	else if (type == MERMAID_TYPE ) return new Merman(type, x, y);
	else if (type == BAT_TYPE) return new Bat(type, x, y);
	else if (type == DOOR_TYPE) return new Door(type, x, y);
	else if (type == 1000) return new Boss(type, x, y);
	else if (type == 21) return new CheckPoint(type, x, y);
	return NULL;
}


 