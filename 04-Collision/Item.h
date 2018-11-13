#pragma once
#include "GameObject.h"
class Item :public CGameObject
{
public:
	
	Item(int X, int Y);
	Item();
	~Item();
	char* PathRandom();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	int GetIsCreated();
	void RenderBoundingBox(Camera* camera);
};
