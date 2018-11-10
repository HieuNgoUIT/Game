#pragma once
#include "GameObject.h"
#include "Simon.h"
class Whip :public CGameObject
{
public:
	Whip(int X, int Y);
	Whip();
	~Whip();
	Simon *simon;
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
 void Render(Camera * camera);
};

