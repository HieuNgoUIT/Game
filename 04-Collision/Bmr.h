#pragma once
#include "SubWeapon.h"
class Bmr :public SubWeapon {
public:
	float currentPos;
	bool isTouchBoundaryR;
	bool isTouchBoundaryL;
	Bmr(int X, int Y);
	~Bmr();
	void Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simondirection);
};