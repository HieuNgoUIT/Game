#pragma once
#include "GameObject.h"
#include "WaterEffect.h"
class Merman :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	Merman(int X, int Y);
	~Merman();
	WaterEffect *watereffect;
	WaterEffect *watereffect1;
	WaterEffect *watereffect2;
	bool isReachPoint;
	float reviveTime = 70;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
