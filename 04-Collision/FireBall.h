#pragma once
#include "GameObject.h"
class FireBall :public CGameObject
{
public:

	FireBall(int X, int Y);
	~FireBall();
	
	
	float reviveTime = 500;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	
};
