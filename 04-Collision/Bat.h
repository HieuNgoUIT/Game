#pragma once
#include "GameObject.h"
#include "debug.h"
class Bat :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	bool allowToDo;
	Bat(int X, int Y);
	~Bat();
	float currentPos;
	bool CheckBot=false;
	bool CheckTop = false;
	float reviveTime = 500;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx ,vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void RePosition();
	
};
