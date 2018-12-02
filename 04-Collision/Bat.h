#pragma once
#include "GameObject.h"
#include "debug.h"
class Bat :public CGameObject
{
public:
	Bat(int X, int Y);
	~Bat();
	float currentPos;
	bool CheckBot=false;
	bool CheckTop = false;
	float reviveTime = 70;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	
};
