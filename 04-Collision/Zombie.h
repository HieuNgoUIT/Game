#pragma once
#include "GameObject.h"

class Zombie :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	
	Zombie(int X,int Y,int direction);
	~Zombie();
	float reviveTime=300;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt ,Camera *camera, float simonx, vector<LPGAMEOBJECT> *coObjects = NULL );
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition(Camera *camera);
};
