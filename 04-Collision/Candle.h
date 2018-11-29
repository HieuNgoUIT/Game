#pragma once
#include "GameObject.h"
#include "Item.h"
class Candle :public CGameObject {
public:
	Item * item;
	Candle(int X, int Y);
	~Candle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
};