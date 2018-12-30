#pragma once
#include "GameObject.h"
#include "Item.h"
class LargeCandle:public CGameObject
{
public:
	
	Item * item;

	LargeCandle(int type, int X,int Y, int numberItem);
	LargeCandle();
	~LargeCandle();
	
	void Delete();
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt,float simonx=0, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void Render(Camera * camera);
	void RenderBoundingBox(Camera* camera);
	char* ConvertItemNumbertoString(int number);
};

