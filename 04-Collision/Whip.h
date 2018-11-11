#pragma once
#include "GameObject.h"

#include "LargeCandle.h"
class Whip :public CGameObject
{
public:
	Whip(int X, int Y);
	Whip();
	~Whip();
	bool isFinish;

	void RenderBoundingBox(Camera* camera);
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects);
	 void Create(float simonX, float simonY, int simonTrend);
 void Render(Camera * camera);
};

