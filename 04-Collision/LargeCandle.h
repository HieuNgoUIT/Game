#pragma once
#include "GameObject.h"
#include "Item.h"
class LargeCandle:public CGameObject
{
public:
	Item * item;
	LargeCandle(int X,int Y, int pos);
	LargeCandle();
	~LargeCandle();
	void Delete();
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void Render(Camera * camera);
	void RenderBoundingBox(Camera* camera);
};

