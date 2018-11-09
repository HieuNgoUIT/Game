#pragma once
#include "GameObject.h"
class LargeCandle:public CGameObject
{
public:
	LargeCandle(int X,int Y);
	LargeCandle();
	~LargeCandle();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
};

