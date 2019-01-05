#pragma once
#include "SubWeapon.h"
class StopWatch :public SubWeapon {
public:
	StopWatch();
	~StopWatch();
	void Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Create(float simonX, float simonY, int simondirection);
}; 
