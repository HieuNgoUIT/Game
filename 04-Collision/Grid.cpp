#include "Grid.h"
 
Grid::Grid()
{

}
 
Grid::~Grid()
{
	
}

void Grid::ReadFileToGrid(char * filename)
{
	listObjectGame.clear();

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
			for (int i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				//if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isDead ==0 /*&& cells[row + GRID_BASE][col + GRID_BASE].at(i)->isCreatedItem == 0*/) // còn tồn tại
				//{
					if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake == false)
					{
						ListObj.push_back(cells[row + GRID_BASE][col + GRID_BASE].at(i));
						cells[row + GRID_BASE][col + GRID_BASE].at(i)->isTake = true;
					}
				/*}*/
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
	for (int i = 0; i < listObjectGame.size(); i++)
	{
		listObjectGame[i]->isTake = false;
	}
}
 
void Grid::Insert(int id, int type,  float x, float y, float w, float h)
{ 
	int Top = floor( y / (float)GRID_CELL_HEIGHT);
	int Bottom = floor((y + h) / (float)GRID_CELL_HEIGHT);

	int Left = floor(x / (float)GRID_CELL_WIDTH);
	int Right = floor((x+w) / (float)GRID_CELL_WIDTH);

	CGameObject * dataObject = GetNewObject(type, x, y, w, h); 
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] : Bo tay roi :v Khong tao duoc object!\n");
		return;
	} 
	dataObject->id=id;
	//dataObject->SetTrend(trend);
	dataObject->isTake = false;

	listObjectGame.push_back(dataObject);

	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row + GRID_BASE][col + GRID_BASE].push_back(dataObject);
		}
	}

}

CGameObject * Grid::GetNewObject(int type, int x, int y,int w, int h)
{
	if (type == 12) return new Brick(type,x, y, w, h);
	if (type == -12) return new Brick(type, x, y, w, h);
	if (type == 10) return new LargeCandle(x, y);
	if (type == 11) return new Candle(x, y);
	if (type == 500) return new Zombie(x, y);
	if (type == -7 || type ==7) return new HiddenStair(type,x, y,w,h);	
	if (type == 80) return new Door(x, y);
	//if (type == 11) return new CheckPoint(x, y);
	return NULL;
}
 