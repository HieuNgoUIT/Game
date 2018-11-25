#pragma once
#include "GameObject.h"
class HiddenStair :public CGameObject
{
public:
	HiddenStair(int X,int Y);
	~HiddenStair();
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void Render(Camera * camera);
	void RenderBoundingBox(Camera* camera);
};