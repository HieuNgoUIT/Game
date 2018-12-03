#pragma once
#include "GameObject.h"
class Pander :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	Pander(int X, int Y);
	~Pander();
	float reviveTime = 70;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
