#pragma once
#include "SubWeapon.h"
class Knife :public SubWeapon {
public:
	Knife(int X,int Y);
	~Knife();
	void Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simondirection);
};