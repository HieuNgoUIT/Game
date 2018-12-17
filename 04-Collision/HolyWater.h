#pragma once
#include "SubWeapon.h"
#include "Sound.h"
class HolyWater :public SubWeapon {
public:
	bool CheckTop;
	float currentPos;
	HolyWater(int X, int Y);
	~HolyWater();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simondirection);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
};