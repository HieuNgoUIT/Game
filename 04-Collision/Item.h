#pragma once
#include "GameObject.h"


class Item :public CGameObject
{
public:
	
	Item();
	Item(int objectnumber,int X,int Y);
	~Item();

	float remainingTime;
	bool CheckLeft = false;
	bool CheckRight = false;
	float currentPos;
	bool isGrounded;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, float simonx = 0, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	int GetIsCreated();
	void RenderBoundingBox(Camera* camera);
	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	
};
