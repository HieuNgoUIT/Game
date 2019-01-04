#pragma once
#include "GameObject.h"
#include "Item.h"
class CheckPoint :public CGameObject
{
public:
	
	CheckPoint(int TYPE, int X, int Y);
	~CheckPoint();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	void RenderBoundingBox(Camera* camera);
};

