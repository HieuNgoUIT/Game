#pragma once
#include "GameObject.h"
#include "WaterEffect.h"
#include "Sound.h"
#include "FireBall.h"

#define ACTIONX 50
#define STARTPLACE 700
#define ENDPLACE 500
#define JUMPV -0.01f
#define GRAVITY 0.05f
class Merman :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	bool allowToDo;
	bool isAttack;
	bool isReachPoint;
	float reviveTime = 500;
	float attackTime = 300;
	float bulletTime = 300;
	Merman(int TYPE, int X, int Y);
	~Merman();
	WaterEffect *watereffect;
	WaterEffect *watereffect1;
	WaterEffect *watereffect2;
	FireBall *fireball;
	
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx , vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
