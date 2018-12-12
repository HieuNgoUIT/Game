#pragma once
#include "GameObject.h"
class Pander :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	bool doJump;
	bool isGrounded;
	bool CheckTop;
	bool allowToDo;
	Pander(int X, int Y);
	~Pander();
	float reviveTime = 500;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx , vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
