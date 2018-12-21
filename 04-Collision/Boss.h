#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Sound.h"
class Boss :public CGameObject
{
public:
	
	float positionyToHit;
	float positionxToHit;
	//int heath;
	Boss();
	Boss(int X, int Y);
	~Boss();
	float lastSimonx;
	float lastSimony;
	float waittingtimebeforeattack=125;
	float currentPos;
	bool CheckBot;
	bool CheckTop;
	bool CheckRight;
	bool CheckLeft;

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx,float simony, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	
	void GoStartPosition(DWORD dt, float simonx, float simony);
	void GoSimonPosition(DWORD dt, float simonx, float simony);

	int untouchable;
	DWORD untouchable_start;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
};
