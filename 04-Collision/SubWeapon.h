#pragma once
#include "GameObject.h"

#include "LargeCandle.h"
class SubWeapon :public CGameObject
{
public:
	SubWeapon(/*int X, int Y*/);
	//SubWeapon();
	~SubWeapon();
	bool isFinish;
	//bool isSubwp;
	float remainingTime;
	/*void RenderBoundingBox(Camera* camera);*/
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt,float left,float right, vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	virtual void Create(float simonX, float simonY, int simondirection);
	void Render(Camera * camera);
	
};

