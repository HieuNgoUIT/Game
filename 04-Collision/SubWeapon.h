#pragma once
#include "GameObject.h"

#include "LargeCandle.h"
class SubWeapon :public CGameObject
{
public:
	SubWeapon(int X, int Y);
	SubWeapon();
	~SubWeapon();
	bool isFinish;
	float remainingTime;
	void RenderBoundingBox(Camera* camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects);
	void Create(float simonX, float simonY, int simondirection);
	void Render(Camera * camera);
	
};

