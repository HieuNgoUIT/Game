#pragma once
#include "GameObject.h"

class Zombie :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	
	Zombie(int X,int Y);
	~Zombie();
	float reviveTime=200;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt , float simonx, vector<LPGAMEOBJECT> *coObjects = NULL );
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
