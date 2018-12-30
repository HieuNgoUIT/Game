#pragma once
#include "GameObject.h"
#include "WaterEffect.h"
#include "Sound.h"
#include "FireBall.h"
class Merman :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	bool allowToDo;
	bool isAttack;
	Merman(int TYPE, int X, int Y);
	~Merman();
	WaterEffect *watereffect;
	WaterEffect *watereffect1;
	WaterEffect *watereffect2;
	FireBall *fireball;
	bool isReachPoint;
	float reviveTime = 500;
	float attackTime = 300;
	float bulletTime = 300;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx , vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
