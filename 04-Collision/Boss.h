#pragma once
#include "GameObject.h"
#include "debug.h"
class Boss :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	Boss(int X, int Y);
	~Boss();
	float lastSimonx;
	float lastSimony;
	float currentPos;
	bool CheckBot;
	bool CheckTop;
	bool CheckRight;
	bool CheckLeft;
	bool isReady;
	bool doneHitSimon;
	float reviveTime = 70;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx,float simony, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void RePosition();
	void GoStartPosition(DWORD dt, float simonx, float simony);
	void GoSimonPosition(DWORD dt, float simonx, float simony);
};
