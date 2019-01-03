#include "Grid.h"
 
Grid::Grid()
{

}
 
Grid::~Grid()
{
	
}

void Grid::ReadFileToGrid(char * filename)
{
	listObject.clear();

	std::ifstream input;
	input.open(filename, std::ifstream::in);

	int id , type ;
	float x, y ;
	int w , h ;
	string checkEnd;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			break;
		}
		id = atoi(checkEnd.c_str());
		input >> type >> x >> y >> w >> h;
		Insert(id, type, x, y, w, h);
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
//
//void Grid::GetListObject(vector<CGameObject*> &ListObj, CGameObject * obj)
//{
//	ListObj.clear(); // clear list
//	ResetTake();
//
//	int rowBottom = floor((obj->y + obj->GetHeight()) / (float)GRID_CELL_HEIGHT);
//	int rowTop = floor((obj->y) / (float)GRID_CELL_HEIGHT);
//
//	int colLeft = floor((obj->x) / (float)GRID_CELL_WIDTH);
//	int colRight = floor((obj->x + obj->GetWidth()) / (float)GRID_CELL_WIDTH);
//
//
//	for (int row = rowTop; row <= rowBottom; row++)
//		for (int col = colLeft; col <= colRight; col++)
//		{
//			for (int i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
//			{
//				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
//				{
//					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
//					{
//						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
//						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
//					}
//				}
//			}
//		}
//}

 
 

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

void Grid::Insert(int id, int type,  float x, float y, float w, float h)
{ 
	int Top = floor( y / (float)GRID_CELL_HEIGHT);
	int Bottom = floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = floor(x / (float)GRID_CELL_WIDTH);
	int Right = floor((x+w) / (float)GRID_CELL_WIDTH);

	CGameObject * dataObject = CreateObject(type, x, y, w, h);
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] ");
		return;
	} 
	dataObject->id=id;
	dataObject->isTake = false;

	listObject.push_back(dataObject);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row ][col].push_back(dataObject);
		}
	}

}

CGameObject * Grid::CreateObject(int type, int x, int y,int w, int h)
{
	if (type == BRICK_TYPE1 || type == BRICK_TYPE2) return new Brick(type,x, y, w, h);
	else if (type == LARGECANDLE_TYPE ) return new LargeCandle(type,x, y,w); //x,y,typeitem
	else if (type == CANDLE_TYPE ) return new Candle(type, x, y,w);//x,y,typeitem
	else if (type == ZOMBIE_TYPE ) return new Zombie(type, x,y,w); //x,y,direction
	else if (type == PANDER_TYPE) return new Pander(type, x, y);
	else if (type == MERMAID_TYPE ) return new Merman(type, x, y);
	else if (type == BAT_TYPE) return new Bat(type, x, y);
	else if (type == BOTSTAIR || type ==TOPSTAIR) return new HiddenStair(type,x, y,w,h);//type,x,y,direction,isleft
	else if (type == BREAKABLEBRICK_TYPE1 || type == BREAKABLEBRICK_TYPE2) return new BreakableBrick(type, x, y, w, h);
	else if (type == DOOR_TYPE) return new Door(type, x, y);
	else if (type == 1000) return new Boss(type, x, y);
	return NULL;
}
 