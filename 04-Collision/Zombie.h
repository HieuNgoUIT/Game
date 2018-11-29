#pragma once
#include "GameObject.h"
class Zombie :public CGameObject
{
public:
	Zombie(int X,int Y);
	~Zombie();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
};
