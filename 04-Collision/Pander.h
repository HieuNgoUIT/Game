#pragma once
#include "GameObject.h"

#define ACTIONBEFOREX 200
#define JUMPVX 0.3f
#define JUMPVY -0.1f
#define RUNVX 0.4f
#define MAXHEIGHT 50
#define GRAVITY 0.05f
class Pander :public CGameObject
{
public:
	float startXpos;
	float startYpos;
	bool doJump;
	bool CheckTop;
	bool allowToDo;
	bool isGrounded;
	float reviveTime = 500;
	Pander(int TYPE, int X, int Y);
	~Pander();
	
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx , vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void RePosition();
};
