#pragma once
#include "SubWeapon.h"
class Axe :public SubWeapon {
public:
	bool CheckTop;
	float currentPos;
	Axe(int X, int Y);
	~Axe();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simondirection);
};