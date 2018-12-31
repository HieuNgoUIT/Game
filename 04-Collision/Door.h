#pragma once
#include "GameObject.h"
class Door :public CGameObject {
public:
	Door(int TYPE,int X,int Y);
	~Door();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void RenderBoundingBox(Camera* camera);
};